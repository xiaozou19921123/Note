
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
#include <hash_map>
#include <hash_set>
#include<queue>
//----------------------------------------------------------------
//ǰ׺��
struct Nodes
{
	int data;

	Nodes *next;
	Nodes *rand;
	Nodes *front;

	Nodes *left;
	Nodes *right;

	Nodes *parent;

	Nodes(int value) :data(value){};
	Nodes(){};
};

struct TrieNode
{
	int path;//�ж��ٸ��ַ������ڵ㣬����;�����Ľڵ㣬�����ٸ��ַ�����
	int end;//�ж��ٸ��ַ�����β
	//vector<Node*> nodes;
	/*Node *map[26];
	TrieNode(){ memset(map, 0, 4 * 26); };*/
	TrieNode *map[26];
	TrieNode():path(0),end(0){ memset(map, 0, sizeof(map)); }
	//TrieNode() :path(0), end(0){ memset(map, 0, 4*26); }
	
};

//vector<TrieNode*> map(26,nullptr);
class TrieTree
{
public:
	TrieTree();
	void insert(string word);
	void deletes(string word);
	bool search(string word);
	int prefixNumber(string word);

	TrieNode *root;

};

TrieTree::TrieTree()
{
	root = new TrieNode();
}
void TrieTree::insert(string word)
{
	if (word.empty())
	{
		return;
	}
	const char* chs = word.data();
	//char chs[100];
	//strcpy_s(chs, word.c_str());
	TrieNode *node = root;
	int index = 0;

	for (auto i = 0; i < word.length(); i++)
	{
		index = chs[i] - 'a';
		if (node->map[index] == nullptr)
		{
			
			node->map[index] = new TrieNode();
		}
		node = node->map[index];
		node->path++;
	}
	node->end++;
	
}

void TrieTree::deletes(string word)
{
	if (search(word))
	{
		const char* chs = word.data();
		//char chs[100];
		//strcpy_s(chs, word.c_str());

		TrieNode *node = root;
		int index = 0;
		for (int i = 0; i < word.length(); i++)
		{
			index = chs[i] - 'a';
			if (--node->map[index]->path == 0)
			{
				node->map[index] = nullptr;
				return;
			}
			node = node->map[index];
		}
		node->end--;
	}

}
bool TrieTree::search(string word)
{
	if (word.empty())
	{
		return false;
	}
	//====const char* chs = word.data();
	char chs[100];
	strcpy_s(chs, word.c_str());

	TrieNode *node = root;
	int index = 0;
	for (int i = 0; i < word.length(); i++)
	{
		int index = chs[i] - 'a';
		if (node->map[index] == nullptr)
		{
			return false;
		}
		node = node->map[index];
	}
	return node->end != 0;
}

int TrieTree::prefixNumber(string pre)
{
	if (pre.empty())
	{
		return false;
	}
	//====const char* chs = pre.data();
	char chs[100];
	strcpy_s(chs, pre.c_str());

	TrieNode *node = root;
	int index = 0;
	for (int i = 0; i < pre.length(); i++)
	{
		index = chs[i] - 'a';
		if (node->map[index] == nullptr)
		{
			return 0;
		}
		node = node->map[index];
	}
	return node->path;
}


void TrieTreeTest()
{
	TrieTree trieTree;
	cout << "search =" << trieTree.search("zou")<<endl;
	trieTree.insert("zou");
	cout << "insert search =" << trieTree.search("zou") << endl;
	trieTree.deletes("zou");
	cout << "deletes search =" << trieTree.search("zou") << endl;

	trieTree.insert("zou");
	trieTree.insert("zou");
	trieTree.insert("zou");
	trieTree.insert("zoudd");
	trieTree.insert("zouddd");
	cout << "prefixNumber=" << trieTree.prefixNumber("zou") << endl;
	cout << "prefixNumber=" << trieTree.prefixNumber("zoud") << endl;
	cout << "prefixNumber=" << trieTree.prefixNumber("ddd") << endl;
}
//----------------------------------------------------------------
class Edge;
class Node
{
public:
	int value;
	int in;//�ж��ٸ��ڵ�ָ����
	int out;//��ָ����ٸ��ڵ�
	vector<Node> nexts;//���ҳ����ܵ���Ľڵ�
	vector<Edge> edges;//�ߣ����ҷ���ߵļ���
	Node(int value) :in(0), out(0)
	{
		this->value = value;
	}
	Node(){}
	bool operator==(const Node&o){ return value == o.value; }
};

