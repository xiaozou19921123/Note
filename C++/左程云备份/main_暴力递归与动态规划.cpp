#include <iostream>
#include <algorithm>
#include <string>
#include<hash_map>
#include<hash_set>
#include <limits.h>
#include <stack>
using namespace std;

void swap(string &str,int i,int j)
{
	if (i >= str.length() || j >= str.length())
	{
		return;
	}
	char temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}
//---------------------------------------------------------------------------
//�����ݹ�
long getFactor(int n)
{
	if (n == 1)
	{
		return 1L;
	}
	return (long)n*getFactor(n - 1);
}

int getMin(int *arr, int L, int R)
{
	if (L == R)
	{
		return arr[L];
	}
	int mid = (L + R) / 2;
	int leftMin = getMin(arr, L, mid);
	int rightMin = getMin(arr, mid+1, R);
	return std::min(leftMin, rightMin);
}

void digui_test()
{
	cout << "�׳ˣ�" << getFactor(5) << endl;
	int arr[] = { 4, 1, 9, 3, 8, 10 };
	cout << "���ַ���ȡ��Сֵ��" << getMin(arr, 0, sizeof(arr) / sizeof(int) - 1);
}
//---------------------------------------------------------------------------
//��С·������--�����ݹ�汾

const int COLS = 3;
int process(int matrix[][COLS], int i, int j, int rows, int cols);
int miniPath(int matrix[][COLS], int rows, int cols)
{
	return process(matrix, 0, 0, rows, cols);
}

int process(int matrix[][COLS], int i, int j, int rows, int cols)
{
	if (i == rows - 1 && j == cols - 1)
	{
		return matrix[i][j];
	}
	if (i == rows - 1)
	{
		return matrix[i][j] + process(matrix, i, j + 1, rows, cols);
	}
	if (j == cols - 1)
	{
		return matrix[i][j] + process(matrix, i+1, j, rows, cols);
	}
	return matrix[i][j] + std::min(process(matrix, i, j + 1, rows, cols), process(matrix, i+1, j, rows, cols));
}
//++++++++++++++++++++++
//��С·������--��̬�滮�汾
hash_map<string, int> cache;
int process2(int matrix[][COLS], int i, int j, int rows, int cols);
int miniPath2(int matrix[][COLS], int rows, int cols)
{
	return process2(matrix, 0, 0, rows, cols);
}

int process2(int matrix[][COLS], int i, int j, int rows, int cols)
{
	int result = 0;
	if (i == rows - 1 && j == cols - 1)
	{
		result = matrix[i][j];
	}
	else if (i == rows - 1)
	{
		int next = 0;
		string nextKey = to_string(i) + "_" + to_string(j+1);
		if (cache.find(nextKey) != cache.end())
		{
			next = cache[nextKey];
		}
		else
		{
			next = process2(matrix, i, j + 1, rows, cols);
		}
		result = matrix[i][j] + next;
		//result = matrix[i][j] + process2(matrix, i, j + 1, rows, cols);
	}
	else if (j == cols - 1)
	{
		int next = 0;
		string nextKey = to_string(i+1) + "_" + to_string(j);
		if (cache.find(nextKey) != cache.end())
		{
			next = cache[nextKey];
		}
		else
		{
			next = process2(matrix, i+1, j, rows, cols);
		}
		result = matrix[i][j] + next;
		//result = matrix[i][j] + process2(matrix, i + 1, j, rows, cols);
	}
	else
	{
		int rightNext = 0;
		string rightNextKey = to_string(i) + "_" + to_string(j + 1);
		if (cache.find(rightNextKey) != cache.end())
		{
			rightNext = cache[rightNextKey];
		}
		else
		{
			rightNext = process2(matrix, i, j + 1, rows, cols);
		}

		int downNext = 0;
		string downNextKey = to_string(i + 1) + "_" + to_string(j);
		if (cache.find(downNextKey) != cache.end())
		{
			downNext = cache[downNextKey];
		}
		else
		{
			downNext = process2(matrix, i + 1, j, rows, cols);
		}

		result = matrix[i][j] + std::min(rightNext,downNext);
		//result = matrix[i][j] + std::min(process2(matrix, i, j + 1, rows, cols), process2(matrix, i + 1, j, rows, cols));
	}
	string status_results = to_string(i) + "_" + to_string(j);
	cache[status_results] = result;
	return result;
}

