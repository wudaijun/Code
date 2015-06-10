#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

template<typename T>
class Stack
{
public:
	Stack()
		:_top(-1), _capacity(512)
	{
		_base = new T[_capacity];
	}

	bool push(const T& t)
	{
		if(_top == _capacity - 1)
		{
			T* oldbase = _base;
			_base = new T[_capacity*2];
			memcpy((char*)_base, (char*)oldbase, _capacity*sizeof(T));
			_capacity <<= 1;
		}
		_base[_top+1] = t;
		++ _top;
		return true;
	}

	bool pop(T& t)
	{
		if(_top == -1)
			return false;
		t = _base[_top--];
		return true;
	}

private:
	int _top;  // 当前栈顶位置
	int _capacity; // 容量
	T* _base; // 栈起始位置
};

#define LEFT (-1)  // (
#define RIGHT (-2) // )
#define ADD (-3)   // +
#define SUB (-4)   // -
class Solution
{
public:
	int caculate(string s)
	{
		const size_t length = s.size();
		
		int curnum = -1;
		int result = 0;
		for(int i=0; i<length; ++i)
		{
			char c = s[i];
			switch(c)
			{
			case ' ':
				break;

			case '+':
				_stack.push(calc(curnum));
				curnum = -1;
				_stack.push(ADD);
				break;

			case '-':
				_stack.push(calc(curnum));
				curnum = -1;
				_stack.push(SUB);
				break;

			default:
				if(curnum == -1)
					curnum = c - '0';
				else
					curnum = curnum*10 + (c-'0');
				break;
			}
		}
		
		return calc(curnum);
	}
	
	int calc(int n)
	{
		int arg, op;
		if(!_stack.pop(op))
		{
			return n;
		}
		assert(_stack.pop(arg));
		int result = 0;
		switch(op)
		{
		case ADD:
			result = arg + n;
			break;
		case SUB:
			result = arg - n;
			break;
		define:
			std::cerr<<"error: unknown op"<<endl;
			break;
		}
		return result;
	}

private:
	Stack<int> _stack; 
};

int main()
{
	Solution s;
	string expr;
	cout<<"input expr: "<<endl;
	cin >> expr;
	while(expr != "q")
	{ 
		cout<<s.caculate(expr)<<endl;
		cout<<"input expr: "<<endl;
		cin >> expr;
	}
	return 0;
}