class Node_hash
{
public:
	bool operator() (const Node &lhs, const Node&rhs)const
	{
		return !(lhs.value == rhs.value);//ע������һ��ȡ�������Ͻ̳̺ö඼�Ǵ��
	}
	size_t operator()(const Node&node)const
	{
		return node.value;
	}
	static const size_t bucket_size = 4u;
	static const size_t min_buckets = 8u;
};

class Edge
{
public:
	int weight;
	Node from;
	Node to;
	Edge(int weight, Node from, Node to)
	{
		this->weight = weight;
		this->from = from;
		this->to = to;
	}
	bool operator==(const Edge&o){ return weight == o.weight; }
};


class Edge_hash
{
public:
	bool operator() (const Edge &lhs, const Edge&rhs)const
	{
		return !(lhs.weight == rhs.weight);//ע������һ��ȡ�������Ͻ̳̺ö඼�Ǵ��
	}
	size_t operator()(const Edge&edge)const
	{
		return edge.weight;
	}
	static const size_t bucket_size = 4u;
	static const size_t min_buckets = 8u;
};
class Graph
{
public:
	hash_map<int, Node> nodes;
	//vector<Edge*> edges;
	hash_set<Edge,Edge_hash> edges;
	Graph(){};
};

class GraphGenerator
{
	GraphGenerator(int matrix[][3],int len)
	{
		Graph graph;
		for (int i = 0; i < len; i++)
		{
			int from = matrix[i][0];
			int to = matrix[i][1];
			int weight = matrix[i][2];
			hash_map<int, Node>::iterator hash_map_iter = graph.nodes.find(from);
			if (hash_map_iter != graph.nodes.end())
			{
				graph.nodes[from] = Node(from);
			}
			hash_map_iter = graph.nodes.find(to);
			if (hash_map_iter != graph.nodes.end())
			{
				graph.nodes[to] = Node(to);
			}
			Node fromNode = graph.nodes[from];
			Node toNode = graph.nodes[to];
			Edge newEdge =Edge(weight, fromNode, toNode);
			fromNode.nexts.push_back(toNode);
			fromNode.out++;
			toNode.in++;
			fromNode.edges.push_back(newEdge);
			graph.edges.insert(newEdge);
		}
	}
	
};
//+++++++++++++++++++++++++++++++++++++++
void bfs(Node& node)
{
	queue<Node> queue_;
	hash_set<Node,Node_hash> map;
	hash_set<Node, Node_hash>::iterator iter_node;

	queue_.push(node);
	map.insert(node);
	while (!queue_.empty())
	{
		Node cur = queue_.front();
		queue_.pop();
		cout << "bfs cout=" << cur.value << endl;
		for (Node next : cur.nexts)
		{
			iter_node = map.find(next);
			if (iter_node != map.end())
			{
				cout << "find=" << next.value<< endl;
				map.insert(next);
				queue_.push(next);
			}
			else
			{
				cout << "not found" << endl;
			}
		}
	}
}

void test_BFS()
{
	
	Node node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7);
	node1.nexts.push_back(node2);
	node1.nexts.push_back(node3);
	node1.nexts.push_back(node4);

	node2.nexts.push_back(node3);
	node2.nexts.push_back(node7);

	node3.nexts.push_back(node5);
	node4.nexts.push_back(node6);
	node7.nexts.push_back(node3);

	bfs(node1);
}

