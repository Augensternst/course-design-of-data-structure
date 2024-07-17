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
		cerr << "链表节点数量必须大于0" << endl;
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
		cerr << "参数必须大于0" << endl;
		return false;
	}
	if (first == nullptr) {
		cerr << "链表未初始化" << endl;
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
		cout << "第" << total << "个死者的位置是：" << temp->pos << endl;
		delete temp; // 释放节点内存  
		num--;
		current = current->next;
	}
	cout << "最后剩下 " << k << " 人" << endl;
	cout << "最后的生还者位置为：" << endl;
	current = first;
	for (int i = 0; i < k; i++) {
		cout << current->pos << "    ";
		current = current->next;
	}

	// 释放头节点内存  
	delete first;
	first = nullptr;
	return true;
}

circ_list Josephus;
int main()
{
	int N, S, M, K;

	while (true) {
		cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环直到剩下K个人为止" << endl;
		cout << "请输入生死游戏的总人数N：";
		cin >> N;
		cout << "请输入游戏开始的位置S：";
		cin >> S;
		cout << "请输入死亡数字M：";
		cin >> M;
		cout << "请输入剩余的生还者人数K：";
		cin >> K;
		if (N > 0 && S > 0 && M > 0 && K > 0 && K <= N) {
			break; // 当所有输入都合理时，跳出循环  
		}
		else {
			cerr << "输入的参数必须大于0且K不能大于N，请重新输入" << endl;
			cin.clear(); // 清除输入缓冲区的错误标记  
			cin.ignore(1024, '\n'); // 忽略缓冲区剩余的输入  
		}
	}

	circ_list Josephus;
	Josephus.Init_circ_list(N);
	Josephus.circ_delete(N, S, M, K);

	return 0;
}
