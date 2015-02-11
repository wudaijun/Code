#include "sendbuffer.h"

SendBuffer::SendBuffer(size_t capacity /* = 65536 */)
{
    size_t fix_capacity = 16;
    while (fix_capacity < capacity)
        fix_capacity <<= 1;

    _capacity = fix_capacity;
    _capacity_mask = _capacity - 1;

    _buffer = new char[_capacity];

    _alloc_count = 0;
    _read_count = 0;
    _write_count = 0;
    _idle_count = _capacity;
}

SendBuffer::~SendBuffer()
{
    delete []_buffer;
}

bool SendBuffer::Push(const char* data, size_t len)
{
    if (nullptr == data || len == 0 || len > _capacity)
        return false;

    auto idle = _idle_count.fetch_sub(len);
    if (idle >= len)
    {
        // 申请写入空间
        auto alloc_start = _alloc_count.fetch_add(len);
        auto alloc_end = alloc_start + len;

        // 执行写入
        auto fix_start = alloc_start & _capacity_mask;
        auto fix_end = alloc_end & _capacity_mask;
        if (fix_start < fix_end)
        {
            memcpy(_buffer + fix_start, data, len);
        }
        else// 分两段写
        {
            auto first_len = _capacity - fix_start;
            memcpy(_buffer + fix_start, data, first_len);
            memcpy(_buffer, data + first_len, fix_end);
        }

        // 更新写入位置
        while (true)
        {
            auto tmp = alloc_start;
            if (_write_count.compare_exchange_weak(tmp, alloc_end))
                break;
        }
        return true;
    }
    else
    {
        _idle_count.fetch_add(len);
        return false;
    }
}

char* SendBuffer::Peek(size_t& len)
{
    if (_read_count < _write_count)
    {
        auto can_read = _write_count - _read_count;
        auto fix_start = _read_count & _capacity_mask;
        auto fix_end = (_read_count + can_read) & _capacity_mask;
        if (fix_start >= fix_end) 
        {
            // 只返回第一段
            can_read = _capacity - fix_start;
        }
        len = static_cast<size_t>(can_read);
        return _buffer + fix_start;
    }
    return nullptr;
}

bool SendBuffer::Pop(size_t len)
{
    if (_read_count + len <= _write_count)
    {
        _read_count += len;
        _idle_count.fetch_add(len);
        return true;
    }
    return false;
}