#include <iostream>
#include <algorithm>
using namespace std;

#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
/*
取得(0,x)的随机整数：rand()%x；
取得(a,b)的随机整数：rand()%(b-a)；
取得[a,b)的随机整数：rand()%(b-a)+a；
取得[a,b]的随机整数：rand()%(b-a+1)+a；
取得(a,b]的随机整数：rand()%(b-a)+a+1；
取得0-1之间的浮点数：rand()/double(RAND_MAX)。
*/
void generateRandomArray(int *arr,int maxSize, int minVaule,int maxValue)
{
	for (int i = 0; i < maxSize; i++){
		arr[i] = random(minVaule, maxValue);
	}
}
void swap(int*arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;

	//	arr[i] = arr[i] ^ arr[j];
	//	arr[j] = arr[i] ^ arr[j];
	//	arr[i] = arr[i] ^ arr[j];

}
void printArray(int *arr, int len)
{

	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
void copyArray(int*dst,int*src,int len){
	//while () (*(dst++)) = (*(src++));
	memcpy(dst, src, sizeof(int) * len);
}

bool isEqual(int* arr1, int len1, int*arr2, int len2)
{
	
	if (len1 != len2||(len1==0&&len2!=0)||(len1!=0&&len2==0)){
		return false;
	}
	if (len1 == 0 && len2 == 0){
		return true;
	}
	for (int i = 0; i < len1; i++){
		if (arr1[i] != arr2[i]){
			return false;
		}
	}
	return true;
}


//----------------------------------------------------------------
//冒泡排序法
void bubbleSort(int *arr,int len)
{
	if (arr == NULL){
		return;
	}
	for (int i = len-1; i >0; i--){
		for (int j = 0; j < i; j++){
			if (arr[j]>arr[j + 1]){
				swap(arr, j, j + 1);
			}
		}
	}

}
void logarithmTest_BubbleSort()
{
	
	int size = (int)(random(6, 15));
	int *arr = new int[size];
	int *arr1 = new int[size];
	int *arr2 = new int[size];

	for (int i = 0; i < size; i++){
		arr[i] = random(1, 100);
		arr1[i] = arr[i];
		arr2[i] = arr[i];
	}

	bubbleSort(arr1, size);
	std::sort(arr2, arr2+size);
	bool succed = isEqual(arr1,size,arr2,size);

#if 1
	printArray(arr,size);
	printArray(arr1, size);
	printArray(arr2, size);
	cout << "size="<<size<<"------"<<(succed ? "Nice!" : "Fucking fucked!")<<endl;
#endif

	delete[] arr, arr1, arr2;
}
//----------------------------------------------------------------
//插入排序法第一章第一节01：44:12

void insertionSort(int *arr, int len){
	for (int i = 1; i < len; i++){
		for (int j = i - 1; j >=0 && arr[j] > arr[j + 1]; j--){
			swap(arr,j,j+1);
		}
	}
}
//----------------------------------------------------------------
//选择排序
void selectionSort(int *arr, int len){
	int minIndex = 0;
	for (int i = 0; i < len; i++){
		minIndex = i;
		for (int j = i + 1; j < len; j++){
			minIndex = arr[minIndex]<arr[j] ? minIndex : j;
		}
		swap(arr, i, minIndex);
	}
}
//----------------------------------------------------------------
//快速排序[第二章01：]
void my_partition(int*arr, int L, int R, int &lessIndex, int &moreIndex);
void quickSort(int*arr,int L,int R){
	if (L < R){
		int randNum = random(L, R - 1);
		swap(arr, randNum, R);	//以最右为参照

		int lessIndex = 0, moreIndex = 0;
		my_partition(arr, L, R, lessIndex, moreIndex);
		quickSort(arr, L, lessIndex-1);
		quickSort(arr, moreIndex + 1, R);
	}
}

//【第二章00:49】
void my_partition(int*arr, int L, int R, int &lessIndex, int &moreIndex){
	int less = L - 1;
	int more = R; //以最后一个值为划分值
	while (L < more){
		if (arr[L] < arr[R]){
			swap(arr,++less,L++);
		}
		else if (arr[L] > arr[R]){
			swap(arr,L,--more);
		}
		else{
			L++;
		}
	}
	swap(arr,more,R);
	lessIndex = less + 1;
	moreIndex = more;
}
//----------------------------------------------------------------
//归并排序
void mergeProcess(int *arr, int L,int R);
void merge(int* arr,int L,int m, int R);
void mergeSort(int*arr, int len){
	if (len < 2){
		return;
	}
	mergeProcess(arr,0,len-1);
}

void mergeProcess(int *arr, int L, int R){
	if (L == R){
		return;
	}
	int mid = L + ((R - L) >> 1);;//这里记得大括号，右移符号优先级小于“+-”
	mergeProcess(arr,L,mid);
	mergeProcess(arr, mid+1, R);
	merge(arr,L,mid,R);
}
void merge(int* arr, int L, int m, int R){
	int *help = new int[R - L + 1];
	int i = 0;
	int p1 = L;
	int p2 = m + 1;
	while (p1<=m && p2<=R){
		help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1<=m){
		help[i++] = arr[p1++];
	}
	while (p2 <= R){
		help[i++] = arr[p2++];
	}
	for (int i = 0; i < R - L + 1; i++){
		arr[L+i] = help[i];//注意这里不是arr[i]=help[i]
	}
}
//----------------------------------------------------------------
//堆排序
void heapInsert(int*arr, int index);
void heapify(int*arr, int index, int heapSize);
void heapSort(int*arr,int len){
	for (int i = 0; i < len; i++){
		heapInsert(arr, i);//生成大根堆
	}
	int heapSize = len;
	swap(arr, 0, --heapSize);
	while (heapSize > 0){
		heapify(arr, 0, heapSize);//重新调整大根堆
		swap(arr, 0, --heapSize);
		
	}
}
void heapInsert(int*arr, int index){
	while (arr[index] > arr[(index - 1) / 2]){
		swap(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void heapify(int*arr, int index, int heapSize){
	int left = index * 2 + 1;
	while (left < heapSize){
		int largest = left + 1 < heapSize && arr[left+1] > arr[left] ? left + 1:left;

		largest = arr[largest] > arr[index] ? largest : index;
		if (largest == index){
			break;
		}
		swap(arr,largest,index);
		index = largest;
		left = 2 * index + 1;
	}
	
}

//----------------------------------------------------------------
//桶排序:数组的值大于0
void bucketSort(int* arr , int len) {
	int max = *max_element(arr, arr + len);//注意arr + len而不是arr + len-1
	//int min = *min_element(arr, arr + len);
	int *bucket = new int[max + 1];
	for (int i = 0; i < max + 1; i++){
		bucket[i] = -1;
	}
	for (int i = 0; i < len; i++){
		bucket[arr[i]]++;
	}
	int i = 0;
	for (int j = 0; j < max + 1; j++){
		while (bucket[j]-->=0){
			arr[i++] = j;
		}
	}
	delete[] bucket;
}
//----------------------------------------------------------------
//比较器
class Student{
public:
	string m_name;
	int m_id;
	int m_age;
	Student();
	Student(string name, int id, int age);
	static bool cmp_id(Student&s1, Student&s2);
	static bool cmp_age(Student&s1, Student&s2);

};


Student::Student(){

}
Student::Student(string name, int id, int age){
	m_name = name;
	m_id = id;
	m_age = age;
}
bool Student::cmp_id(Student&s1, Student&s2){
	return s1.m_id < s2.m_id;
}

bool Student::cmp_age(Student&s1, Student&s2){
	return s1.m_age < s2.m_age;
}
//注意cmp_name与上面区别
bool cmp_name(Student&s1, Student&s2){    
	return s1.m_name < s2.m_name;
}

void printStudent(Student* students, int len){
	for (int i = 0; i<3; i++){
		cout << "name:" << students[i].m_name.c_str() << ",id:" << students[i].m_id << ",age:" << students[i].m_age << endl;
	}
}
//----------------------------------------------------------------

int main()
{
	srand((unsigned)time(NULL));
	int array[] = {6,4,7,1,0,5,3,2,8,9};
	int array1[] = {1,2,3};
	int array2[] = {1,2,4};

	int len1 = sizeof(array1) / sizeof(int);
	int len2 = sizeof(array2) / sizeof(int);

	int len = sizeof(array) / sizeof(int);
	printArray(array, len);
	
	//-------------------------------------------------------
	//比较器
	Student *students = new Student[3];
	Student student1("zou1", 3, 22);
	Student student2("zou2", 1, 21);
	Student student3("zou3", 2, 20);
	students[0] = student1;
	students[1] = student2;
	students[2] = student3;
	len = sizeof(students) / sizeof(Student);
	cout << "-----------id------------" << endl;
	std::sort(students,students+3,Student::cmp_id);
	printStudent(students, len);
	cout<<"-------------age----------"<<endl;
	std::sort(students,students+3,Student::cmp_age);
	printStudent(students, len);
	cout << "------------name-----------" << endl;
	std::sort(students, students + 3, cmp_name);
	printStudent(students, len);
	//-------------------------------------------------------

	printArray(array, len);

#if 0
	//----------------------------------------------------------------
	//对数器验证冒泡排序正确性
	//srand((unsigned)time(NULL));
	int i = 100;
	while (i--){
		logarithmTest_BubbleSort();
	}
	//----------------------------------------------------------------
	//产生随机数组
	int randomArray[10];
	generateRandomArray(randomArray,10,1,1000);
	printArray(randomArray,10);
	//----------------------------------------------------------------
	//复制数组
	int *copy_array = new int[len];
	copyArray(copy_array, array,len);
	printArray(copy_array, len);
	//----------------------------------------------------------------
	bubbleSort(array, len);//冒泡排序法
	insertionSort(array, len);//插入排序
	selectionSort(array, len);//选择排序
	heapSort(array, len);//堆排序
	mergeSort(array, len);//归并排序
	quickSort(array, 0, len - 1);//快速排序
	bucketSort(array,len);//桶排序
	//----------------------------------------------------------------
	//比较器
	Student *students = new Student[3];
	Student student1("zou1",3,22);
	Student student2("zou2", 1, 21);
	Student student3("zou3", 2, 20);
	students[0] = student1;
	students[1] = student2;
	students[2] = student3;
	len = sizeof(students) / sizeof(Student);
	cout << "-----------id------------" << endl;
	std::sort(students,students+3,Student::cmp_id);
	printStudent(students, len);
	cout<<"-------------age----------"<<endl;
	std::sort(students,students+3,Student::cmp_age);
	printStudent(students, len);
	cout << "------------name-----------" << endl;
	std::sort(students, students + 3, cmp_name);
	printStudent(students, len);
#endif

	

	getchar();
}