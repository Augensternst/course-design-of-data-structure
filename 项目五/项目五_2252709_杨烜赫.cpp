// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype> // 为 isalpha 和 tolower 函数
using namespace std;

// 创建字典树节点
const int N = 1e6;
struct node {
	int cnt; // 单词频数
	node* next[26]; // 26个可能的后续节点
	node() {
		cnt = 0;
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}
};

// 建立字典树类
class Trie {
private:
	node* root; // 根节点
public:
	int find;
	Trie() {
		root = new node();
		find = 0;
	}
	~Trie() {
		deleteTree(root); // 递归删除所有节点
	}
	void insert(char* word); // 构造插入函数
	void search(char* word); // 构造搜索函数
	void deleteTree(node* root); // 释放字典树内存
};

void Trie::insert(char* word) {
	node* current = root;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (current->next[index] == nullptr) {
			current->next[index] = new node();
			if (current->next[index] == nullptr) {
				// 处理内存分配失败的情况
				std::cerr << "内存分配失败" << std::endl;
				exit(1); // 或者采取其他恢复措施
			}
		}

		current = current->next[index];
	}
	current->cnt++;
}

void Trie::search(char* word) {
	node* current = root;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (current->next[index] == nullptr) {
			find = 0;
			return;
		}
		current = current->next[index];
	}
	find = current->cnt;
}

void Trie::deleteTree(node* root) {
	if (root == nullptr) return;
	for (int i = 0; i < 26; i++) {
		deleteTree(root->next[i]);
	}
	delete root;
}
int main()
{
	cout << "文件检索系统" << endl;
	FILE* fp;
	char filename[1000];
	cout << "请输入文件名:";
	cin.getline(filename, 1000);
	fp = fopen(filename, "w");
	if(fp==nullptr)
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	cout << "请输入一段英文" << endl;
	char concent[10000];
	cin.getline(concent, 10000);
	fputs(concent, fp);
	cout << "本段文本已经保存在指定的文本文件中" << endl;                      
	fclose(fp);
	char keyword[1000];
	cout << "请输入检索的关键词" << endl;
	cin >> keyword;
	cout << endl;
	cout << "显示源文件“" << filename << "”：" << endl;
	fp = fopen(filename, "r");
	fgets(concent, 10000, fp);
	cout << concent;
	Trie con;
	Trie trie;
	int i = 0;
	cout << endl;
	while (concent[i] != '\0')
	{
		// 若当前位置不是字母，则向后寻找
		if (!isalpha(concent[i]))
		{
			i++;
			continue;
		}
		// current用来记录当前单词
		char current[1000];
		int j = 0;
		while (isalpha(concent[i]))
		{
			// 保证currrnt插入的都为小写字母
			current[j] = tolower(concent[i]);
			i++;
			j++;
		}
		current[j] = '\0'; // 添加字符串结束符
		// 若current不为空，插入字典树
		if (strlen(current) != 0) 
			trie.insert(current);
	}
	// 利用_keyWord记录全为小写的关键词
	char _keyWord[1024];
	strcpy(_keyWord, keyword);
	// 利用transform进行转换
	for (int k = 0; _keyWord[k] != '\0'; k++)
	{
		_keyWord[k] = tolower(_keyWord[k]);
	}
	// 利用Trie得到关键词词频
	trie.search(_keyWord);
	cout << endl << "在源文件中共检索到 ：" << trie.find << "个关键字“" << keyword << "”" << endl;
	return 0;
}