void miniPath_Test()
{
	int matrix[][3] = { {1,3,2}, {0,3,4}, {5,7,0} };
	cout<<"�����ݹ�minipath="<<miniPath(matrix, 3, 3)<<endl;
	cout << "��̬�滮minipath=" << miniPath2(matrix, 3, 3) << endl;
}
//---------------------------------------------------------------------------
//��̬�滮����
//����һ������arr����һ������aim�������������ѡ��arr�е�����(�±�)���ܲ����ۼӵõ�aim������true����false

//�����ݹ�汾
bool process1(int arr[], int len, int i, int sum, int aim);
bool money1(int arr[], int len, int aim)
{
	return process1(arr, len,0, 0, aim);
}
bool process1(int arr[], int len, int i, int sum, int aim)
{
#if 0
	if (sum == aim)
	{
		return true;
	}
	if (i == len)
	{
		return false;
	}
#endif
	if (i == len)
	{
		return sum == aim;
	}
	return process1(arr, len, i + 1, sum, aim) || process1(arr, len, i + 1, sum + arr[i], aim);

}
//++++++++++++++++++++++
//��̬�滮�汾
bool process2(int arr[], int len, int i, int sum, int aim);
bool money2(int arr[], int len, int aim)
{
	return process2(arr, len, 0, 0, aim);
}
bool process2(int arr[], int len, int i, int sum, int aim)
{

	if (i == len)
	{
		return sum == aim;
	}
	return process2(arr, len, i + 1, sum, aim) || process2(arr, len, i + 1, sum + arr[i], aim);

}

void money_test()
{
	int arr[] = {3,2,7,8,12,7,55,9};
	cout << "�����ݹ�汾��money2=" << money2(arr, sizeof(arr) / sizeof(int),14) << endl;
}

//---------------------------------------------------------------------------
//��������--�����ݹ�汾
int process1(int weights[], int len1, int values[], int len2, int i, int weight, int bag);
int maxVaule(int weights[],int len1, int values[],int len2, int bag)
{
	if (len1 != len2)
	{
		return -1;
	}
	return process1(weights, len1, values, len2, 0,0,bag);
}

