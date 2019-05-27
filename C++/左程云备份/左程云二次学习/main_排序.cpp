#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>



using namespace std;
#define BUFF_LEN 100

//----------------说明-----------------------

/*冒泡排序：时间复杂度O(N2)、空间复杂度O(N)
插入排序：将一个数据插入到已经排好序的有序数据中，从而得到一个新的、个数加一的有序数据，算法适用于少量数据的排序。

*/
void test()
{
	int i;
	int j;
}

//----------------基础函数-----------------------

//交换数组中的两个位置的字符
void swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
//产生随机数
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
/*
rand()它会返回一个从0到最大随机数的任意整数

取得(0,x)的随机整数：rand()%x；
取得(a,b)的随机整数：rand()%(b-a)；
取得[a,b)的随机整数：rand()%(b-a)+a；
取得[a,b]的随机整数：rand()%(b-a+1)+a；
取得(a,b]的随机整数：rand()%(b-a)+a+1；
取得0-1之间的浮点数：rand()/double(RAND_MAX)。
*/

//打印矩阵
void printArray(int *arr, int len)
{
	if (arr == nullptr || len < 1)
	{
		return;
	}
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
//STL中的排序
void STL_Sort_test()
{
	int arr[] = { 4, 3, 5, 9, 6, 5, 9, 9 };
	int len = sizeof(arr) / sizeof(int);
	std::sort(arr, arr + len);
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//冒泡排序：时间复杂度O(N2)、空间复杂度O(N)
void bubbleSort(int *arr, int len)
{
	if (arr == nullptr || len == 0)
	{
		return;
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				swap(arr, j, j + 1);
			}
		}
	}
}
void bubbleSort_test()
{
	int arr1[] = { 4, 3, 5, 9, 6, 5, 9, 9 };
	int *arr2 = nullptr;
	bubbleSort(arr1, sizeof(arr1) / sizeof(int));
	bubbleSort(arr2, sizeof(arr2) / sizeof(int));
	for (int i = 0; i < sizeof(arr1) / sizeof(int); ++i)
	{
		cout << arr1[i] << " ";
	}
}

//插入排序
void insertionSort(int *arr, int len)
{
	if (arr == nullptr || len <= 0)
	{
		return;
	}
	for (int i = 1; i < len; i++)
	{
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)  //理解for循环终止调节
		{
			swap(arr, j, j + 1);
		}
	}
}
void insertionSort_test()
{
	int arr1[] = { 4, 3, 5, 9, 6, 5, 9, 9 };
	int *arr2 = nullptr;
	insertionSort(arr1, sizeof(arr1) / sizeof(int));
	insertionSort(arr2, sizeof(arr2) / sizeof(int));

	for (int i = 0; i < sizeof(arr1) / sizeof(int); ++i)
	{
		cout << arr1[i] << " ";
	}
}

//选择排序
void selectionSort(int *arr, int len)
{
	if (arr == nullptr || len <= 0)
	{
		return;
	}
	int minIndex = 0;
	for (int i = 0; i < len - 1; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < len; j++)
		{
			minIndex = arr[minIndex]>arr[j] ? j : minIndex;
		}
		swap(arr, minIndex, i);
	}
}
void selectionSort_test()
{
	int arr1[] = { 4, 3, 5, 9, 6, 5, 9, 9 };
	int *arr2 = nullptr;
	selectionSort(arr1, sizeof(arr1) / sizeof(int));
	selectionSort(arr2, sizeof(arr2) / sizeof(int));

	for (int i = 0; i < sizeof(arr1) / sizeof(int); ++i)
	{
		cout << arr1[i] << " ";
	}
}

//快速排序
void partition(int *arr, int L, int R, int &lessIndex, int &moreIndex)
{
	int less = L - 1;
	int more = R;
	while (L < more)
	{
		if (arr[L] < arr[R])
		{
			swap(arr, ++less, L++);
		}
		else if (arr[L] > arr[R])
		{
			swap(arr, L, --more);
		}
		else
		{
			L++;
		}
	}
	swap(arr, R, more);
	lessIndex = less + 1;
	moreIndex = more;
}

void quickSort(int *arr, int len, int L, int R)
{
	if (arr == nullptr || L<0 || L>len - 1 || L > R || R > len - 1)
	{
		return;
	}
	//cout << "L=" << L << "R=" << R << endl;
	int randNum = random(L, R);
	//cout << "randNum=" << randNum << endl;
	swap(arr, randNum, R);
	int lessIndex = 0, moreIndex = 0;

	partition(arr, L, R, lessIndex, moreIndex);
	quickSort(arr, len, L, lessIndex - 1);
	quickSort(arr, len, moreIndex + 1, R);


}

