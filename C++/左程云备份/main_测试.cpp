#include <iostream>  
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

void test(){
	//cout<<"Error: "<<__FILE__<<"\tLine: "<<__LINE__<<"\tFunc: "<<__FUNCTION__<<endl;  
	throw Exception("Custom Exception !", __FILE__, __LINE__, __FUNCTION__);
}





#include <hash_map>
#include <string>
using namespace std;

class ClassA{
public:
	ClassA(int a) :c_a(a){}
	int getvalue()const { return c_a; }
	void setvalue(int a){ c_a; }
private:
	int c_a;
};

//1 define the hash function
struct hash_A{
	size_t operator()(const class ClassA & A)const{
		//  return  hash<int>(classA.getvalue());
		return A.getvalue();
	}
	// bucket information
	static const size_t bucket_size = 4u;
	static const size_t min_buckets = 8u;
};

//2 define the equal function
struct equal_A{
	bool operator()(const class ClassA & a1, const class ClassA & a2)const{
		return  a1.getvalue() == a2.getvalue();
	}
};

int main()
{
	//--------------------------------------------------------------------------
	hash_map<int, string> mymap;
	mymap[9527] = "唐伯虎点秋香";
	mymap[1000000] = "百万富翁的生活";
	mymap[10000] = "白领的工资底线";

	if (mymap.find(9527) != mymap.end())
	{
		cout << "find=" << mymap[9527].c_str() << endl;
	}
	else
	{
		cout << "not found";
	}
	//--------------------------------------------------------------------------
	hash_map<ClassA, string, hash_A, equal_A> hmap;
	ClassA a1(12);
	hmap[a1] = "I am 12";
	ClassA a2(198877);
	hmap[a2] = "I am 198877";

	cout << hmap[a1] << endl;
	cout << hmap[a2] << endl;
	getchar();
}






























//=========================================hash_set========================================
#if 0

/*
hash_set哈希集合容器:使用hashtable数据结构的具有高效数据检索的关联容器
不提供反向迭代器，只有前向迭代器iterator和const_iterator
不允许插入重复的元素键值

* 元素的删除
void erase(iterator pos);
size_type erase(const key_type& k);     //删除等于键值k的元素
void erase(first,last);        //删除[first,last)区间的元素
void clear();

* 访问与搜索
iterator begin();iterator end();//不会将元素排序遍历出来
iterator find(const key_type& k) const; //对于非默认类型如char*,在搜素时应定义相关的函数对象

*/
#include <hash_set>
struct student
{
	char* name;
	int age;
	char* city;
	char* phone;
	bool operator==(const student&o){ return strcmp(city, o.city) == 0; } //注意strcmp相等返回0
};
struct student_hash {
	// comparisons
	bool operator() (const student& a, const student& b)const{
		return !(strcmp(a.city, b.city) == 0);      //不允许同名，name为键值
	}
	// hashing function
	size_t operator()(const student& stu) const
	{
		unsigned long res = 0;
		char* s = stu.city;
		for (; *s; ++s){
			res = *s;
		}
		return size_t(res);
	}
	// bucket information
	static const size_t bucket_size = 128u;
	static const size_t min_buckets = 128u;
};


//typedef unsigned int size_t;
//针对字符串的比较函数对象
class strequal{
public:
	bool operator () (const char* a, const char* b)const{
		return strcmp(a, b) == 0;
	}
};

//========================================================================================================
class Foo
{
public:
	Foo(int i) :value(i){}
	bool operator==(const Foo&o){ return value == o.value; }
public:
	int value;
	//friend class HashFoo;
};
class HashFoo
{
	
public:
	bool operator() (const Foo &lhs, const Foo&rhs)const
	{
		return !(lhs.value == rhs.value);//注意这里一定取反，网上教程好多都是错的
	}
	size_t operator()(const Foo&foo)const
	{
		return foo.value;
	}
	static const size_t bucket_size = 4u;
	static const size_t min_buckets = 8u;
};


