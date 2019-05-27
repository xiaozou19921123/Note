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


//�쳣���ԣ�exceptionʹ��;double��string��ϵͳ���͡��Զ�������
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
		cout << "δ֪�쳣" << endl;
	}
}

//memsetʹ��
/*
memset�ǰ����ֽڶԴ���ʼ���ռ���г�ʼ���ģ�Ҳ����˵����������ĵڶ����������Ǹ���ֵ��һ��Ϊ0��
�ǰ���һ��һ���ֽ�����һ��������ָ����ֵ�ģ����ԣ����ڵ��ֽ��������ͣ�char�����Գ�ʼ��Ϊ����
֧�ֵ�ֵ����û�����⣬���Ƕ��ڷǶ��ֽ���������ֻ�ܳ�ʼ��Ϊ0�������ܳ�ʼ���ɱ�ĳ�ֵ����Ϊ����
���ֽڰ�����˳��ֵ0�Ľ������0���������ʼ��Ϊ������ֵ���ͻ�һ���ֽ�һ���ֽڵĽ��и�ֵ��
�Ӷ�������ֵĽ��������˵���������3֮����û�г��������Ϊ��ʼ��Ϊ0�����������ʼ��Ϊ1��
��ô��Ϊintһ����4���ֽڣ���ô�൱�ڽ�һ��intԪ�س�ʼ������0000 0001 0000 0001 0000 0001 0000 0001��
��������һ��intԪ�ؿ϶�����1������һ���ܴ����
*/
void memset_test()
{
	int i = 0;
	// ��1�����ַ�������г�ʼ��  
	char buf[10];
	memset(buf, 0, sizeof(char) * 10);   // 0����'\0'�ǵȼ۵�  
	for (i = 0; i < 10; ++i)
	{
		printf("%c", buf[i]);
	}
	printf("\n");

	// ��2�����ַ�ָ����ָ�����ʼ���������Ѿ������ڴ�  
	char* pBuf = (char *)malloc(sizeof(char) * 10);

	if (pBuf != NULL)
	{
		memset(pBuf, '1', sizeof(char) * 10);     // 0����'\0'�ǵȼ۵�  
		for (i = 0; i < 10; ++i)
		{
			printf("%c ", pBuf[i]);
		}
		printf("\n");

		free(pBuf);
		pBuf = NULL;
	}

	// ��3��������������г�ʼ��  
	int iBuf[10];
	memset(iBuf, 127, sizeof(int) * 10);//�ڶ�������Ϊ0,����������г�ʼ��Ϊ0��Ϊ1����
	for (i = 0; i < 10; ++i)
	{
		printf("%d ", iBuf[i]);
	}
	printf("\n");
}


//����ʵ��ջ
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
		throw exception("��Ч��ʼ������");
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
		throw exception("ջΪ��");
	}
	return arr[size];
}

template<typename T>
void ArrayStack<T>::push(T obj)
{
	if (++size > len - 1)
	{
		throw exception("ջ����");
	}
	arr[size] = obj;
}

template<typename T>
void ArrayStack<T>::pop()
{
	if (size == -1)
	{
		throw exception("ջΪ��");
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

	//exception_test();//�쳣����

	//memset_test();

	template_arrayStack_test();//ģ��ʹ��
	


	/*int *arr=new int[1];
	arr[0] = 1;
	arr[1] = 2;
	cout << "size=" << sizeof(arr) / sizeof(int) <<",arr[0]=" <<arr[0]<<endl;
	arr[2] = 3;
	cout << "size=" << sizeof(arr) / sizeof(int) << ",arr[0]=" << arr[1] << endl;

	delete arr;*/
	getchar();
}