//----------------------------------------------------------------





int main()
{
	//TrieTreeTest();//ǰ׺��
	
	//hash_set<int> int_test;
	//int_test.insert(1);
	//int_test.insert(2);
	//int_test.insert(3);
	//int_test.insert(4);
	//for (hash_set<int>::iterator iter; iter != int_test.end(); iter++)
	//{
	//	cout << *iter<<endl;
	//}
	test_BFS();

	getchar();

}





//===============================================================================================
//����ǰ׺������
#if 0

//ʹ���ֵ����洢Ӣ�ĵ��ʣ�ʹ�õĽṹ��26���ֵ����������ֵ��ʵĴ�Сд
#include <cstring>
#include <iostream>

/* trie�Ľڵ����� */
template <int Size> //SizeΪ�ַ���Ĵ�С
struct trie_node
{
	int freq; //��ǰ�ڵ��Ƿ������Ϊ�ַ����Ľ�β,�����freq>0,��������ظ����ʣ�freq��ʾ�õ��ʵĴ�Ƶ
	int node; //�ӽڵ�ĸ���
	trie_node *child[Size]; //ָ���ӽڵ�ָ��

	/* ���캯�� */
	trie_node() : freq(0), node(0) { memset(child, 0, sizeof(child)); }
};

/* trie */
template <int Size, typename Index> //SizeΪ�ַ���Ĵ�С��IndexΪ�ַ���Ĺ�ϣ����
class trie
{
public:
	/* �������ͱ��� */
	typedef trie_node<Size> node_type;
	typedef trie_node<Size>* link_type;

	/* ���캯�� */
	trie(Index i = Index()) : index(i){ }

	/* �������� */
	~trie() { clear(); }

	/* ��� */
	void clear()
	{
		clear_node(root);
		for (int i = 0; i < Size; ++i)
			root.child[i] = 0;
	}

	/* �����ַ��� */
	template <typename Iterator>
	void insert(Iterator begin, Iterator end)
	{
		link_type cur = &root; //��ǰ�ڵ�����Ϊ���ڵ�
		for (; begin != end; ++begin)
		{
			if (!cur->child[index[*begin]]) //����ǰ�ַ��Ҳ���ƥ�䣬���½��ڵ�
			{
				cur->child[index[*begin]] = new node_type;
				++cur->node; //��ǰ�ڵ���ӽڵ�����һ
			}
			cur = cur->child[index[*begin]]; //����ǰ�ڵ�����Ϊ��ǰ�ַ���Ӧ���ӽڵ�
		}
		(cur->freq)++; //���ô�����һ���ַ��Ľڵ�Ŀ���ֹ��־Ϊ��
	}

	/* �����ַ��������C����ַ��������ذ汾 */
	void insert(const char *str)
	{
		insert(str, str + strlen(str));
	}

	/* �����ַ������㷨�Ͳ������� */
	template <typename Iterator>
	int getfreq(Iterator begin, Iterator end)
	{
		link_type cur = &root;
		for (; begin != end; ++begin)
		{
			if (!cur->child[index[*begin]])
				return false;
			cur = cur->child[index[*begin]];
		}
		return cur->freq;
	}

	/* �����ַ��������C����ַ��������ذ汾 */
	bool find(const char *str)
	{
		int freq = getfreq(str, str + strlen(str));
		return freq > 0;
	}

	/* �����ַ���str�Ĵ�Ƶ*/
	int getfreq(const char* str)
	{
		return getfreq(str, str + strlen(str));
	}

	/* ɾ���ַ��� */
	template <typename Iterator>
	bool erase(Iterator begin, Iterator end)
	{
		bool result; //���ڴ���������
		erase_node(begin, end, root, result);
		return result;
	}

	/* ɾ���ַ��������C����ַ��������ذ汾 */
	bool erase(const char *str)
	{
		return erase(str, str + strlen(str));
	}

