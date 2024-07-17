#include<iostream>
using namespace std;
struct circ_linknode {
	int pos;
	circ_linknode* next;
};
class circ_list
{
public:
	circ_list() {
		first = nullptr;
	};
	bool Init_circ_list(int n);
	bool circ_delete(int n, int s, int m, int k);
private:
	circ_linknode* first;

};
bool circ_list::Init_circ_list(int n) {
	if (n <= 0) {
		cerr << "����ڵ������������0" << endl;
		return false;
	}
	first = new circ_linknode;
	first->pos = 1;
	first->next = first;
	circ_linknode* pcurrent = first;
	for (int i = 2; i <= n; i++) {
		circ_linknode* pnew = new circ_linknode;
		pnew->pos = i;
		pnew->next = first;
		pcurrent->next = pnew;
		pcurrent = pnew;
	}
	return true;
}


bool circ_list::circ_delete(int n, int s, int m, int k)
{
	if (n <= 0 || s <= 0 || m <= 0 || k <= 0) {
		cerr << "�����������0" << endl;
		return false;
	}
	if (first == nullptr) {
		cerr << "����δ��ʼ��" << endl;
		return false;
	}
	circ_linknode* current = first;
	int num = n;
	int total = 0;
	for (int i = 0; i < s - 1; i++)
	{
		current = current->next;
	}
	while (num > k)
	{
		for (int i = 1; i < m - 1; i++)
		{
			current = current->next;
		}
		circ_linknode* temp = current->next;
		current->next = temp->next;
		total++;
		cout << "��" << total << "�����ߵ�λ���ǣ�" << temp->pos << endl;
		delete temp; // �ͷŽڵ��ڴ�  
		num--;
		current = current->next;
	}
	cout << "���ʣ�� " << k << " ��" << endl;
	cout << "����������λ��Ϊ��" << endl;
	current = first;
	for (int i = 0; i < k; i++) {
		cout << current->pos << "    ";
		current = current->next;
	}

	// �ͷ�ͷ�ڵ��ڴ�  
	delete first;
	first = nullptr;
	return true;
}

circ_list Josephus;
int main()
{
	int N, S, M, K;

	while (true) {
		cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ���˿�ʼ���������ѭ��ֱ��ʣ��K����Ϊֹ" << endl;
		cout << "������������Ϸ��������N��";
		cin >> N;
		cout << "��������Ϸ��ʼ��λ��S��";
		cin >> S;
		cout << "��������������M��";
		cin >> M;
		cout << "������ʣ�������������K��";
		cin >> K;
		if (N > 0 && S > 0 && M > 0 && K > 0 && K <= N) {
			break; // ���������붼����ʱ������ѭ��  
		}
		else {
			cerr << "����Ĳ����������0��K���ܴ���N������������" << endl;
			cin.clear(); // ������뻺�����Ĵ�����  
			cin.ignore(1024, '\n'); // ���Ի�����ʣ�������  
		}
	}

	circ_list Josephus;
	Josephus.Init_circ_list(N);
	Josephus.circ_delete(N, S, M, K);

	return 0;
}