int process1(int weights[], int len1, int values[], int len2, int i,int weight,int bag)
{
	if (weight > bag)
	{
		return INT_MIN;
	}
	if (i == len1)
	{
		return 0;
	}
	return std::max(process1(weights, len1, values, len2, i + 1, weight, bag), values[i]+process1(weights, len1, values, len2, i + 1, weight + weights[i], bag));
}
//++++++++++++
//��������--��̬�滮�汾
//��̬�滮�������ɷ��Ʊ����ݹ���̣�Ҳ�������ɣ���̬�滮���Ǳ��������ݹ���м����
int maxValue2(int weights[], int len1, int values[], int len2, int bag)
{
	if (len1 != len2)
	{
		return -1;
	}
	const int len = len1;
	int **dp = new int*[len+1];
	memset(dp, 0, sizeof(dp));//��ѧϰ���ٶ�ѧϰmemset
	for (int i = len - 1; i >= 0; i--)
	{
		for (int j = bag; j >= 0; j--)
		{
			//������Ǹ��±����ݹ��е���������
			//return std::max(process1(weights, len1, values, len2, i + 1, weight, bag), values[i]+process1(weights, len1, values, len2, i + 1, weight + weights[i], bag));

			if (j + weights[i] <= bag)
			{
				dp[i][j] = std::max(dp[i][j], values[i] + dp[i + 1][j + weights[i]]);//Ҫô�����ձ�λ������λ��+weights[i]
			}
			else
			{
				dp[i][j] = dp[i + 1][j];//Ҫô�����ձ�λ������λ��
			}
		}
	}
	return dp[0][0];//�������ݹ�ĳ�ʼ״̬��
}
void maxVaule_Test()
{
	int weights[] = {3,2,4,7};
	int values[] = {5,6,3,19};
	cout << "��������-�����ݹ飬��������ֵ" << maxVaule(weights, sizeof(weights) / sizeof(int), values, sizeof(values) / sizeof(int), 11)<<endl;
	cout << "��������-��̬�滮����������ֵ" << maxVaule(weights, sizeof(weights) / sizeof(int), values, sizeof(values) / sizeof(int), 11) << endl;
}
//��ŵ������
void func(int n, string from, string mid, string to);
void Hanoi(int n)
{
	if (n > 0)
	{
		func(n, "left", "mid", "right");
	}
}
void func(int n, string from, string mid, string to)
{
	if (n == 1)
	{
		cout << "move from " << from.c_str() << " to " << to.c_str()<<endl;
	}
	else
	{
		func(n - 1, from, to, mid);
		func(1,from,mid,to);
		func(n - 1, mid, from, to);
	}
}
void Hanoi_test()
{
	Hanoi(3);
}
//---------------------------------------------------------------------------
//��ӡ�ַ��������Ӵ�
void f(string chs, int index, string pre);
void print_all_subsquences(string str)
{
	cout << "" << endl;
	f(str,0,"");

}
void f(string chs, int index, string pre)
{
	if (index == chs.length())
	{
		if (pre.compare(""))//preΪ�գ�����0�������ж�������pre��Ϊ��
		{
			cout << pre.c_str() << endl;
		}
		return;
	}
	f(chs, index + 1, pre + chs[index]);//���з�ǰ�泤����ǰ����֮��Ȼ
	f(chs, index + 1, pre);
	
}
void print_all_subsquences_test()
{
	print_all_subsquences("abc");
}
//---------------------------------------------------------------------------
//��ӡ�ַ���ȫ����-�����ظ���ĸ
void process1(string chs, int i);
void print_all_permutations1(string str)
{
	process1(str, 0);
}
void process1(string chs, int i)
{
	if (i == chs.length())
	{
		cout << chs<<endl;
	}
	for (int j = i; j < chs.length(); j++)
	{
		swap(chs, i, j);
		process1(chs, i + 1);
		swap(chs, i, j);
	}
}
//+++++++++++++++++++++++++++
//��ӡ�ַ���ȫ���� - �������ظ���ĸ
void process2(string chs, int i);
void print_all_permutations2(string str)
{
	process2(str, 0);
}
void process2(string chs, int i)
{
	if (i == chs.length())
	{
		cout << chs << endl;
	}
	hash_set<char> set;
	for (int j = i; j < chs.length(); j++)
	{
		if (set.find(chs[j]) == set.end())
		{
			set.insert(chs[j]);
			swap(chs, i, j);
			process2(chs, i + 1);
			swap(chs, i, j);
		}
	}
}

void print_all_permutations_test()
{
	print_all_permutations1("abc");
	cout << "---------------------------" << endl;
	print_all_permutations1("acc");
	cout << "---------------------------" << endl;
	print_all_permutations2("abc");
	cout << "---------------------------" << endl;
	print_all_permutations2("acc");
}
//---------------------------------------------------------------------------
//ĸţ����
int cowNumber1(int n)
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1 || n == 2 || n == 3)
	{
		return n;
	}
	return cowNumber1(n - 1) + cowNumber1(n - 3);
}
int cowNumber2(int n)
{
	if (n < 1)
	{
		return 0;
	}
	if (n == 1 || n == 2 || n == 3)
	{
		return n;
	}
	return cowNumber1(n - 1) + cowNumber1(n - 3) - cowNumber1(n - 20);
}
void cowNumber_test()
{
	cout<<"��ʼ1ͷţ��21���ĸţ����="<<cowNumber1(21)<<endl;
	cout << "��ʼ1ͷţ,ÿͷĸţ����20�꣬21���ĸţ����=" << cowNumber2(21) << endl;
}
//---------------------------------------------------------------------------
//�ݹ��������ջ--��ϰ�ݹ�(���صݹ�)+++++++++++++����ʧ��
int getAndRemoveLastElement(stack<int> *stack_);
void reverseStack(stack<int> *stack_)
{
	if (stack_->empty())
	{
		return;
	}
	int i = getAndRemoveLastElement(stack_);
	reverseStack(stack_);
	stack_->push(i);
}