	/* ���ֵ�����������������е��� */
	template <typename Functor>
	void traverse(Functor execute = Functor())
	{
		char word[100] = { 0 };
		traverse_node(root, execute, word, 0);
	}

	/*����ֵ������ʵ��ܸ����������ظ��ַ���*/
	int sizeAll()
	{
		return sizeAll(root);
	}

	int sizeAll(node_type& cur)
	{
		int size = cur.freq;
		for (int i = 0; i < Size; ++i)
		{
			if (cur.child[i] == 0)
				continue;
			size += sizeAll(*cur.child[i]);
		}
		return size;
	}

	/*����ֵ������ʵ��ܸ������ظ��ַ�����һ������*/
	int sizeNoneRedundant()
	{
		return sizeNoneRedundant(root);
	}

	int sizeNoneRedundant(node_type& cur)
	{
		int size = cur.freq>0 ? 1 : 0;
		for (int i = 0; i < Size; ++i)
		{
			if (cur.child[i] == 0)
				continue;
			size += sizeNoneRedundant(*cur.child[i]);
		}
		return size;
	}

	/*���ַ�����Ĺ���ǰ׺�ĳ���*/
	int maxPrefix_length()
	{
		int length = maxPrefix_length(root);
		return length - 1;   //��Ϊlength�����˸��ڵ㣬��Ҫɾ����
	}

	int maxPrefix_length(node_type& cur)
	{
		int length = 0;
		for (int i = 0; i<Size; ++i)
		{
			if (cur.child[i] != 0)
			{
				int tmp = maxPrefix_length(*cur.child[i]);
				if (tmp > length)
				{
					length = tmp;
				}

			}
		}
		if (length > 0 || cur.node >1 || cur.freq >0 && cur.node>0)  //cur.node >1 ����"abcde"��"abcdf"���������cur.freq>0 && cur.node>0����"abcde"��"abcdef"�������
		{
			length++;
		}
		return length;

	}
	/*���ַ�������ǰ׺*/
	void maxPrefix(std::string& prefix)
	{
		maxPrefix(root, prefix);
		std::string word(prefix);
		int size = word.size();
		for (int i = 0; i<size; ++i)
			prefix[i] = word[size - 1 - i];
		prefix.erase(size - 1);   //��Ϊprefix�����˸��ڵ��ַ�����Ҫ����ɾ����

	}

	void maxPrefix(node_type& cur, std::string& prefix)
	{
		std::string word;
		int length = 0;
		int k = 0;
		for (int i = 0; i<Size; ++i)
		{
			if (cur.child[i] != 0)
			{
				maxPrefix(*cur.child[i], word);
				if (word.size() > length)
				{
					length = word.size();
					prefix.swap(word);
					k = i;
				}

			}
		}
		if (length > 0 || cur.node >1 || cur.freq >0 && cur.node>0)  //cur.node >1 ����"abcde"��"abcdf"���������cur.freq>0 && cur.node>0����"abcde"��"abcdef"�������
		{
			prefix.push_back(k + 'a');
		}
	}

private:

	template<typename Functor>
	void traverse_node(node_type& cur, Functor execute, char* word, int index)
	{
		if (cur.freq)
		{
			std::string str = word;
			execute(str, cur.freq);
		}
		for (int i = 0; i < Size; ++i)
		{
			if (cur.child[i] != 0)
			{
				word[index++] = 'a' + i;
				traverse_node(*cur.child[i], execute, word, index);
				word[index] = 0;
				index--;
			}
		}

	}


	/* ���ĳ���ڵ�������ӽڵ� */
	void clear_node(node_type& cur)
	{
		for (int i = 0; i < Size; ++i)
		{
			if (cur.child[i] == 0) continue;
			clear_node(*cur.child[i]);
			delete cur.child[i];
			cur.child[i] = 0;
			if (--cur.node == 0) break;
		}
	}

