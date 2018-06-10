#include <iostream>
#include <algorithm>
using namespace std;

void printArray(int *arr, int len)
{

	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
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
//-------------------------------------------------------
//归并排序应用:最小和
int mergeProcess(int *arr, int L, int R);
int merge(int* arr, int L, int m, int R);
int mergeSort(int*arr, int len){
	if (len < 2){
		return 0;
	}
	return mergeProcess(arr, 0, len - 1);
}

int mergeProcess(int *arr, int L, int R){
	if (L == R){
		return 0;
	}
	int mid = L + ((R - L) >> 1);;//这里记得大括号，右移符号优先级小于“+-”
	//mergeProcess(arr, L, mid);
	//mergeProcess(arr, mid + 1, R);
	//merge(arr, L, mid, R);
	return mergeProcess(arr, L, mid) + mergeProcess(arr, mid + 1, R) + merge(arr, L, mid, R);
}
int merge(int* arr, int L, int m, int R){
	int *help = new int[R - L + 1];
	int i = 0;
	int p1 = L;
	int p2 = m + 1;
	int res = 0;
	while (p1 <= m && p2 <= R){
		res += arr[p1] < arr[p2] ? (R - p2 + 1)*arr[p1] : 0;
		help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= m){
		help[i++] = arr[p1++];
	}
	while (p2 <= R){
		help[i++] = arr[p2++];
	}
	for (int i = 0; i < R - L + 1; i++){
		arr[L + i] = help[i];//注意这里不是arr[i]=help[i]
	}
	return res;
}
//-------------------------------------------------------
//荷兰国旗

void my_partition(int*arr, int L, int R, int p, int &lessIndex, int &moreIndex){
	int less = L - 1;
	int more = R + 1; //以最后一个值为划分值
	while (L < more){
		if (arr[L] < p){
			swap(arr, ++less, L++);
		}
		else if (arr[L] > p){
			swap(arr, L, --more);
		}
		else{
			L++;
		}
	}
	swap(arr, more, R);
	lessIndex = less + 1;
	moreIndex = more - 1;
}
//-------------------------------------------------------
//桶排序应用：数组内所有数都为long,要求时间复杂度O(N),排序后最大间隙
int bucket(long num, long len, long min, long max);
int maxGap(int*arr,int len){
	if (len < 2){
		cout << "len<2" << endl;
		return 0;
	}
	int min = *min_element(arr,arr+len);
	int max = *max_element(arr, arr + len);
	//cout << "min=" << min << ",max=" << max<<endl;
	if (min == max){
		cout << "min=max" << endl;
		return 0;
	}
	bool *hasNum = new bool[len+1];

	int  *maxs = new int[len + 1];
	int  *mins = new int[len + 1];
	for (int i = 0; i < len + 1; i++){
		hasNum[i] = false;   //注意这里需要初始化
		//mins[i] = -1;
		//maxs[i] = -1;
	}
	int bid = 0;
	for (int i = 0; i < len; i++){
		bid = bucket(arr[i], len, min, max);//分配到哪个桶
		mins[bid] = hasNum[bid] ? std::min(mins[bid], arr[i]) : arr[i];
		maxs[bid] = hasNum[bid] ? std::max(mins[bid], arr[i]) : arr[i];
		hasNum[bid] = true;
	}
	int res = 0;
	int lastMax = maxs[0];
	for (int i = 1; i <=len; i++){
		if (hasNum[i]){
			res = std::max(res, mins[i] - lastMax);
			lastMax = maxs[i];
		}
	}
	return res;
}
int bucket(long num,long len,long min,long max){
	return (int)((num - min)*len / (max - min));
}
//-------------------------------------------------------
int main()
{
	//int array[] = { 6, 4, 7, 1, 9, 5, 3, 2, 0, 8 ,1};
	int array[] = { 5,1,0,9,18,11,6,3,12};
	int len = sizeof(array) / sizeof(int);

	int maxGap_value = maxGap(array, len);
	cout << "maxGap_value=" << maxGap_value<<endl;
	printArray(array, len);
#if 0
	//-------------------------------------------------------
	//最小和问题
	int smallSum=mergeSort(array,len);
	printArray(array, len);
	cout << "smallSum=" << smallSum<<endl;
	//-------------------------------------------------------
	//荷兰国旗
	int lessIndex=0, moreIndex=0;
	my_partition(array,0,len-1,1,lessIndex,moreIndex);
	cout << "lessIndex=" << lessIndex << " moreIndex=" << moreIndex << endl;
#endif
	getchar();
}