int getAndRemoveLastElement(stack<int>* stack_)
{
	int result = stack_->top();
	stack_->pop();
	if (stack_->empty())
	{
		return result;
	}
	else
	{
		int last = getAndRemoveLastElement(stack_);
		stack_->push(result);
		return last;
	}
}

void reverseStack_test()
{
	stack<int>*stack_ = new stack<int>();
	stack_->push(1);
	stack_->push(2);
	stack_->push(3);
	stack_->push(4);
	reverseStack(stack_);
	while (!stack_->empty())
	{
		int res = stack_->top();
		stack_->pop();
		cout << res << endl;
	}
	//ע��ǧ��Ҫ������ķ�������Ϊstack pop��size�᲻�ϱ�С�����²���ȫ�������
	//for (int i = 0; i < stack_->size(); i++)
	//{
	//	int res = stack_->top();
	//	stack_->pop();
	//	cout << res << endl;
	//}
}
//---------------------------------------------------------------------------
//WaterProblem-class08-01
//����ⷨ��ʱ�临�Ӷ�O(Nƽ��)
int getWater1(int arr[], int len)
{
	if (arr == nullptr || len < 3)
	{
		return 0;
	}
	int value = 0;
	for (int i = 1; i < len - 1; i++)
	{
		int leftMax = 0;
		int rightMax = 0;
		for (int l = 0; l < i; l++)
		{
			leftMax = std::max(arr[l], leftMax);
		}
		for (int r = i + 1; r < len; r++)
		{
			rightMax = std::max(arr[r], rightMax);
		}
		value += std::max(0,std::min(leftMax,rightMax)-arr[i]);
	}
	return value;
}
int getWater2(int arr[], int len)
{
	if (arr == nullptr || len < 3)
	{
		return 0;
	}
	int n = len - 2;
	int *leftMaxs = new int[n];
	leftMaxs[0] = arr[0];
	for (int i = 1; i < n; i++)
	{
		leftMaxs[i] = std::max(leftMaxs[i - 1], arr[i]);
	}
	int *rightMaxs = new int[n];
	rightMaxs[n-1] = arr[n+1];
	for (int i = n - 2; i >=0; i--)
	{
		rightMaxs[i] = std::max(rightMaxs[i+1],arr[i+2]);
	}
	int value = 0;
	for (int i = 1; i <=n; i++)
	{
		value += std::max(0,std::min(leftMaxs[i-1],rightMaxs[i-1])-arr[i]);
	}
	return value;
}
int getWater3(int arr[], int len)
{
	if (arr == nullptr || len < 3)
	{
		return 0;
	}
	int value = 0;
	int leftMax = arr[0];
	int rightMax = arr[len - 1];
	int l = 1;
	int r = len - 2;
	while (l <= r)
	{
		if (leftMax <= rightMax)
		{
			value += std::max(0,leftMax-arr[l]);
			leftMax = std::max(leftMax,arr[l++]);
		}
		else
		{
			value += std::max(0, rightMax - arr[r]);
			rightMax = std::max(rightMax, arr[r--]);
		}
	}
	return value;
}
void getWater_test()
{
	int arr[] = {5,6,3,7,4,2,5};
	cout<<"ʱ�临�Ӷ�O(Nƽ��)-��ˮ��="<<getWater1(arr, sizeof(arr) / sizeof(int))<<endl;
	cout << "ʱ�临�Ӷ�O(3N)-��ˮ��=" << getWater2(arr, sizeof(arr) / sizeof(int)) << endl;
	cout << "ʱ�临�Ӷ�O(N)-��ˮ��=" << getWater3(arr, sizeof(arr) / sizeof(int)) << endl;
}
int main()
{
	
	//money_test();
	//maxVaule_Test();
	//Hanoi_test();
	//print_all_subsquences_test();
	//print_all_permutations_test();
	//cowNumber_test();
	//reverseStack_test();
	getWater_test();

	getchar();
}