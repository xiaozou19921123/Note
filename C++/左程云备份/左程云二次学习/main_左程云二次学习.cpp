#include <iostream>
#include <string>
#include <algorithm>
#include <exception>
using namespace std;

void test(int input=1)
{
	cout << "filename="<<__FILE__ << endl;
	cout << "line=" << __LINE__ << endl;
	cout<<"function="<<__FUNCTION__ << endl;
	
}


//异常测试：exception使用;double、string等系统类型、自定义类型
void throw_test()
{

	throw exception("01-throw excption runing!");
	throw string("02-throw string");
}
void throw_test2()
{
	throw string("02-throw string");
}
void exception_test()
{
	try
	{
		throw_test();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		throw_test2();
	}
	catch (string info)
	{
		cout << info << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}
}

//memset使用
/*
memset是按照字节对待初始化空间进行初始化的，也就是说，函数里面的第二个参数的那个初值（一般为0）
是按照一个一个字节往第一个参数所指区域赋值的，所以，对于单字节数据类型（char）可以初始化为任意
支持的值，都没有问题，但是对于非多字节数据类型只能初始化为0，而不能初始化成别的初值，因为对所
有字节按任意顺序赋值0的结果都是0，而如果初始化为其他的值，就会一个字节一个字节的进行赋值，
从而出现奇怪的结果。比如说，上面的例3之所以没有出错就是因为初始化为0，但是如果初始化为1，
那么因为int一般是4个字节，那么相当于将一个int元素初始化成了0000 0001 0000 0001 0000 0001 0000 0001，
这样对于一个int元素肯定不是1，而是一个很大的数
*/
void memset_test()
{
	int i = 0;
	// 例1：对字符数组进行初始化  
	char buf[10];
	memset(buf, 0, sizeof(char) * 10);   // 0或者'\0'是等价的  
	for (i = 0; i < 10; ++i)
	{
		printf("%c", buf[i]);
	}
	printf("\n");

	// 例2：对字符指针所指区域初始化，必须已经分配内存  
	char* pBuf = (char *)malloc(sizeof(char) * 10);

	if (pBuf != NULL)
	{
		memset(pBuf, '1', sizeof(char) * 10);     // 0或者'\0'是等价的  
		for (i = 0; i < 10; ++i)
		{
			printf("%c ", pBuf[i]);
		}
		printf("\n");

		free(pBuf);
		pBuf = NULL;
	}

	// 例3：对整型数组进行初始化  
	int iBuf[10];
	memset(iBuf, 127, sizeof(int) * 10);//第二个数字为0,完成数组所有初始化为0。为1不是
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", iBuf[i]);
	}
	printf("\n");
}


//数组实现栈
template<typename T>
class ArrayStack
{
public:
	ArrayStack(int iniSize);
	~ArrayStack();

	T top();
	void pop();
	void push(T obj);
	bool empty();
private:
	T *arr;
	int size;
	int len;
};

template<typename T>
ArrayStack<T>::ArrayStack(int iniSize) :len(iniSize), size(-1)
{
	if (iniSize < 1)
	{
		throw exception("无效初始化长度");
	}

	arr = new T[iniSize];

}
template<typename T>
ArrayStack<T>::~ArrayStack()
{
	delete arr;
}

template<typename T>
T ArrayStack<T>::top()
{
	if (size == -1)
	{
		throw exception("栈为空");
	}
	return arr[size];
}

template<typename T>
void ArrayStack<T>::push(T obj)
{
	if (++size > len - 1)
	{
		throw exception("栈已满");
	}
	arr[size] = obj;
}

template<typename T>
void ArrayStack<T>::pop()
{
	if (size == -1)
	{
		throw exception("栈为空");
	}
	size--;
}

template<typename T>
bool ArrayStack<T>::empty()
{
	return size <0 ? true : false;
}


void template_arrayStack_test()
{
	try
	{
		ArrayStack<string> *arrayStack = new ArrayStack<string>(5);
		
		arrayStack->push("a");
		arrayStack->push("b");
		arrayStack->push("c");
		arrayStack->pop();
		//arrayStack->pop();
		//arrayStack->pop();
		//arrayStack->pop();

		arrayStack->push("d");
		arrayStack->push("e");
		arrayStack->push("f");

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
int main()
{
	
	//test();

	//exception_test();//异常测试

	//memset_test();

	template_arrayStack_test();//模版使用
	


	/*int *arr=new int[1];
	arr[0] = 1;
	arr[1] = 2;
	cout << "size=" << sizeof(arr) / sizeof(int) <<",arr[0]=" <<arr[0]<<endl;
	arr[2] = 3;
	cout << "size=" << sizeof(arr) / sizeof(int) << ",arr[0]=" << arr[1] << endl;

	delete arr;*/
	getchar();
}