// ReSharper disable All
#include <iostream>
using namespace std;
const int MAX = 21;
int n = 0;//����������к���
class queen
{
private:
	char board[MAX][MAX];//�洢����
	bool left_diagonal[MAX * 2];//���Ӧ����Խ���
	bool right_diagonal[MAX * 2];//���Ӧ���ҶԽ���
	bool is_queen[MAX + 1];//�õ��Ƿ�Ϊ�ʺ�

public:
	queen();
	int count;
	void print_board();
	void find_queen(int r);

}Queen;
queen::queen()
{
	count = 0;
	for (int i = 0; i < MAX * 2; i++)
	{
		left_diagonal[i] = false;
		right_diagonal[i] = false;
	}
	for (int i = 0; i < MAX; i++)
	{
		is_queen[i] = false;
		for (int j = 0; j < MAX; j++)
		{
			board[i][j] = '0';
		}
	}
}
void queen::print_board()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;

}
void queen::find_queen(int r)
{
	if (r == n)
	{
		print_board();
		count++;
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (!is_queen[i] && !left_diagonal[i + r] && !right_diagonal[r - i + n])
		{
			board[r][i] = 'X';
			is_queen[i] = left_diagonal[i + r] = right_diagonal[r - i + n] = true;
			find_queen(r + 1);
			is_queen[i] = left_diagonal[i + r] = right_diagonal[r - i + n] = false;
			board[r][i] = '0';
		}
	}

}
int main()
{
	cout << "����N��N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��С��Խ����ϣ�" << endl << endl;
	cout << "������ʺ�ĸ�����1-20����";
	while(true)
	{
		cin >> n;
		if(n<1||n>20||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����ʺ���������ȷ�����������룡" << endl;
			continue;
		}
		else
		{
			break;
		}

	}
	Queen.find_queen(0);
	cout << "����" << Queen.count << "�ֽⷨ" << endl;
	return 0;
}