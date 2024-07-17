// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype> // Ϊ isalpha �� tolower ����
using namespace std;

// �����ֵ����ڵ�
const int N = 1e6;
struct node {
	int cnt; // ����Ƶ��
	node* next[26]; // 26�����ܵĺ����ڵ�
	node() {
		cnt = 0;
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}
};

// �����ֵ�����
class Trie {
private:
	node* root; // ���ڵ�
public:
	int find;
	Trie() {
		root = new node();
		find = 0;
	}
	~Trie() {
		deleteTree(root); // �ݹ�ɾ�����нڵ�
	}
	void insert(char* word); // ������뺯��
	void search(char* word); // ������������
	void deleteTree(node* root); // �ͷ��ֵ����ڴ�
};

void Trie::insert(char* word) {
	node* current = root;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (current->next[index] == nullptr) {
			current->next[index] = new node();
			if (current->next[index] == nullptr) {
				// �����ڴ����ʧ�ܵ����
				std::cerr << "�ڴ����ʧ��" << std::endl;
				exit(1); // ���߲�ȡ�����ָ���ʩ
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
	cout << "�ļ�����ϵͳ" << endl;
	FILE* fp;
	char filename[1000];
	cout << "�������ļ���:";
	cin.getline(filename, 1000);
	fp = fopen(filename, "w");
	if(fp==nullptr)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	cout << "������һ��Ӣ��" << endl;
	char concent[10000];
	cin.getline(concent, 10000);
	fputs(concent, fp);
	cout << "�����ı��Ѿ�������ָ�����ı��ļ���" << endl;                      
	fclose(fp);
	char keyword[1000];
	cout << "����������Ĺؼ���" << endl;
	cin >> keyword;
	cout << endl;
	cout << "��ʾԴ�ļ���" << filename << "����" << endl;
	fp = fopen(filename, "r");
	fgets(concent, 10000, fp);
	cout << concent;
	Trie con;
	Trie trie;
	int i = 0;
	cout << endl;
	while (concent[i] != '\0')
	{
		// ����ǰλ�ò�����ĸ�������Ѱ��
		if (!isalpha(concent[i]))
		{
			i++;
			continue;
		}
		// current������¼��ǰ����
		char current[1000];
		int j = 0;
		while (isalpha(concent[i]))
		{
			// ��֤currrnt����Ķ�ΪСд��ĸ
			current[j] = tolower(concent[i]);
			i++;
			j++;
		}
		current[j] = '\0'; // ����ַ���������
		// ��current��Ϊ�գ������ֵ���
		if (strlen(current) != 0) 
			trie.insert(current);
	}
	// ����_keyWord��¼ȫΪСд�Ĺؼ���
	char _keyWord[1024];
	strcpy(_keyWord, keyword);
	// ����transform����ת��
	for (int k = 0; _keyWord[k] != '\0'; k++)
	{
		_keyWord[k] = tolower(_keyWord[k]);
	}
	// ����Trie�õ��ؼ��ʴ�Ƶ
	trie.search(_keyWord);
	cout << endl << "��Դ�ļ��й������� ��" << trie.find << "���ؼ��֡�" << keyword << "��" << endl;
	return 0;
}