	/* ��������ɾ������ڵ㣬����ֵ�������丸�ڵ������Ƿ��ɾ���ýڵ� */
	template <typename Iterator>
	bool erase_node(Iterator begin, Iterator end, node_type &cur, bool &result)
	{
		if (begin == end) //�������ַ�����β���ݹ����ֹ����
		{
			result = (cur.freq > 0);   //�����ǰ�ڵ��Ƶ��>0,��ǰ�ڵ������Ϊ��ֹ�ַ�����ô���Ϊ��
			if (cur.freq)
				cur.freq--;            //�����ǰ�ڵ�Ϊ��ֹ�ַ�����Ƶ��һ
			return cur.freq == 0 && cur.node == 0;    //���ýڵ�Ϊ��Ҷ����ô֪ͨ�丸�ڵ�ɾ����
		}
		//���޷�ƥ�䵱ǰ�ַ�ʱ���������Ϊ�ٲ����ؼ٣���֪ͨ�丸�ڵ㲻Ҫɾ����
		if (cur.child[index[*begin]] == 0) return result = false;
		//�ж��Ƿ�Ӧ��ɾ�����ӽڵ�
		else if (erase_node((++begin)--, end, *(cur.child[index[*begin]]), result))
		{
			delete cur.child[index[*begin]]; //ɾ�����ӽڵ�
			cur.child[index[*begin]] = 0; //�ӽڵ�����һ
			//����ǰ�ڵ�Ϊ��Ҷ����ô֪ͨ�丸�ڵ�ɾ����
			if (--cur.node == 0 && cur.freq == 0) return true;
		}
		return false; //������������ؼ�
	}

	/* ���ڵ� */
	node_type root;

	/* ���ַ�ת��Ϊ������ת����������� */
	Index index;
};

//index function object
class IndexClass
{
public:
	int operator[](const char key)
	{
		if (key >= 'a' && key <= 'z')
			return key - 'a';
		else if (key >= 'A' && key <= 'Z')
			return key - 'A';
	}
};

class StringExe
{
public:
	void operator()(std::string& str, int freq)
	{
		std::cout << str.c_str() << ":" << freq << std::endl;
	}
};
int main()
{
	trie<26, IndexClass> t;
	t.insert("tree");
	t.insert("tree");
	t.insert("tea");
	t.insert("A");
	t.insert("BABCDEGG");
	t.insert("BABCDEFG");

	t.traverse<StringExe>();

	int sizeall = t.sizeAll();
	std::cout << "sizeAll:" << sizeall << std::endl;

	int size = t.sizeNoneRedundant();
	std::cout << "size:" << size << std::endl;

	std::string prefix;
	int deep = t.maxPrefix_length();
	t.maxPrefix(prefix);
	std::cout << "deep:" << deep << " prefix:" << prefix.c_str() << std::endl;

	if (t.find("tree"))
		std::cout << "find tree" << std::endl;
	else
		std::cout << "not find tree" << std::endl;

	int freq = t.getfreq("tree");
	std::cout << "tree freq:" << freq << std::endl;

	if (t.erase("tree"))
		std::cout << "delete tree" << std::endl;
	else
		std::cout << "not find tree" << std::endl;

	freq = t.getfreq("tree");
	std::cout << "tree freq:" << freq << std::endl;

	if (t.erase("tree"))
		std::cout << "delete tree" << std::endl;
	else
		std::cout << "not find tree" << std::endl;

	if (t.erase("tree"))
		std::cout << "delete tree" << std::endl;
	else
		std::cout << "not find tree" << std::endl;

	sizeall = t.sizeAll();
	std::cout << "sizeAll:" << sizeall << std::endl;

	size = t.sizeNoneRedundant();
	std::cout << "size:" << size << std::endl;


	if (t.find("tre"))
		std::cout << "find tre" << std::endl;
	else
		std::cout << "not find tre" << std::endl;



	t.traverse<StringExe>();

	getchar();
}

#endif