#include "sendbuffer.h"
#include <thread>
#include <iostream>

SendBuffer buffer;

void Producer()
{
    char tmp[1024];
    while (true)
    {
        size_t pushcount = rand() % 1024;
        if (!buffer.Push(tmp, pushcount))
        {
            std::cout << "full" << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Consumer()
{
    while (true)
    {
        size_t len;
        char* buf = buffer.Peek(len);
        if (!buf)
        {
            std::cout << "empty" << std::endl;
            break;
        }
        buffer.Pop(len);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::thread p1(Producer);
    std::thread p2(Producer);
    std::thread p3(Producer);

    std::thread c(Consumer);

    p1.join();
    p2.join();
    p3.join();

    c.join();

    int n;
    std::cin >> n;
    return 0;
}