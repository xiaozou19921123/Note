#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <exception>
using namespace std;



//数组实现栈
class ArrayStack
{
public:
	ArrayStack(int iniSize);
	~ArrayStack(){ delete[] arr; }

	int& operator[](int index);
	int top();
	void pop();
	void push(int obj);
	bool empty();
private:
	int *arr;
	int size;
	int len;
};
int& ArrayStack::operator[](int index)
{
	if (index < 0)
	{
		throw exception("栈为空");
	}
	return arr[index];
}
ArrayStack::ArrayStack(int iniSize) :len(iniSize),size(-1)
{
	if (iniSize < 1)
	{
		throw exception("无效初始化长度");
	}

	arr = new int[iniSize];
	
}
int ArrayStack::top()
{
	if (size ==-1)
	{
		throw exception("栈为空");
	}
	//cout << "top=" << arr[size];
	return arr[size];
}

void ArrayStack::push(int obj)
{
	if (++size > len - 1)
	{
		throw exception("栈已满");
	}

	arr[size] = obj;
	//cout << "arr[size]=" << arr[size] << "size=" << size << endl;;
}
void ArrayStack::pop()
{
	if (size == -1)
	{
		throw exception("栈为空");
	}
	size--;
}

bool ArrayStack::empty()
{
	return size <0 ? true : false;
}

void arrayStack_test()
{
	try
	{
		ArrayStack *arrayStack = new ArrayStack(5);
		//int a=arrayStack->top();
		arrayStack->push(1);
		arrayStack->push(2);
		arrayStack->push(3);
		arrayStack->pop();
		//arrayStack->pop();
		//arrayStack->pop();
		//arrayStack->pop();

		arrayStack->push(5);
		arrayStack->push(6);
		arrayStack->push(6);

		cout << "重载[]=" << (*arrayStack)[0] << " " << (*arrayStack)[1] << " " << (*arrayStack)[2] << endl;
		while (!arrayStack->empty())
		{
			cout << arrayStack->top() << " ";
			arrayStack->pop();
		}
		cout << endl;
	}
	catch (exception &e)
	{
		cout << "error=" << e.what() << endl;
	}
}

//数组实现队列
class ArrayQueue
{
public:
	ArrayQueue(int iniSize);
	~ArrayQueue(){ delete[]arr; }
	void push(int obj);
	int pop();
	int front();
	bool empty();
private:

	int *arr;
	int len;
	int first;
	int last;
	int size;
};

ArrayQueue::ArrayQueue(int iniSize) :len(iniSize), size(0),first(0), last(0)
{
	if (iniSize < 1)
	{
		throw exception("无效的初始化输入长度");
	}
	arr = new int[iniSize];
}
void ArrayQueue::push(int obj)
{
	if (++size >len)
	{
		throw exception("队里已满");
	}
	arr[last] = obj;
	last = last==len-1? 0 : last + 1;
	
}

int ArrayQueue::pop()
{
	if (--size < 0)
	{
		throw exception("队列已空");
	}
	int temp = first;
	first = first==len-1? 0 : first + 1;
	return arr[temp];
}

int ArrayQueue::front()
{
	if (size <0)
	{
		throw exception("队列已空");
	}
	return arr[last];
	
}
bool ArrayQueue::empty()
{
	return size>0 ? false : true;
}

void ArrayQueue_test()
{
	try
	{
		ArrayQueue *arrayQueue = new ArrayQueue(5);
		arrayQueue->push(1);
		arrayQueue->push(2);
		arrayQueue->push(3);
		arrayQueue->pop();
		//arrayQueue->pop();
		//arrayQueue->pop();
		//arrayQueue->pop();

		arrayQueue->push(5);
		arrayQueue->push(6);
		arrayQueue->push(6);
		while (!arrayQueue->empty())
		{
			cout << arrayQueue->pop() << " ";

		}
		cout << endl;
	}
	catch (exception &e)
	{
		cout << "error=" << e.what() << endl;
	}
}

//返回栈的最小值
class GetMinStack
{
public:
	GetMinStack();
	~GetMinStack();

	void push(int obj);
	int pop();
	int getMin();
	bool empty();
	int top();

private:
	stack<int>*m_stack;
	stack<int>*help;
};

GetMinStack::GetMinStack()
{
	m_stack = new stack<int>();
	help = new stack<int>();
}
GetMinStack::~GetMinStack()
{
	delete m_stack, help;
}
void GetMinStack::push(int obj)
{
	m_stack->push(obj);
	int temp = help->empty() ? obj : std::min(obj, help->top());
	help->push(temp);
}
int GetMinStack::pop()
{
	if (m_stack->empty())
	{
		throw exception("栈为空");
	}
	int pop_value = m_stack->top();
	m_stack->pop();
	help->pop();
	return pop_value;

}
int GetMinStack::getMin()
{
	if (m_stack->empty())
	{
		throw exception("栈为空");
	}
	return help->top();
}
bool GetMinStack::empty()
{
	return m_stack->empty() ? true : false;
}

