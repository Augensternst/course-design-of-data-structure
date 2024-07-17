// ReSharper disable All
#include <iostream>
using namespace std;
const int MAX = 21;
int n = 0;//输入的棋盘行和列
class queen
{
private:
	char board[MAX][MAX];//存储棋盘
	bool left_diagonal[MAX * 2];//点对应的左对角线
	bool right_diagonal[MAX * 2];//点对应的右对角线
	bool is_queen[MAX + 1];//该点是否为皇后

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
	cout << "现有N×N的棋盘，放入N个皇后，要求所有皇后不在同一行、列、对角线上！" << endl << endl;
	cout << "请输入皇后的个数（1-20）：";
	while(true)
	{
		cin >> n;
		if(n<1||n>20||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入皇后数量不正确，请重新输入！" << endl;
			continue;
		}
		else
		{
			break;
		}

	}
	Queen.find_queen(0);
	cout << "共有" << Queen.count << "种解法" << endl;
	return 0;
}