using namespace stdext;
struct T {
	T(int x) : value(x){}
	int value;
	bool operator==(const T&o){ return value == o.value; }
};
struct htraits {
	// comparisons
	bool operator()(const T& lhs, const T& rhs) const {
		return !(lhs.value == rhs.value);
	}
	// hashing function
	size_t operator()(const T& key) const {
	return key.value;
	}
	// bucket information
	static const size_t bucket_size = 4u;
	static const size_t min_buckets = 8u;
};

#if 0
int main()
{
	//-------------------------------------
	T a(1), b(2), c(3);
	hash_set<T, htraits> ht;
	ht.insert(a);
	ht.insert(b);
	ht.insert(c);
	hash_set<T, htraits>::iterator iter = ht.find( T(3));
	if (iter != ht.end())
	{
		cout << "find:" << iter->value<<endl;
	}
	else
	{
		cout << "sorry not find!!!!"<<endl;
	}

	//-------------------------------------
	hash_set<Foo, HashFoo> hashTable;
	Foo f1(1), f2(2), f3(3);
	hashTable.insert(f1);
	hashTable.insert(f2);
	hashTable.insert(f3);
	hash_set<Foo, HashFoo>::iterator it;
	it = hashTable.find(f3);

	if (it != hashTable.end())
	{
		cout << "find:" << it->value << endl;
	}
	else
	{
		cout << "sorry not find" << endl;
	}

	for (auto it = hashTable.begin(); it != hashTable.end(); it++)
	{
		cout << "hashTable=" << it->value<<endl;
	}

	getchar();

}
//========================================================================================================


# else
int main()
{
	using namespace std;
	//hash_set<const char*,hash<const char*>,strequal> a;
	hash_set<const char*> a;
	a.insert("tongjin");
	a.insert("cumirror");
	a.insert("makelaugh");
	a.insert("feiguodeyun");
	// hash<const char*>默认提供的hash函数对象
	//hash_set<const char*,hash<const char*>,strequal>::const_iterator b=a.find("tongjin");
	hash_set<const char*>::const_iterator b = a.find("tongjin");
	cout<<*b<<" is "<<(b!=a.end()?"present":"not present")<<endl;
	
	student s[] = {
			{ "童进", 23, "长沙", "XXX" },
			{ "老大", 23, "武汉", "XXX" },
			{"饺子",23,"福州","XXX"},
			{"王老虎",23,"地球","XXX"},
			{"周润发",23,"香港1","XXX"},
			{"周星星",23,"香港2","XXX"},   //city不能重复，否则会出错，find也会出错
			{"童进",23,"香港3","XXX"}   //name重复
	};     
	//hash_set<student> c;
	hash_set<student, student_hash> c;
	c.insert(s[0]);
	c.insert(s[1]);
	c.insert(s[2]);
	c.insert(s[3]);
	c.insert(s[4]);
	c.insert(s[5]);

	// 注意hash容器并不能实现排序
	for (hash_set<student, student_hash>::iterator i = c.begin(); i != c.end(); i++){
		printf("%s,%d,%s\n", i->name, i->age, i->city);
		//cout << i->name << " " << i->age << " " << i->city << endl;
	}
	hash_set<student, student_hash>::iterator iter_ = c.find(s[5]);
	if (iter_ != c.end())
	{
		cout << "find ";
		printf("%s,%d,%s\n", iter_->name, iter_->age, iter_->city);
	}
	else
	{
		cout<<"sourry not find";
	}


#if 0
	cout << "Test Exception !" << endl;
	try{
		cout << "Do Exception !" << endl;
		test();
	}
	catch (Exception exe1){
		cerr << "Catch Exception : " << exe1.info() << endl;
	}
	cout << "Test Finish!" << endl;
#endif

	getchar();
	return 0;
}

#endif

#endif