void getMinStack_test()
{
	try
	{
		GetMinStack *getMinStack = new GetMinStack();
		getMinStack->push(9);
		getMinStack->push(2);
		cout << "getMin=" << getMinStack->getMin() << endl;
		getMinStack->pop();
		cout << "getMin=" << getMinStack->getMin() << endl;
		getMinStack->push(8);
		cout << "getMin=" << getMinStack->getMin() << endl;
		getMinStack->push(10);
		getMinStack->push(1);
		cout << "getMin=" << getMinStack->getMin() << endl;
		while (!getMinStack->empty())
		{
			cout << getMinStack->pop() << " ";
		}
		cout << endl;
	}
	catch (exception e)
	{
		cout << "error," << e.what() << endl;
	}
	
}

//两个栈实现队列
class Stack2Queue
{
public:
	Stack2Queue();
	~Stack2Queue();
	void push(int obj);
	int pop();
	int front();
	bool empty();

private:
	stack<int>*pushStack;
	stack<int>*popStack;
};

Stack2Queue::Stack2Queue()
{
	pushStack = new stack<int>();
	popStack = new stack<int>();
}
Stack2Queue::~Stack2Queue()
{
	delete pushStack, popStack;
}

void Stack2Queue::push(int obj)
{
	pushStack->push(obj);
}

int Stack2Queue::pop()
{
	if (pushStack->empty() && popStack->empty())
	{
		throw exception("栈为空");
	}

	if (popStack->empty())
	{
		while (!pushStack->empty())
		{
			int temp = pushStack->top();
			pushStack->pop();
			popStack->push(temp);
		}
	}
	int temp = popStack->top();
	popStack->pop();
	return temp;

}

int Stack2Queue::front()
{
	if (pushStack->empty() && popStack->empty())
	{
		throw exception("栈为空");
	}

	if (popStack->empty())
	{
		while (!pushStack->empty())
		{
			int temp = pushStack->top();
			pushStack->pop();
			popStack->push(temp);
		}
	}
	return  popStack->top();

}
bool Stack2Queue::empty()
{
	return pushStack->empty() && popStack->empty() ? true : false;
}

void stack2Queue_test()
{
	try
	{
		Stack2Queue *stack2Queue = new Stack2Queue();
		stack2Queue->push(3);
		stack2Queue->push(1);
		stack2Queue->push(2);
		stack2Queue->pop();
		stack2Queue->push(5);
		stack2Queue->push(9);
		while (!stack2Queue->empty())
		{
			cout << stack2Queue->pop() << " ";
		}
		cout << endl;
	}
	catch (exception &e)
	{
		cout << "error," << e.what() << endl;
	}
	
}

//两个队列实现栈
class Queue2Stack
{
public:
	Queue2Stack();
	~Queue2Stack();
	void push(int obj);
	int pop();
	int top();
	bool empty();
	void swap();
private:
	queue<int>*pushQueue,*helpQueue;

};
Queue2Stack::Queue2Stack()
{
	pushQueue = new queue<int>();
	helpQueue = new queue<int>();
}
Queue2Stack::~Queue2Stack()
{
	delete pushQueue, helpQueue;
}
void Queue2Stack::swap()
{
	queue<int>*temp = pushQueue;
	pushQueue = helpQueue;
	helpQueue = temp;
}
void Queue2Stack::push(int obj)
{
	pushQueue->push(obj);
}

int Queue2Stack::pop()
{
	if (pushQueue->empty())
	{
		throw exception("栈为空");
	}
	while (pushQueue->size() > 1)
	{
		int temp = pushQueue->front();
		helpQueue->push(temp);
		pushQueue->pop();
	}
	int popValue = pushQueue->front();
	pushQueue->pop();
	swap();
	return popValue;
}

int Queue2Stack::top()
{
	if (pushQueue->empty())
	{
		throw exception("栈为空");
	}
	while (pushQueue->size() > 1)
	{
		int temp = pushQueue->front();
		helpQueue->push(temp);
		pushQueue->pop();
	}
	int frontValue = pushQueue->front();
	pushQueue->pop();
	helpQueue->push(frontValue);
	swap();
	return frontValue;
}

bool Queue2Stack::empty()
{
	return pushQueue->empty() && helpQueue->empty() ? true : false;
}

void queue2Stack_test()
{
	try
	{
		Queue2Stack *queue2Stack = new Queue2Stack();
		queue2Stack->push(3);
		queue2Stack->push(1);
		queue2Stack->push(2);
		queue2Stack->pop();
		queue2Stack->push(5);
		queue2Stack->push(9);
		while (!queue2Stack->empty())
		{
			cout << queue2Stack->pop() << " ";
		}
		cout << endl;
	}
	catch (exception &e)
	{
		cout << "error," << e.what() << endl;
	}
}

int main()
{
	
	//arrayStack_test();//数组实现栈

	//ArrayQueue_test();//数组实现队列

	//getMinStack_test();//返回栈最小值

	//stack2Queue_test();//两个栈实现一个队列

	//queue2Stack_test();//两个队列实现一个栈



	getchar();
}