void quickSort_test()
{
	int arr[] = { 1, 4, 3, 9, 4, 3, 4, 6, 9, 8, 8, 10 };
	int len = sizeof(arr) / sizeof(int);
	quickSort(arr, len, 0, len - 1);
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//荷兰国旗--Partition思想应用
void netherlandsFlag_Partition(int *arr, int L, int R, int p, int &lessIndex, int &moreIndex)
{
	int less = L - 1;
	int more = R;  //以最后一个值为划分值
	while (L < more)
	{
		if (arr[L] < p)
		{
			swap(arr, ++less, L++);
		}
		else if (arr[L] > arr[R])
		{
			swap(arr, L, --more);
		}
		else
		{
			L++;
		}
	}
	swap(arr, R, more);
	lessIndex = less + 1;
	moreIndex = more;
}

void netherlandsFlag_test()
{
	int arr1[] = { 1, 0, 1, 2, 2, 0, 2, 2, 0, 1 };
	int arr2[] = { 1, 0, 2, 7, 6, 5 };

	int lessIndex = -1, moreIndex = -1;
	netherlandsFlag_Partition(arr1, 0, sizeof(arr1) / sizeof(int) - 1, 1, lessIndex, moreIndex);
	cout << "lessIndex=" << lessIndex << ",moreIndex=" << moreIndex << endl;
	for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;

	netherlandsFlag_Partition(arr2, 0, sizeof(arr2) / sizeof(int) - 1, 5, lessIndex, moreIndex);
	cout << "lessIndex=" << lessIndex << ",moreIndex=" << moreIndex << endl;
	for (int i = 0; i < sizeof(arr2) / sizeof(int); i++)
	{
		cout << arr2[i] << " ";
	}
	cout << endl;

}

//归并排序
void merge(int *arr, int L, int mid, int R)
{
	int *help = new int[R-L+ 1];
	int p1 = L;
	int p2 = mid + 1;
	int i = 0;
	while (p1 <= mid&&p2 <= R)
	{
		help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= mid)
	{
		help[i++] = arr[p1++];
	}
	while (p2 <= R)
	{
		help[i++] = arr[p2++];
	}
	for (int i = 0; i <R-L + 1; i++)
	{
		arr[L + i] = help[i];
	}
}
void mergeProcess(int *arr, int L, int R)
{
	if (L == R)
	{
		return;
	}
	int mid = L + ((R-L) >> 1);
	mergeProcess(arr, L, mid);
	mergeProcess(arr, mid + 1, R);
	merge(arr, L, mid, R);
}
void mergeSort(int *arr, int len)
{
	if (arr == nullptr || len < 2)
	{
		return;
	}
	mergeProcess(arr, 0,len-1);
}
void mergeSor_test()
{
	int arr1[] = { 1, 0, 1, 2, 2, 0, 2, 2, 0, 1 };

	mergeSort(arr1, sizeof(arr1) / sizeof(int));
	for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
}


//归并应用-求小和
int merge2(int*arr,int L,int mid,int R)
{
	int *help = new int[R - L + 1];
	int p1 = L;
	int p2 = mid + 1;
	int i = 0;
	int res = 0;
	while (p1 <= mid&&p2 <= R)
	{
		res += arr[p1] < arr[p2] ?arr[p1]*(R-p2+1) : 0;
		help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= mid)
	{
		help[i++] = arr[p1++] ;
	}
	while (p2 <= R)
	{
		help[i++] = arr[p2++];
	}
	for (int i = 0; i < R - L + 1; i++)
	{
		arr[L + i] = help[i];
	}
	return res;
}
int mergeProcess2(int *arr,int L,int R)
{
	//递归的终止条件一定要记得加
	if (L == R)
	{
		return 0;
	}
	int mid = L + ((R - L) >> 1);
	return mergeProcess2(arr, L, mid)+mergeProcess2(arr, mid+1, R)+merge2(arr,L,mid,R);
}
int smallSum(int *arr, int len)
{
	if (arr == nullptr || len < 2)
	{
		throw exception("无效输入参数");
	}
	mergeProcess2(arr, 0, len - 1);
}

void smallSum_test()
{
	int array[] = { 4, 1, 3, 5, 0, 6 };
	int len = sizeof(array) / sizeof(int);
	try
	{
		cout << "最小和=" << smallSum(array, len) << endl;
		cout << "最小和=" << smallSum(nullptr, len) << endl;
	}
	catch (exception &e)
	{
		cout << "error" << e.what() << endl;;
	}
	printArray(array, len);
}


//堆排序
void heapInsert(int *arr,int index)
{
	while (arr[index] > arr[(index - 1) / 2])
	{
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void heapify(int *arr, int heapSize,int index)
{
	int left = 2 * index + 1;
	while (left < heapSize-1)
	{
		int lartgest = left + 1 < heapSize - 1 && arr[left] < arr[left + 1] ? left + 1 : left;
		if (arr[lartgest] == arr[index]) //后面的数全是一样
		{
			break;
		}
		swap(arr, lartgest, index);
		index = lartgest;
		left = 2 * index + 1;
	}
}
void heapSort(int *arr, int len)
{
	if (arr == nullptr || len < 2)
	{
		return;
	}
	for (int i = 0; i < len; i++)
	{
		heapInsert(arr, i);
	}
	int heapSize = len;
	swap(arr, 0, --heapSize);
	while (heapSize > 0)
	{
		heapify(arr,heapSize, 0);
		swap(arr, 0, --heapSize);
	}
}
void heapSort_test()
{
	int arr1[] = { 1, 0, 1, 2, 2, 0, 2, 2, 0, 1 };

	heapSort(arr1, sizeof(arr1) / sizeof(int));
	for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
}


//桶排序--也称计数排序

//经典实例：范围[0~200]的数, 几亿个数
void buckSort(int *arr, int len)
{
	if (arr == nullptr || len < 2)
	{
		return;
	}
	int max = *max_element(arr, arr + len);
	int *bucket = new int[max + 1];
	memset(bucket, 0, sizeof(int)*(max + 1));
	for (int i = 0; i < len; ++i)
	{
		bucket[arr[i]]++;
	}
	int j = 0;
	for (int i = 0; i < max + 1; i++)
	{
		while (bucket[i]--)
		{
			arr[j++] = i;
		}
	}
	delete[] bucket;
}
void buckSort_test()
{
	int arr1[] = { 1, 0, 1, 2, 2, 0, 2, 2, 0, 1 ,6,3,9,5,10,8,8,6};
	buckSort(arr1, sizeof(arr1) / sizeof(int));
	for (int i = 0; i < sizeof(arr1) / sizeof(int); i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
}

//桶排序--无序数组排序后相邻数最大差值，时间复杂度O(N)，数组内所有数都为long
int bucket(int len,long num, long min,long max)
{
	return int ((num - min)*1.0 / (max - min)*len);
}
long maxGap(long*arr, int len)
{
	if (arr == nullptr || len < 2)
	{
		throw exception("无效输入");
	}
	long min = *min_element(arr, arr + len);
	long max = *max_element(arr, arr + len);

	if (min == max)//记得加这里：如果全部相等，直接返回
	{
		return 0;
	}
	long *mins = new long[len+1];//记得这里，是len+1
	long *maxs = new long[len+1];
	bool *hasNum = new bool[len + 1];
	memset(hasNum, 0, sizeof(bool)*(len + 1));

	//把原数组中所有的数装进桶
	for (int i = 0; i < len; i++)
	{
		int bid = bucket(len, arr[i], min, max);
		//if (!hasNum[bid])
		//{
		//	mins[bid] = arr[i];
		//	maxs[bid] = arr[i];
		//}
		//else
		//{
		//	mins[bid] = arr[i] < mins[bid] ? arr[i] : mins[bid];
		//	maxs[bid] = arr[i] > maxs[bid] ? arr[i] : maxs[bid];
		//}
		mins[bid] = hasNum[bid] ? std::min(mins[bid], arr[i]) : arr[i];
		maxs[bid] = hasNum[bid] ? std::max(maxs[bid], arr[i]) : arr[i];
		hasNum[bid] = true;
	}
	
	long lastMax = maxs[0];
	long maxGap = 0;
	bool isPreNull = false;

	for (int i = 1; i < len + 1; i++)
	{
		if (hasNum[i])
		{
			maxGap = std::max(maxGap, mins[i] - lastMax);
			lastMax = maxs[i];
		}
	}
	return maxGap;

#if 0
  //不能通过所有测试案例
	//for (int i = 0; i < len + 1; i++)
	//{
	//	cout << "mins=" << mins[i] << "maxs=" << maxs[i] << "hasNum[i]=" << hasNum[i] << endl;
	//}
	for (int i=1; i < len+1; i++)
	{
		if (!hasNum[i] )
		{
			if (!isPreNull)
			{	
				lastMax = maxs[i - 1];
			}
			isPreNull = true;
		}
		else
		{
			if (isPreNull)
			{
				maxGap = std::max(maxGap, mins[i] - lastMax);
			}
			isPreNull = false;
		}

	}
	return maxGap;
#endif
}

void maxGap_test()
{
	//long arr[] = { 1L, 2L, 5L, 4L, 6L };//输出2
	//long arr[] = { 9L, 3L, 1L, 10L };//输出6
	long arr[] = { 0L,12L,25L,38L,39L,51L,62L,77L,78L };//输出
	cout << "maxGap=" << maxGap(arr, sizeof(arr) / sizeof(long)) << endl;
}
//输出数组arr2不在有序数组arr1中的数[二分法查找]
void printNumArray(int *sortedArray, int len1,int *arr,int len2, vector<int>&num)
{
	if (sortedArray == nullptr || arr == nullptr || len1 < 0 || len2 < 1)
	{
		return;
	}
	
	for (int i = 0; i < len2; i++)
	{
		int L = 0;
		int R = len1 - 1;
		bool isContain = false;
		while (L <= R)  //注意这里执行条件不是L<R
		{
			int mid = L + ((R - L) >> 1);
			if (sortedArray[mid] == arr[i])
			{
				isContain = true;
				break;
			}
			else if (sortedArray[mid] < arr[i])
			{
				L = mid + 1;
			}
			else
			{
				R = mid - 1;
			}
		}
		
		if (!isContain)
		{
			num.push_back(arr[i]);
		}
	}
}
void printNumArray_test()
{
	int sortedArray[] = { 1, 3, 7, 9, 10, 22, 32, 56, 68, 88, 99, 100 };
	int array[] = { 3,2, 22,5, 56,5, 99,6,66};
	vector<int> printNum;
	printNumArray(sortedArray, sizeof(sortedArray) / sizeof(int), array, sizeof(array) / sizeof(int), printNum);
	for (int i = 0; i < printNum.size(); i++)
	{
		cout << printNum.at(i) << " ";
	}
	cout << endl;
}

//比较器使用--不稳定排序
class Student
{
public:
	Student(){};
	Student(string name, int id, int age)
	{
		this->name = name;
		this->id = id;
		this->age = age;
	}
	string name;
    int age;
	int id;
	static bool cmp_name(const Student&s1, const Student&s2){ return s1.name < s2.name; }
	static bool cmp_id_increase(const Student&s1, const Student&s2){ return s1.id < s2.id; }
	static bool cmp_id_decrease(const Student&s1, const Student&s2){ return s1.id > s2.id; }
	static bool cmp_age(const Student&s1, const Student&s2){ return s1.age < s2.age; }
};
void printStudent(const Student &student)
{
	cout << "name=" << student.name << ", id=" << student.id <<", age="<<student.age<< endl;
}
void compare_test()
{
	Student *students = new Student[6];
	
	students[0] = Student("zou1", 3, 22);
	students[1] = Student("zou2", 1, 25);
	students[2] = Student("zou3", 2, 20);

	students[3] = Student("zou6", 1, 20);
	students[4] = Student("zou5", 1, 20);
	students[5] = Student("zou4", 1, 20);

	int len = 6;
	cout << "----------------------cmp_name-------------------------" << endl;
	std::sort(students, students + 6, Student::cmp_name);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}
	cout << "----------------------不稳定cmp_id_increase-------------------------" << endl;
	std::sort(students, students + 6, Student::cmp_id_increase);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}
	cout << "----------------------不稳定cmp_id_decrease-------------------------" << endl;
	std::sort(students, students + 6, Student::cmp_id_decrease);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}
	cout << "----------------------cmp_age-------------------------" << endl;
	std::sort(students, students + 6, Student::cmp_age);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}
	cout << "----------------------稳定cmp_id_increase-------------------------" << endl;
	std::stable_sort(students, students + 6, Student::cmp_name);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}
	cout << "---------------------------------------" << endl;
	std::stable_sort(students, students + 6, Student::cmp_id_increase);
	for (int i = 0; i < len; i++)
	{
		printStudent(students[i]);
	}

	delete[]students;
	students = nullptr;
}
int main()
{
	srand((int)time(0));//随机数种子

	//STL_Sort_test();

	//bubbleSort_test();//冒泡排序
	//insertionSort_test();//插入排序
	//selectionSort_test();//选择排序

	//netherlandsFlag_test();//荷兰国旗问题
	//quickSort_test();//快速排序
	//mergeSor_test();//归并排序
	//heapSort_test();//堆排序
	//buckSort_test();//桶排序
	///maxGap_test();//桶排序应用--邻近最小距离
	//smallSum_test();//归并应用--求小和问题
	//printNumArray_test();//输出数组arr2不在有序数组arr1中的数
	
	compare_test();//比较器使用
	getchar();
}