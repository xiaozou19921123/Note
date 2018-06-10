#include <iostream>
#include <algorithm>
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
//using namespace std;
using std::cout;
//----------------------------------------------------------------
//自定义抛出异常
#include <sstream>  
using namespace std;
typedef unsigned long uint32_t;
class Exception {
private:
	string opt_info;
	const char * const err_info;
	const char * const throw_file;
	uint32_t throw_line;
	const char * const throw_func;
public:
	Exception(const char * const info = 0, const char * const throw_file = "", uint32_t throw_line = 0, const char * const throw_func = "") :err_info(info), throw_file(throw_file), throw_line(throw_line), throw_func(throw_func){}
	string info(){
		stringstream strStream;
		strStream << throw_line;
		opt_info = string(err_info) + " File: " + throw_file + "; Line: " + strStream.str() + "; Function: " + throw_func;
		return opt_info;
	}
};
void throwException(const char* info){
	throw Exception(info, __FILE__, __LINE__, __FUNCTION__);
}
//-----------------------------------------------------------------
//数组实现栈
class ArrayStack{
public:
	ArrayStack(int initSize);
	~ArrayStack();

	int peek();
	void push(int obj);
	int pop();

private:
	int *arr;
	int size;
	int len;
	
};
ArrayStack::~ArrayStack(){
	delete[]arr;
}
ArrayStack::ArrayStack(int initSize){
	try{
		if (initSize< 0){
			throwException("The init size is less than 0");
		}
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	arr = new int[initSize];
	len = initSize - 1;
	size = 0;
}

int ArrayStack::peek(){
	try{
		if (size == 0){
			throwException("The queue is empty");
		}
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return arr[size-1];		
}

void ArrayStack::push(int obj){
	try{
		//cout << "into push" << endl;
		if (size==len){
			throwException("The queue is full");
		}
		//cout << "The queue is not full!!!" << endl;
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}

	arr[size++] = obj;
}

int ArrayStack::pop(){
	try{
		if (size == 0){
			throwException("The queue is empty");
		}
		return arr[--size];
	}catch(Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
		return -10000000;
	}
	
}

//-----------------------------------------------------------------
class ArrayQueue{
public:
	ArrayQueue(int iniSize);
	~ArrayQueue();

	int peek();
	void push(int obj);
	int pop();

private:
	int *arr;
	int size;
	int len;
	int first;
	int last;
};


ArrayQueue::ArrayQueue(int iniSize){
	if (iniSize == 0) {
		std::cerr<<"iniSize == 0";
	}
	arr = new int[iniSize];
	len = iniSize;
	size = 0;
	first = 0;
	last = 0;
}
ArrayQueue::~ArrayQueue(){
	delete[] arr;
}

int ArrayQueue::peek()
{
	if (size == 0){
		cerr << "size==0";
	}
	return arr[first];
}

void ArrayQueue::push(int obj){
	if (size == len) {
		cerr << "the queue is full";
		return;
	}
	size++;
	arr[last] = obj;
	last = last==len-1 ? 0 : last+1;
}

int ArrayQueue::pop(){
	try{
		if (size == 0){
			throwException("The queue is empty");
		}
		size--;
		int temp = first;
		first = first == len - 1 ? 0 : first + 1;
		return arr[temp];
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
		return -1000000;
	}
}
//-----------------------------------------------------------------
//获取最小栈
//实现一个特殊栈，在实现栈的基本功能的基础上，再实现返回栈中最小元素的操作O(1)

#include<stack>

class GetMinStack{
public:
	GetMinStack();
	~GetMinStack();

	void push(int newNum);
	int pop();
	int getMin();

private:
	stack<int> *stackData;
	stack<int> *stackMin;

};
GetMinStack::GetMinStack(){
	stackData = new stack<int>();
	stackMin = new stack<int>();
}
GetMinStack::~GetMinStack(){
	delete stackData, stackMin;
}
void GetMinStack::push(int newNum){
	if (stackMin->empty()){
		stackMin->push(newNum);
	}else if(newNum<=getMin()){
		stackMin->push(newNum);
	}
	else{
		stackMin->push(getMin());
	}
	stackData->push(newNum);
}

int GetMinStack::pop(){
	try{
		if (stackData->empty()){
			throwException("The stack_stackData is empty");
		}
		int popValue = stackData->top();
		stackData->pop();
		stackMin->pop();

		return popValue;
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return -10000;
}
int GetMinStack::getMin(){
	try{
		if (stackMin->empty()){
			throwException("The stack_stackMin is empty");
		}
		return stackMin->top();
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return -10000;
}
//-----------------------------------------------------------------
//两个栈实现队列
#include<stack>
class Stacks2Queue{
public:
	Stacks2Queue();
	~Stacks2Queue();
	void push(int obj);
	int pop();
	int peek();

private:
	stack<int> *stackPush, *stackPop;

 };

Stacks2Queue::Stacks2Queue(){
	stackPush = new stack<int>();
	stackPop = new stack<int>();

}

void Stacks2Queue::push(int obj){
	stackPush->push(obj);
}
int Stacks2Queue::pop(){
	try{
		if (stackPop->empty() && stackPush->empty()){
			throwException("Quenue is empty");
		}else if (stackPop->empty()){
			while (!stackPush->empty()){
				int temp = stackPush->top();
				stackPop->push(temp);
				stackPush->pop();
			}
		}
		int temp = stackPop->top();
		stackPop->pop();
		return temp;
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return -10000;
}
int Stacks2Queue::peek(){
	try{
		if (stackPop->empty() && stackPush->empty()){
			throwException("Quenue is empty");
		}else if (stackPop->empty()){
			while (!stackPush->empty()){
				int temp = stackPush->top();
				stackPop->push(temp);
				stackPush->pop();
			}
		}
		return stackPop->top();
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return -10000;
}
Stacks2Queue::~Stacks2Queue(){
	delete[]stackPush, stackPop;
}
//-----------------------------------------------------------------
//两个队列实现一个栈
#include<queue>
class Queue2Stack{
public:
	Queue2Stack();
	void push(int obj);
	int pop();
	int top();
	void swap();
private:
	queue<int>*my_queue, *help;
};
Queue2Stack::Queue2Stack(){
	my_queue = new queue<int>();
	help = new queue<int>();
}

void Queue2Stack::push(int obj){
	my_queue->push(obj);
}

int Queue2Stack::pop(){
	try{
		if (my_queue->empty()){
			throwException("Stack is empty");
		}
		while (my_queue->size() != 1){
			int temp = my_queue->front();
			help->push(temp);
			my_queue->pop();
		}
		int res = my_queue->front();
		my_queue->pop();
		swap();
		return res;
	}
	catch (Exception ex){
		cerr << "Catch Exception : " << ex.info() << endl;
	}
	return -100000;
}

void Queue2Stack::swap(){
	queue<int> *temp;
	temp = my_queue;
	my_queue=help;
	help = temp;

}
//-----------------------------------------------------------------
//猫狗队列
class Pet{
public:
	string getPetType();
//private:
	string type;
};
string Pet::getPetType(){
	return type;
};


class Dog :public Pet{
public:
	Dog();
//private:
//	string type;
};

Dog::Dog(){
	type = "dog";
}
class Cat :public Pet{
public:
	Cat();
//private:
//	string type;
};
Cat::Cat(){
	type = "cat";
}
class PetEnterQueue{
public:
	PetEnterQueue(Pet pet,long count);
	Pet getPet();
	long getCount();
	string getPetType();

private:
	Pet m_pet;
	long m_count;
};

PetEnterQueue::PetEnterQueue(Pet pet, long count){
	m_pet = pet;
	m_count = count;
}
Pet PetEnterQueue::getPet(){
	return m_pet;
}
long PetEnterQueue::getCount(){
	return m_count;
}
string PetEnterQueue::getPetType(){
	return m_pet.getPetType();
}
class DogCatQueue{
public:
	DogCatQueue();
	void add(Pet&pet);
	void popAll();
	void popDog();
	void popCat();
	bool isEmpty();
	bool isDogEmpty();
	bool isCatEmpty();


private:
	queue<PetEnterQueue> *dogQ, *catQ;
	long count;
};

bool DogCatQueue::isEmpty(){
	cout << "isEmpty--" << (dogQ->empty() || catQ->empty())<<endl;
	return dogQ->empty() || catQ->empty();
}
bool DogCatQueue::isDogEmpty(){
	cout << "isDogEmpty--" << (dogQ->empty())<<endl;
	return dogQ->empty();
}
bool DogCatQueue::isCatEmpty(){
	cout << "isCatEmpty--" << (catQ->empty()) << endl;
	return catQ->empty();
}
DogCatQueue::DogCatQueue(){
	dogQ = new queue<PetEnterQueue>();
	catQ = new queue<PetEnterQueue>();
	count = 0;
}
void DogCatQueue::add(Pet&pet){
	if (pet.getPetType() == "dog"){
		PetEnterQueue *petEnterQueue = new PetEnterQueue(pet, count++);
		dogQ->push(*petEnterQueue);
		delete petEnterQueue;
	}else if (pet.getPetType() == "cat"){
		PetEnterQueue *petEnterQueue = new PetEnterQueue(pet, count++);
		catQ->push(*petEnterQueue);
		delete petEnterQueue;
	}else{
		cerr<<"err, not dog or cat";
	}
}
void DogCatQueue::popAll(){
	if (dogQ->empty() && catQ->empty()){
		cerr << "the Queue is empty!";
	}
	while (!dogQ->empty() || !catQ->empty()){
		if (!dogQ->empty() && !catQ->empty()){
			if (dogQ->front().getCount() < catQ->front().getCount()){
				cout << "popALL:" << dogQ->front().getPetType() << "-pet-" << dogQ->front().getCount() << endl;
				dogQ->pop();
			}
			else{
				cout << "popALL:" << catQ->front().getPetType() << "-pet-" << catQ->front().getCount() << endl;
				catQ->pop();
			}
		}else if (!dogQ->empty()){
			cout << "popALL:" << dogQ->front().getPetType() << "-pet-" << dogQ->front().getCount() << endl;
			dogQ->pop();
		}else if (!catQ->empty()){
			cout << "popALL:" << catQ->front().getPetType() << "-pet-" << catQ->front().getCount() << endl;
			catQ->pop();
		}
		count--;
	}
	
}
void DogCatQueue::popDog(){
	if (dogQ->empty()){
		cerr << "dogQ is empty()";
	}
	while (!dogQ->empty()){
		cout << dogQ->front().getPetType() << "---" << dogQ->front().getCount()<<endl;
		dogQ->pop();
	}
}
void DogCatQueue::popCat(){
	if (catQ->empty()){
		cerr << "catQ is empty()";
	}
	while (!catQ->empty()){
		cout << catQ->front().getPetType() << "---" << catQ->front().getCount() << endl;
		catQ->pop();
	}
}
//-----------------------------------------------------------------
//hash_map
/*
hash_map是一个聚合类，它继承自_Hash类，包括一个vector，一个list和一个pair，
其中vector用于保存桶，list用于进行冲突处理，pair用于保存key->value结构，简要地伪码如下：
class hash_map<class _Tkey, class _Tval>
{
private:
typedef pair<_Tkey, _Tval> hash_pair;
typedef list<hash_pair>    hash_list;
typedef vector<hash_list>  hash_table;
};
*/
#include<hash_map>
typedef pair < const char*, float > mk_pair;
void hash_map_operation(){
	hash_map<const char*, float> hm;
	hm["apple"] = 1.0f;
	hm["pear"] = 1.5f;
	hm["orange"] = 2.0f;
	hm["banana"] = 1.8f;
	hm.insert(mk_pair("mago", 2.8));

	char str[] = { "zou" };
	hm[str] = 66.6f;

	cout << "hm.count=" << hm.count("banana1") << endl;
	hash_map<const char*, float>::iterator i, iend, j;
	iend = hm.end();

	//hm.erase("pear");//删除元素

	for (i = hm.begin(); i != iend; i++){
		cout << "hm: " << (*i).first << "--" << (*i).second << endl;
	}
	//元素搜索
	i = hm.find("pear");
	cout << "水果：" << (*i).first << ",价钱：" << (*i).second << endl;
	j = hm.find("pear");
	if (j != hm.end()){
		cout << "hash_map容器个数" << hm.size() << endl;
	}
	else{
		cout << "哈希表的表长：" << hm.bucket_count() << endl;
	}
}
//-----------------------------------------------------------------
//hashmap应用：设计RandomPlool结构
//typedef int T;
template<typename T>
class Pool{
public:
	Pool();
	~Pool();
	void insert(T key);
	void deleteT(T key);
	T getRandom();
	
private:
	hash_map<T, int>keyIndexMap;
	hash_map<int, T>indexKeyMap;
	int size;
};

template<typename T>
Pool<T>::~Pool(){
	//delete keyIndexMap, indexKeyMap;
}

template<typename T>
Pool<T>::Pool(){
	//keyIndexMap = new hash_map<int, int>();
	//indexKeyMap = new hash_map<int, int>();
	size = 0;
}

template<typename T>
void Pool<T>::insert(T key){
	if (!keyIndexMap.count(key)){
		keyIndexMap[key] = size;
		indexKeyMap[++size] = key;
	}
}

template<typename T>
void Pool<T>::deleteT(T key){
	if (keyIndexMap.count(key)){
		int deleteIndex = keyIndexMap[key];
		int lastIndex = --size;
		T lastKey = indexKeyMap[key];
		keyIndexMap[lastKey] = deleteIndex;
		indexKeyMap[deleteIndex] = lastKey;
		keyIndexMap.erase(key);
		indexKeyMap.erase(deleteIndex);
	}
}

template<typename T>
T Pool<T>::getRandom(){
	if (size == 0){
		cerr << "Pool size is empty";
	}
	int randomIndex = random(1, size - 1);
	return indexKeyMap[randomIndex];
}
void randomPoolTest(){
	srand((unsigned)time(NULL));
	Pool<int> pool;
	pool.insert(10);
	pool.insert(20);
	pool.insert(30);
	pool.insert(40);
	pool.insert(100);
	pool.insert(110);
	pool.insert(120);

	int i = 10;
	while (i--)
		cout << "pool.getRandom()=" << pool.getRandom() << endl;

	Pool<string> pool1;//Pool<const char*> pool1;
	pool1.insert("zou1");
	pool1.insert("zou2");
	pool1.insert("zou3");
	pool1.insert("zou10");
	pool1.insert("zou20");
	pool1.insert("zou30");
	pool1.insert("zou100");
	pool1.insert("zou110");
	pool1.insert("zou120");
	i = 10;
	while (i--)
		cout << "pool.getRandom()=" << pool1.getRandom() << endl;
}
//------------------------------------------------------------
//二维数组螺旋打印
void printEdge(int matrix[][3], int tR, int tC, int dR, int dC);
void spiralOrderPrint(int matrix[][3], int rows, int cols){
	int tR = 0;
	int tC = 0;
	int dR = rows - 1;
	int dC = cols - 1;
	while (tR <= dR&&tC <= dC){
		printEdge(matrix, tR++, tC++, dR--, dC--);
	}
}

void printEdge(int matrix[][3], int tR, int tC, int dR, int dC){
	if (tR == dR){
		for (int i = tC; i <= dC; i++){
			cout << matrix[tR][i] << " ";
		}
	}
	else if (tC == dC){
		for (int i = tR; i <= dR; i++){
			cout << matrix[i][tC];
		}
	}
	else{
		int curC = tC;
		int curR = tR;
		while (curC != dC){
			cout << matrix[tR][curC++] << " ";
		}
		while (curR != dR){
			cout << matrix[curR++][dC] << " ";
		}
		while (curC != tC){
			cout << matrix[dR][curC--] << " ";
		}
		while (curR != tR){
			cout << matrix[curR--][tC] << " ";
		}
	}
}
//------------------------------------------------------------
//二维数组“之”字形打印

void printLevel(int matrix[][3], int tR, int tC, int dR, int dC, bool fromUp);
void printMatrixZigZag(int matrix[][3], int rows, int cols){
	int tR = 0, tC = 0, dR = 0, dC = 0;
	int endR = rows - 1;
	int endC = cols - 1;
	bool fromUp = false;
	while (tR != endR + 1){
		printLevel(matrix, tR, tC, dR, dC, fromUp);
		tR = tC == endC ? tR + 1 : tR;
		tC = tC == endC ? tC : tC + 1;
		dC = dR == endR ? dC + 1 : dC;
		dR = dR == endR ? dR : dR + 1;
		fromUp = !fromUp;
	}
}
void printLevel(int matrix[][3], int tR, int tC, int dR, int dC, bool fromUp){
	if (fromUp){
		while (tR != dR + 1){
			cout << matrix[tR++][tC--]<<" ";
		}
	}else {
		while (dR != tR - 1){
			cout << matrix[dR--][dC++] << " ";
		}
	}
}
//-----------------------------------------------------------
//在行列都拍好序的矩阵中找数
bool isContainsInSortedMatrix(int matrix[][3], int rows, int cols,int K){
	int tR = 0;
	int tC = cols - 1;
	while (tR<rows && tC>-1){
		if (matrix[tR][tC] == K){
			return true;
		}else if (matrix[tR][tC] > K){
			tC--;
		}else{
			tR++;
		}
	}
	return false;
}
//-----------------------------------------------------------
//打印两个有序链表公共部分

struct Node{
	int data;
	
	Node *next;
	Node *rand;
	Node *front;

	Node *left;
	Node *right;

	Node *parent;

	Node(int value) :data(value){};
	Node(){};
};

void printCommonPart(Node *head1,Node *head2){
	while (head1 != NULL&&head2 != NULL){
		if (head1->data < head2->data){
			head1 = head1->next;
		}else if (head1->data > head2->data){
			head2 = head2->next;
		}else{
			cout << head1->data;
			head1 = head1->next;
			head2 = head2->next;
		}
	}
}
void printNodes(Node *node){
	while (node->next != nullptr){
		cout << node->data<<" ";
		node = node->next;
	}
	cout << node->data << " ";
	cout << endl;
}


//-----------------------------------------------------------
//判断是否为回文结构1:额外空间复杂度O(N)
bool isPalindrome1(Node *head){
	if (head == nullptr || head->next == nullptr){
		return true;
	}
	std::stack<Node*> *stacks = new std::stack<Node*>();
	Node *cur = head;
	while (cur != nullptr){
		stacks->push(cur);
		cur=cur->next;
	}
	while (head != nullptr){

		if (head->data != stacks->top()->data){
			return false;
		}
		stacks->pop();
		head = head->next;
	}
	return true;
}
//判断是否为回文结构2:额外空间复杂度O(N/2)
bool isPalindrome2(Node *head){
	if (head == nullptr || head->next == nullptr){
		return true;
	}
	Node *right = head->next;//记得这里需要next
	Node *cur = head;
	while (cur->next != nullptr&&cur->next->next != nullptr){
		right = right->next;//指向中间
		cur = cur->next->next;
	}

	std::stack<Node*> *stacks = new std::stack<Node*>();
	while (right->next != nullptr){  //中间后面的指针压入栈
		stacks->push(right);
		//cout << right->data << endl;
		right = right->next;
	}
	stacks->push(right);   //注意这里最后尾部记得压入栈
	while (!stacks->empty()){
		//---cout << head->data<<"----" << stacks->top()->data << endl;
		if (head->data != stacks->top()->data){
			return false;
		}
		head = head->next;
		stacks->pop();
	}
	return true;
}
//判断是否为回文结构3:额外空间复杂度O(1)
bool isPalindrome3(Node *head){
	if (head == nullptr || head->next == nullptr){
		return true;
	}
	Node *n1 = head;
	Node *n2 = head;
	while (n2->next != nullptr&&n2->next->next != nullptr){  
		n1 = n1->next;        //n1->mid
		n2 = n2->next->next;  //n2->end
	}
	n2 = n1->next;        // n2 -> right part first node
	n1->next = nullptr;
	Node*n3;
	while (n2 != nullptr){
		n3 = n2->next;
		n2->next = n1;
		n1 = n2;
		n2 = n3;
	}
	//printNodes(n1);
	n3 = n1;
	n2 = head;
	//printNodes(head);
	bool res = true;
	while (n1 != nullptr&&n2 != nullptr){
		if (n1->data != n2->data){
			res= false;
			break;
		}
		n1 = n1->next;
		n2 = n2->next;
	}
	n1 = n3->next;
	n3->next = nullptr;
	
	while (n1 != nullptr) { // recover list
		n2 = n1->next;
		n1->next = n3;
		n3 = n1;
		n1 = n2;
	}
	return res;
}
//-----------------------------------------------------------
//链表排序：两种方法--将单向链表按某值划分左边小，中间相等，右边大形式
void arrPartition(Node**nodeArr, int len, int pivot);
void swapNode(Node**nodeArr, int a, int b);
Node* nodePartition1(Node*head, int pivot){   //归并排序中的partition
	if (head == nullptr){
		return head;
	}
	Node *cur = head;
	int len = 0;
	while (cur != nullptr){
		len++;
		cur = cur->next;
	}
	Node**nodeArr = new Node*[len];
	cur = head;
	for (int i = 0; i < len; i++){
		nodeArr[i] = cur;
		cur = cur->next;
	}
	arrPartition(nodeArr, len,pivot);
	for (int i = 1; i < len; i++){
		nodeArr[i-1]->next = nodeArr[i];
	}
	nodeArr[len-1]->next = nullptr;
	return nodeArr[0];
}

Node* nodePartition2(Node*head, int pivot){   //归并排序中的partition
	Node* sH = nullptr;//small head
	Node* sT = nullptr;//small tail
	Node* eH = nullptr;
	Node* eT = nullptr;
	Node* bH = nullptr;
	Node* bT = nullptr;
	Node*next = nullptr;
	while (head != nullptr){
		next = head->next;
		head->next = nullptr;
		if (head->data < pivot){
			if (sH == nullptr){
				sH = head;
				sT = head;
			}else{
				sT->next = head;
				sT = head;
			}
		}else if (head->data == pivot){
			if (eH == nullptr){
				eH = head;
				eT = head;
			}
			else{
				eT->next = head;
				eT = head;
			}
		}else{
			if (bH == nullptr){
				bH = head;
				bT = head;
			}
			else{
				bT->next = head;
				bT = head;
			}
		}
		head = next;
	}
	if (sT != nullptr){
		sT->next = eH;
		eT = eT == nullptr ? sT : eT;
	}
	if (eT != nullptr){
		eT->next = bH;
	}
	return sH != nullptr ? sH : eH != nullptr ? eH : bH;
}
void arrPartition(Node**nodeArr,int len ,int pivot){
	int small = -1;
	int big = len;
	int index = 0;
	while (index != big){
		if (nodeArr[index]->data < pivot){
			swapNode(nodeArr, ++small, index++);
		}else if (nodeArr[index]->data == pivot){
			index++;
		}else{
			swapNode(nodeArr, --big, index);
		}
	}

}
void swapNode(Node**nodeArr, int a, int b){
	Node temp = *nodeArr[a];
	*nodeArr[a] = *nodeArr[b];
	*nodeArr[b] = temp;
}
//-----------------------------------------------------------
//两种深度复制链表：
Node*copyNodesWithRand1(Node*head){   //使用hashMap
	if (head == nullptr){
		return head;
	}
	hash_map<Node*,Node*>map;
	Node*cur = head;
	while (cur != nullptr){
		map[cur] = new Node(cur->data);
		cur = cur->next;
	}
	cur = head;
	while (cur != nullptr){
		map[cur]->next = cur->next;
		map[cur]->rand = cur->rand;
		cur = cur->next;
	}
	return map[head];
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
Node* copyNodesWithRand2(Node*head){  
	if (head == nullptr){
		return nullptr;
	}
	Node*cur = head;
	Node*next = nullptr;
	// copy node and link to every node
	while (cur != nullptr){
		next = cur->next;
		cur->next = new Node(cur->data);
		cur->next->next = next;
		cur = next;
	}
	cur = head;
	Node*curCopy = nullptr;
	// set copy node rand
	while (cur != nullptr){
		next = cur->next->next;
		curCopy = cur->next;
		curCopy->rand = cur->rand != nullptr ? cur->rand->next : nullptr;
		cur = next;
	}
	Node *res = head->next;
	cur = head;
	// split
	while (cur != nullptr){
		next = cur->next->next;
		curCopy = cur->next;
		curCopy->next = next;
		curCopy->next = next != nullptr ? next->next : nullptr;
		cur = next;
	}
	return res;

}
//-----------------------------------------------------------
//获取两个单链表（有环或者无环）
Node*getLoopNode(Node*head);
Node*noLoop(Node*head1, Node*head2);
Node*bothLoop(Node*head1,Node*loop1, Node*head2,Node*loop2);
Node*getIntersectNode(Node*head1, Node*head2){
	if (head1 == nullptr || head2 == nullptr){
		return nullptr;
	}
	Node* loop1 = getLoopNode(head1);
	Node* loop2 = getLoopNode(head2);
	
	if (loop1 == nullptr&&loop2 == nullptr){
		return noLoop(head1,head2);
	}
	else if (loop1 != nullptr&&loop2 != nullptr){
		//cout << "loop=" << loop1->data << "-----" << loop2->data;
		return bothLoop(head1,loop1,head2,loop2);
	}
	return nullptr;
}
Node*noLoop(Node*head1, Node*head2){
	if (head1 == nullptr || head2 == nullptr){
		return nullptr;
	}
	Node*cur1 = head1;
	Node*cur2 = head2;
	int n = 0;
	while (cur1->next != nullptr){
		n++;
		cur1 = cur1->next;
	}
	while (cur2->next != nullptr){
		n--;
		cur2 = cur2->next;
	}
	if (cur1 != cur2){
		return nullptr;
	}
	cur1 = n > 0 ? head1 : head2;          //回到长链的首部
	cur2 = cur1 == head1 ? head2 : head1;  //回到短链的首部
	n = std::abs(n);

	while (n != 0){				//长链先多走几步
		n--;
		cur1 = cur1->next;
	}

	while (cur1 != cur2){      //一起走
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;

}
Node*bothLoop(Node*head1, Node*loop1, Node*head2, Node*loop2){
	Node*cur1=nullptr;
	Node*cur2=nullptr;
	if (loop1 == loop2){
		cur1 = head1;
		cur2 = head2;
		int n = 0;
		while (cur1!= loop1){
			n++;
			cur1 = cur1->next;
		}
		while (cur2!= loop2){
			n--;
			cur2 = cur2->next;
		}
		cur1 = n > 0 ? head1 : head2;
		cur2 = cur1 == head1 ? head2 : head1;
		n = std::abs(n);//n=n>0?n:-n;
		while (n != 0){
			n--;
			cur1 = cur1->next;
		}
		while (cur1 != cur2){
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;
	}else{
		cur1 = loop1->next;
		while (cur1 != loop1){
			if (cur1 == loop2){
				return loop1;
			}
			cur1 = cur1->next;
		}
		return nullptr;
	}
}
Node*getLoopNode(Node*head){
	if (head == nullptr || head->next == nullptr || head->next->next == nullptr){
		return nullptr;
	}
	Node *n1 = head->next;//n1->slow
	Node *n2 = head->next->next;//n2->fast
	while (n1 != n2){
		if (n2->next == nullptr || n2->next->next == nullptr){
			return nullptr;
		}
		n2 = n2->next->next;
		n1 = n1->next;
	}
	n2 = head;//n2回到头部
	while (n1 != n2){
		n1 = n1->next;
		n2 = n2->next;
	}
	return n1;
}

//----------------------------------------------------------
//优先队列应用：随时找到数据流的中位数
#include<functional>
class MedianHolder{
public:
	void modifyTwoHeapSize();
	void addNewNum(int newNum);
	double getMedian();
private:
	priority_queue<int> *maxHeap = new priority_queue<int>(); //默认排序由大到小
	priority_queue < int, vector<int>, greater<int> >*minHeap = new priority_queue < int, vector<int>, greater<int> >();

};
double MedianHolder::getMedian(){

	int maxHeapSize = maxHeap->size();
	int minHeapSize = minHeap->size();
	if (minHeapSize + maxHeapSize == 0){
		return 0;
	}
	
	if (((minHeapSize + maxHeapSize) & 1) == 0){  //位运算级别比==低，记得加括号
		return ((double)minHeap->top()+maxHeap->top())/2;
	}
	return maxHeapSize > minHeapSize ? maxHeap->top() : minHeap->top();
}
void MedianHolder::addNewNum(int newNum){

	if (maxHeap->empty()){
		maxHeap->push(newNum);
		return;
	}
	if (newNum<=maxHeap->top()){
		maxHeap->push(newNum);
	}else{
		if (minHeap->empty()){
			minHeap->push(newNum);
			return;
		}
		if (newNum>=minHeap->top()){
			minHeap->push(newNum);
		}
		else{
			maxHeap->push(newNum);
		}
	}

	modifyTwoHeapSize();

}

void MedianHolder::modifyTwoHeapSize(){
	if (maxHeap->size() == minHeap->size() + 2){
		int temp = maxHeap->top();
		minHeap->push(temp);
		maxHeap->pop();
		
	}
	if (minHeap->size() == maxHeap->size() + 2){
		int temp = minHeap->top();
		maxHeap->push(temp);
		minHeap->pop();
		
	}
}
//-----------------------------------------------------------
//优先队列应用：最小铜板消耗
int lessMoney(int *arr,int len){
	priority_queue < int, vector<int>, greater<int> >*pQ = new priority_queue < int, vector<int>, greater<int> >();
	for (int i = 0; i < len; i++){
		pQ->push(arr[i]);
	}
	int sum = 0;
	int cur = 0;
	while (pQ->size()!=1){
		int temp1 = pQ->top();
		pQ->pop();
		int temp2 = pQ->top();
		pQ->pop();
		cur = temp1 + temp2;
		sum += cur;
		pQ->push(cur);
	}
	return sum;
}
//-----------------------------------------------------------
//优先队列应用（自定义比较器）：项目挣钱最大化
struct Node2{
	int p;
	int c;
	Node2(){};
	Node2(int profit, int cost) :p(profit), c(cost){};
};

//由大到小排
struct cmp_min_p{
	bool operator()(Node2& n1, Node2& n2)const{
		return n1.p > n2.p;
	}
};

//由小到大排
struct cmp_max_c{     
	bool operator()(Node2& n1, Node2& n2)const{
		return n1.c < n2.c;
	}
};
//W--为初始资金，k——最多交易次数（串行）;len——总共有多少交易
int findMaximizedCapital(int k, int W, int*profits, int *costs, int len){
	Node2 *nodes = new Node2[len];
	for (int i = 0; i < len; i++){
		nodes[i] = Node2(profits[i], costs[i]);
	}
	priority_queue<Node2, vector<Node2>, cmp_min_p>*minCostQ = new priority_queue<Node2, vector<Node2>, cmp_min_p>();
	priority_queue<Node2, vector<Node2>, cmp_max_c>*maxProfitQ = new priority_queue<Node2, vector<Node2>, cmp_max_c>();

	for (int i = 0; i < len; i++){
		minCostQ->push(nodes[i]);
	}

	for (int i = 0; i < k; i++){
		while (!minCostQ->empty() && minCostQ->top().c <= W){
			cout << "到这里了吗" << endl;
			maxProfitQ->push(minCostQ->top());
			minCostQ->pop();
		}
		if (maxProfitQ->empty()){
			cout << "没有" << endl;
			return W;
		}

		W += maxProfitQ->top().p;
		maxProfitQ->pop();
	}
	delete[]nodes;
	return W;
}
//-----------------------------------------------------------
//二叉树前序、中序、后序遍历（递归和非递归实现）
class PreInPosTraversal{
public:
	void preOrderRecur(Node*head);
	void preOrderUnRecur(Node*head);

	void inOrderRecur(Node*head);
	void inOrderUnRecur(Node*head);

	void posOrderRecur(Node*head);
	void posOrderUnRecur(Node*head);
	void posOrderUnRecur2(Node*head);
};

//递归版本
void PreInPosTraversal::preOrderRecur(Node*head){
	if (head == nullptr){
		return;
	}
	cout << head->data<<" ";
	preOrderRecur(head->left);
	preOrderRecur(head->right);
}

void PreInPosTraversal::inOrderRecur(Node*head){
	if (head == nullptr){
		return;
	}
	inOrderRecur(head->left);
	cout << head->data << " ";
	inOrderRecur(head->right);
}

void PreInPosTraversal::posOrderRecur(Node*head){
	if (head == nullptr){
		return;
	}
	posOrderRecur(head->left);
	posOrderRecur(head->right);
	cout << head->data << " ";
}

//非递归版本
void PreInPosTraversal::preOrderUnRecur(Node*head){
	cout << "pre-order-unRecur: "<<endl;
	if (head != nullptr){
		std::stack<Node*> *stacks = new std::stack<Node*>();
		stacks->push(head);
		while (!stacks->empty()){
			head = stacks->top();
			stacks->pop();
			cout << head->data << " ";
			if (head->right != nullptr){
				stacks->push(head->right);
			}
			if (head->left != nullptr){
				stacks->push(head->left);
			}
		}
	}
	cout << endl;
}
void PreInPosTraversal::inOrderUnRecur(Node*head){
	cout << "in-order-unRecur: " << endl;
	if (head != nullptr){
		stack<Node*>*stacks = new stack<Node*>();
		while (!stacks->empty() || head != nullptr){
			if (head != nullptr){
				stacks->push(head);
				head = head->left;
			}
			else{
				head = stacks->top();
				stacks->pop();
				cout << head->data << " ";
				head=head->right;
			}
		}
	}
	cout << endl;
}
//代码类似先序遍历（中左右）
//后序遍历（左右中）：先中右左，在左右中
void PreInPosTraversal::posOrderUnRecur(Node*head){
	cout << "pos-order-unRecur: " << endl;
	if (head!=nullptr){
		stack<Node*>*s1 = new stack<Node*>();
		stack<Node*>*s2 = new stack<Node*>();
		s1->push(head);
		while (!s1->empty()){
			head = s1->top();
			s1->pop();
			s2->push(head);
			if (head->left != nullptr){
				s1->push(head->left);
			}
			if (head->right != nullptr){
				s1->push(head->right);
			}
		}
		while (!s2->empty()){
			cout << s2->top()->data << " ";
			s2->pop();
		}
	}
	cout << endl;
}

void PreInPosTraversal::posOrderUnRecur2(Node*h){
	cout << "pos-order-unRecur2: " << endl;
	if (h != nullptr){
		stack<Node*>*stacks = new stack<Node*>();
		stacks->push(h);
		Node*c = nullptr;
		while (!stacks->empty()){
			c = stacks->top();
			if (c->left != nullptr&&h != c->left&&h != c->right){
				stacks->push(c->left);
			}
			else if (c->right != nullptr&&h != c->right){
				stacks->push(c->right);
			}
			else{
				cout << stacks->top()->data << " ";
				stacks->pop();
				h = c;
			}
		}
		cout << endl;
	}
}
//-----------------------------------------------------------
//打印二叉树
//"v"——左下方找父节点
//"^"——左上方找父节点
void pritnInOrder(Node*head, int height, string to, int len);
string getSpace(int num);
void printNodeTree(Node*head){
	pritnInOrder(head, 0, "H", 17);
}
void pritnInOrder(Node*head, int height, string to, int len){
	if (head == nullptr){
		return;
	}
	pritnInOrder(head->right, height + 1, "v", len);
	string val = to + to_string(head->data) + to;
	int lenM = val.length();
	int lenL = (len - lenM) / 2;
	int lenR = len - lenM - lenL;
	val = getSpace(lenL) + val + getSpace(lenR);
	cout << getSpace(height*len) + val << endl;
	pritnInOrder(head->left, height + 1, "^", len);
}
string getSpace(int num){
	string space = " ";
	for (int i = 0; i < num; i++){
		space.append(" ");
	}
	return space;
}

//-----------------------------------------------------------
//二叉树应用：折纸问题（中序遍历）
void printProcess(int i, int N, bool down);
Node*getLeftMost(Node *node);
void printAllFolds(int N){
	printProcess(1, N, true);
}
//i为当前所在层、down——当前为下（折纸凹处）
void printProcess(int i, int N, bool down){
	if (i > N){
		return;
	}
	printProcess(i + 1, N, true);
	cout << (down ? "down" : "up") << " ";
	printProcess(i + 1, N, false);
}
//-----------------------------------------------------------
//找到二叉树的后继节点(中序遍历应用)
Node *getNextNode(Node*node){
	if (node == nullptr){
		return node;
	}
	if (node->right != nullptr){
		return getLeftMost(node->right);
	}
	else{
		Node*parent = node->parent;
		while (parent != nullptr&&parent->left != node){
			node = parent;
			parent = node->parent;
		}
		return parent;
	}

}
Node*getLeftMost(Node *node){
	if (node == nullptr){
		return node;
	}
	while (node->left != nullptr){
		node = node->left;
	}
	return node;
}
//-----------------------------------------------------------
//并查集class4_09
class DisJointSets{
public:
	hash_map<Node*, Node*> fatherMap;
	hash_map<Node*, int> rankMap;

	void makeSets(list<Node*> nodes);//初始化
	Node* findFather(Node *n);
	bool isSameSet(Node *a, Node *b);
	void unionSets(Node * a, Node *b);
	void printFather(Node *a);
};


void DisJointSets::makeSets(list<Node*> nodes)
{
	//初始化：每个元素各自独立成为自己集合
	fatherMap.clear();
	rankMap.clear();
	for (auto node : nodes)
	{
		fatherMap[node] = node;
		rankMap[node] = 1;
	}
}

Node* DisJointSets::findFather(Node *n)
{
	Node* father = fatherMap[n];
	if (father!=n)
	{
		father = findFather(father);
	}
	fatherMap[n] = father;
	return father;
}

bool DisJointSets::isSameSet(Node *a, Node *b)
{
	return findFather(a) == findFather(b);
}

void DisJointSets::unionSets(Node*a, Node*b)
{
	if (a == nullptr || b == nullptr)
	{
		return;
	}
	Node *aFather = findFather(a);
	Node *bFather = findFather(b);
	if (aFather != bFather)
	{
		int aSize = rankMap[aFather];
		int bSize = rankMap[bFather];
		if (aSize <= bSize)
		{
			fatherMap[aFather] = bFather;
			rankMap[bFather] = aSize + bSize;
		}
		else
		{
			fatherMap[bFather] = aFather;
			rankMap[aFather] = aSize + bSize;
		}
	}
}

void DisJointSets::printFather(Node *a)
{
	Node *father = findFather(a);
	std::cout << "father=" << father->data<<std::endl;
}
void DisJointSetsTest()
{
	Node*node1 = new Node(1);
	Node*node2 = new Node(2);
	Node*node3 = new Node(3);
	Node*node4 = new Node(4);
	Node*node5 = new Node(5);

	list<Node*> nodes;
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);
	nodes.push_back(node5);

	DisJointSets disJointSets;
	disJointSets.makeSets(nodes);

	for (auto node : nodes)
	{
		disJointSets.printFather(node);
	}

	disJointSets.unionSets(node1, node2);
	disJointSets.unionSets(node2, node3);

	for (auto node : nodes)
	{
		disJointSets.printFather(node);
	}
}

//-----------------------------------------------------------
int main()
{
	DisJointSetsTest();


#if 0
	Node*head = new Node(5);
	head->parent = nullptr; //head-parent-nullptr
	head->left=new Node(3);
	head->left->parent = head;  //3-parent-5
	head->right=new Node(8);
	head->right->parent = head; //8-parnet-5
	head->left->left=new Node(2);
	head->left->left->parent = head->left;//2-parent-3
	head->left->right=new Node(4);
	head->left->right->parent = head->left;//4-parent-3
	head->left->right->left = nullptr;
	head->left->right->right = nullptr;
	head->left->left->left=new Node(1);
	head->left->left->left->parent = head->left->left;//1-parent-2
	head->left->left->right = nullptr;
	head->left->left->left->left = nullptr;
	head->left->left->left->right = nullptr;

	head->right->left=new Node(7);
	head->right->left->parent = head->right;//7-parent-8
	head->right->left->left=new Node(6);
	head->right->left->left->parent = head->right->left;//6-parent-7
	head->right->left->right = nullptr;
	head->right->left->left->left = nullptr;
	head->right->left->left->right = nullptr;
	head->right->right=new Node(10);
	head->right->right->parent = head->right;//10-parent-8
	head->right->right->left=new Node(9);
	head->right->right->left->parent = head->right->right;//9-parent-10
	head->right->right->left->left = nullptr;
	head->right->right->left->right = nullptr;
	head->right->right->right=new Node(11);
	head->right->right->right->parent=head->right->right;//11-parent-10;
	head->right->right->right->left = nullptr;
	head->right->right->right->right = nullptr;
	printNodeTree(head);
#endif

#if 0
		//-----------------------------------------------------------------
		//数组实现栈
		int iniSize = 10;
		ArrayStack arrayStack(iniSize);
		arrayStack.push(1);
		cout << "push=" << 1 << endl;
		arrayStack.push(2);
		cout << "push=" << 2 << endl;
		arrayStack.push(3);
		cout << "push=" << 3 << endl;
		cout << "------pop=" << arrayStack.pop() << endl;
		cout << "------pop=" << arrayStack.pop() << endl;

		arrayStack.push(4);
		cout << "push=" << 4 << endl;
		arrayStack.push(5);
		cout << "push=" << 5 << endl;

		cout << "------pop=" << arrayStack.pop() << endl;
		cout << "------pop=" << arrayStack.pop() << endl;
		cout << "------pop=" << arrayStack.pop() << endl;
		cout << "------pop=" << arrayStack.pop() << endl;
		//-----------------------------------------------------------------
		//数组实现队列
		int iniSize = 10;
		ArrayQueue arrayQueue(iniSize);
		arrayQueue.push(1);
		cout << "push=" << 1 << endl;
		arrayQueue.push(2);
		cout << "push=" << 2 << endl;
		arrayQueue.push(3);
		cout << "push=" << 3 << endl;
		cout << "------pop=" << arrayQueue.pop() << endl;
		cout << "------pop=" << arrayQueue.pop() << endl;

		arrayQueue.push(4);
		cout << "push=" << 4 << endl;
		arrayQueue.push(5);
		cout << "push=" << 5 << endl;

		cout << "------pop=" << arrayQueue.pop() << endl;
		cout << "------pop=" << arrayQueue.pop() << endl;
		cout << "------pop=" << arrayQueue.pop() << endl;
		cout << "------pop=" << arrayQueue.pop() << endl;
		//-------------------------------------------------------------
		//获取最小栈
		GetMinStack stack;
		stack.push(3);
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.push(5);
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.push(2);
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.push(9);
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.push(1);
		cout << "stack.getMin=" << stack.getMin() << endl;
		cout << "----------------------------------" << endl;
		stack.pop();
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.pop();
		cout << "stack.getMin=" << stack.getMin() << endl;
		stack.pop();
		cout << "stack.getMin=" << stack.getMin() << endl;
		//----------------------------------------------------------------
		//两个栈实现队列
		Stacks2Queue stacks2Queue;
		stacks2Queue.push(1);
		stacks2Queue.push(2);
		stacks2Queue.push(3);
		cout << "------pop=" << stacks2Queue.pop() << endl;
		stacks2Queue.push(4);
		cout << "------pop=" << stacks2Queue.pop() << endl;
		stacks2Queue.push(5);
		cout << "------pop=" << stacks2Queue.pop() << endl;
		cout << "------pop=" << stacks2Queue.pop() << endl;
		cout << "------pop=" << stacks2Queue.pop() << endl;
		//----------------------------------------------------------------
		//两个队列实现栈
		Queue2Stack queue2Stack;
		queue2Stack.push(1);
		queue2Stack.push(2);
		queue2Stack.push(3);
		cout << "------pop=" << queue2Stack.pop() << endl;
		queue2Stack.push(4);
		cout << "------pop=" << queue2Stack.pop() << endl;
		queue2Stack.push(5);
		cout << "------pop=" << queue2Stack.pop() << endl;
		cout << "------pop=" << queue2Stack.pop() << endl;
		cout << "------pop=" << queue2Stack.pop() << endl;
		//-------------------------------------------------------
		//猫狗队列
		/*Dog dog;
		cout << "----"<<dog.getPetType()<<endl;*/
		DogCatQueue *dogCatQueue=new DogCatQueue();
		Dog dog1,dog2,dog3,dog4;// 0 1 3 5
		Cat cat1,cat2,cat3,cat4;// 2 4 6 7
		dogCatQueue->add(dog1); //0
		dogCatQueue->add(dog2); //1
		dogCatQueue->add(cat1); //2
		dogCatQueue->add(dog3); //3
		dogCatQueue->add(cat2); //4
		dogCatQueue->add(dog4); //5
		dogCatQueue->add(cat3); //6
		dogCatQueue->add(cat4); //7

#if 0
		dogCatQueue->popAll();
#else
		dogCatQueue->isDogEmpty();
		dogCatQueue->popDog();
		dogCatQueue->isDogEmpty();
		dogCatQueue->isCatEmpty();
		dogCatQueue->popCat();
		dogCatQueue->isCatEmpty();
#endif
		//-------------------------------------------------------------
		//hash_map
		hash_map_operation();
		randomPoolTest();//hashmap应用：设计RandomPlool结构
		//-------------------------------------------------------------
		//二维数组螺旋输出
		int matrix[][3]={{1,2,3},{4,5,6},{7,8,9}};
		spiralOrderPrint(matrix,3,3);
		//--------------------------------------------------------------
		//
		int matrix[][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
		printMatrixZigZag(matrix, 3, 3);
		//--------------------------------------------------------------
		//二维数组“之”字形打印
		int matrix[][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
		printMatrixZigZag
			//--------------------------------------------------------------
			//在行列都拍好序的矩阵中找数
			int matrix[][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
		cout << "isContains=" << isContainsInSortedMatrix(matrix, 3, 3, 4);
		//--------------------------------------------------------------
		//打印两个有序链表公共部分
		Node *node1=new Node(2);
		node1->next=new Node(3);
		node1->next->next=new Node(5);
		node1->next->next->next=new Node(6);
		node1->next->next->next->next = nullptr;

		Node *node2=new Node(1);
		node2->next=new Node(2);
		node2->next->next=new Node(5);
		node2->next->next->next=new Node(7);
		node2->next->next->next=new Node(6);
		node2->next->next->next->next=new Node(8);
		node2->next->next->next->next->next = nullptr;
		printNodes(node1);
		printNodes(node2);
		printCommonPart(node1, node2);
		//--------------------------------------------------------------
		//判断是否为回文结构
		Node *node1 = new Node(2);
		node1->next = new Node(3);
		node1->next->next=new Node(3);
		node1->next->next->next=new Node(2);
		node1->next->next->next->next = new Node(1);
		node1->next->next->next->next->next = nullptr;
		cout << "是否为回文结构1=" << isPalindrome1(node1) << endl;
		cout << "是否为回文结构2=" << isPalindrome2(node1) << endl;
		cout << "是否为回文结构3=" << isPalindrome3(node1) << endl;
		//--------------------------------------------------------------
		//链表排序
		Node *node1 = new Node(2);
		node1->next = new Node(3);
		node1->next->next = new Node(3);
		node1->next->next->next = new Node(2);
		node1->next->next->next->next = new Node(1);
		node1->next->next->next->next->next = nullptr;
		printNodes(node1);
		//Node* node_partition = nodePartition1(node1,2);
		Node* node_partition = nodePartition2(node1, 2);
		printNodes(node_partition);
		//--------------------------------------------------------------
		//获取两个单链表（有环或者无环）
		// 1->2->3->4->5->6->7->null
		Node *head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);
		head1->next->next->next->next->next->next->next = nullptr;

		// 0->9->8->6->7->null
		Node *head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		cout << "应该输出6：-------" << getIntersectNode(head1,head2)->data<<endl;

		// 1->2->3->4->5->6->7->4->->->
		head1 = new Node(1);
		head1->next = new Node(2);
		head1->next->next = new Node(3);
		head1->next->next->next = new Node(4);
		head1->next->next->next->next = new Node(5);
		head1->next->next->next->next->next = new Node(6);
		head1->next->next->next->next->next->next = new Node(7);
		head1->next->next->next->next->next->next->next = head1->next->next->next; // 7->4

		// 0->9->8->2->->->
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next; // 8->2
		cout << "应该输出2：-------" << getIntersectNode(head1, head2)->data << endl;

		// 0->9->8->6->4->5->6->->
		head2 = new Node(0);
		head2->next = new Node(9);
		head2->next->next = new Node(8);
		head2->next->next->next = head1->next->next->next->next->next; // 8->6
		cout << "应该输出4：-------" << getIntersectNode(head1, head2)->data << endl;
		//--------------------------------------------------------------
		//优先队列应用：随时找到数据流的中位数
		MedianHolder *medianHolder = new MedianHolder();
		int array[] = { 6, 3, 9, 5, 8, 7 };
		int len = sizeof(array) / sizeof(int);
		for (int i = 0; i<len; i++){
			medianHolder->addNewNum(array[i]);
		}

		cout << "中位数为：" << medianHolder->getMedian() << endl;
		delete medianHolder;
		//--------------------------------------------------------------
		//优先队列应用：最小铜板消耗
		int array[] = { 10, 30, 20 };
		int len = sizeof(array) / sizeof(int);
		cout << "less money=" << lessMoney(array, len);
		//--------------------------------------------------------------
		//优先队列应用（自定义比较器）：项目挣钱最大化
		int costs[] = { 15, 10, 25, 20 };
		int profits[] = { 25, 20, 40, 30 };
		int len = sizeof(profits) / sizeof(int);
		cout << "findMaximizedCapital=" << findMaximizedCapital(2, 20, profits, costs, len);
		//--------------------------------------------------------------
		//二叉树前序、中序、后序遍历（递归和非递归实现）
		Node*head=new Node(5);
		head->left=new Node(3);
		head->right=new Node(8);
		head->left->left=new Node(2);
		head->left->right=new Node(4);
		head->left->right->left = nullptr;
		head->left->right->right = nullptr;
		head->left->left->left=new Node(1);
		head->left->left->right = nullptr;
		head->left->left->left->left = nullptr;
		head->left->left->left->right = nullptr;

		head->right->left=new Node(7);
		head->right->left->left=new Node(6);
		head->right->left->right = nullptr;
		head->right->left->left->left = nullptr;
		head->right->left->left->right = nullptr;
		head->right->right=new Node(10);
		head->right->right->left=new Node(9);
		head->right->right->left->left = nullptr;
		head->right->right->left->right = nullptr;
		head->right->right->right=new Node(11);
		head->right->right->right->left = nullptr;
		head->right->right->right->right = nullptr;

		PreInPosTraversal preInPosTraversal;
		cout<<"-------------------------递归-------------------------------"<<endl;	
		preInPosTraversal.preOrderRecur(head);
		cout<<endl;
		preInPosTraversal.preOrderUnRecur(head);
		cout << endl;

		preInPosTraversal.inOrderRecur(head);
		cout<<endl;
		preInPosTraversal.inOrderUnRecur(head);
		cout << endl;

		preInPosTraversal.posOrderRecur(head);
		cout << endl;
		preInPosTraversal.posOrderUnRecur(head);
		preInPosTraversal.posOrderUnRecur2(head);
		cout << "-------------------------非递归-------------------------------" << endl;
		//--------------------------------------------------------------
		//二叉树应用：折纸问题（中序遍历）
		printAllFolds(3);
		//--------------------------------------------------------------
		//找到二叉树的后继节点(中序遍历应用)
		Node*head=new Node(5);
		head->parent = nullptr; //head-parent-nullptr
		head->left=new Node(3);
		head->left->parent = head;  //3-parent-5
		head->right=new Node(8);
		head->right->parent = head; //8-parnet-5
		head->left->left=new Node(2);
		head->left->left->parent = head->left;//2-parent-3
		head->left->right=new Node(4);
		head->left->right->parent = head->left;//4-parent-3
		head->left->right->left = nullptr;
		head->left->right->right = nullptr;
		head->left->left->left=new Node(1);
		head->left->left->left->parent = head->left->left;//1-parent-2
		head->left->left->right = nullptr;
		head->left->left->left->left = nullptr;
		head->left->left->left->right = nullptr;

		head->right->left=new Node(7);
		head->right->left->parent = head->right;//7-parent-8
		head->right->left->left=new Node(6);
		head->right->left->left->parent = head->right->left;//6-parent-7
		head->right->left->right = nullptr;
		head->right->left->left->left = nullptr;
		head->right->left->left->right = nullptr;
		head->right->right=new Node(10);
		head->right->right->parent = head->right;//10-parent-8
		head->right->right->left=new Node(9);
		head->right->right->left->parent = head->right->right;//9-parent-10
		head->right->right->left->left = nullptr;
		head->right->right->left->right = nullptr;
		head->right->right->right=new Node(11);
		head->right->right->right->parent=head->right->right;//11-parent-10;
		head->right->right->right->left = nullptr;
		head->right->right->right->right = nullptr;

		printNodeTree(head);
		Node *test = getNextNode(head->left->right);
		if (test != nullptr){
			cout << "getNextNode(4)=" << test->data << endl;
		}
		test = getNextNode(head->left->left->left);
		if (test != nullptr){
			cout << "getNextNode(1)=" << test->data << endl;
		}
		test = getNextNode(head->right->left->left);
		if (test != nullptr){
			cout << "getNextNode(6)=" << test->data << endl;
		}
		test = getNextNode(head);
		if (test != nullptr){
			cout << "getNextNode(5)=" << test->data << endl;
		}
		test = getNextNode(head->right->right->right);
		if (test != nullptr){
			cout << "getNextNode(11)=" << test->data << endl;
		}else{
			cout<<"已经是最后一个"<<endl;
		}
		//--------------------------------------------------------------
#endif
		getchar();

}