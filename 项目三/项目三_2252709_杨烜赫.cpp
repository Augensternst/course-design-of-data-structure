// ReSharper disable All
#include<iostream>
using namespace std;
//��ͼ��С����
const int X_MAX = 100;
const int Y_MAX = 100;
//====================================================================================
//�Թ���ʼ��
class game_function;
class maze {
	friend class game_function;
public:
	maze();
	bool init_maze();
	bool check_map();
private:
	int row;
	int col;
	int road_num;
	char** map;
	char** solve;

}Maze;
maze::maze()
{
	row = 0;
	col = 0;
	road_num = 0;
	map = nullptr;
	solve = nullptr;
}
bool maze::init_maze() {
	while (true) {
		cout << "�������Թ���������������" << endl;
		cin >> row >> col;
		if (row <= 0 || col <= 0 || !cin.good()) {
			cout << "�������в��Ϸ�������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		map = new char* [row];
		for (int i = 0; i < row; i++) {
			map[i] = new char[col];
		}
		cout << "�������Թ�����0��ʾ�յأ�#��ʾΧǽ��" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> map[i][j];
			}
		}
		// ����Թ���Ч��
		if (!check_map()) {
			for (int i = 0; i < row; i++) {
				delete[] map[i];
			}
			delete[] map;
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "�����Թ������Ϲ涨�����������룡" << endl;
			continue;
		}

		cout << "�Թ���ʼ���ɹ���" << endl;
		// ��ӡ�Թ�
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		break;
	}
	return true;
}
bool maze::check_map() {
	// �����ΧһȦ�Ƿ�ΪΧǽ
	for (int i = 0; i < row; i++) {
		if (map[i][0] != '#' || map[i][col - 1] != '#') return false;
	}
	for (int j = 0; j < col; j++) {
		if (map[0][j] != '#' || map[row - 1][j] != '#') return false;
	}

	// �����ʼ���Ƿ�Ϊ�յ�
	if (map[1][1] != '0' || map[row - 2][col - 2] != '0') {
		cout << "�Թ���ʼ���յ����겻�Ϸ�������������" << endl;
		return false;
	}
	return true;
}
//====================================================================================
//�ڵ㶨��
struct linknode
{
	//��¼��������
	int x;
	int y;
	//�����Ǻ�
	bool mark;
	//ָ����
	linknode* next;
	//��¼չʾ�ڵ�����
	void print_coordinate()
	{
		cout << '<' << x << ',' << y << '>';
	}
	//�ڵ��ʼ��
	linknode(int x_=0,int y_=0): x(x_), y(y_), mark(false)
	{
		next = nullptr;
	}
};
//����������������� 
class game_linklist
{
	friend game_linklist;
private:
	linknode* head;           // ����ͷָ��
public:
	game_linklist();             //���캯��������������
	~game_linklist();			//����������ɾ����ռ�
	bool Insert(int i, linknode& e);//�ڱ��е�i��λ�ò���Ԫ��
	linknode* Getlink(int i);       //��λ���ң���ȡ��i���ڵ��ַ
	int Length();			//���
	void ListDisplay();		//�����������Ԫ��
};
game_linklist::game_linklist() {
	//���캯��������������
	head = new linknode;
	// ��ʧ���������ʾ����֤��׳��
	if (head == nullptr)
	{
		cerr << "�ڴ�������" << endl;
		system("pause");
		exit(1);
	}
	head->next = nullptr;
}
game_linklist::~game_linklist() {
	//����������ɾ����ռ�
	while (head) {
		const linknode* p = head;
		head = head->next;
		delete p;
	}
	head = nullptr;
}
bool game_linklist::Insert(int i, linknode& e) {
	// ����һ���µĽڵ�
	linknode* s = new linknode(e);
	if (s == nullptr) {
		cerr << "�ڴ�������" << endl;
		exit(1);
	}

	// ���뵽����ͷ��
	s->next = head->next;
	head->next = s;
	return true;
}

linknode* game_linklist::Getlink(int i) {
	//��λ���ң���ȡ��i��Ԫ�ص�ֵ
	linknode* p;
	p = head->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)
		throw "����λ���쳣��";
	else
		return p;
}
int game_linklist::Length() {
	//���
	linknode* p;
	p = head;
	int n = 0;
	while (p->next) {
		p = p->next;
		n++;
	}
	return n;
}
void game_linklist::ListDisplay()
{
	linknode* now = head->next;
	while (now != NULL)
	{
		now->print_coordinate();
		now = now->next;
		if (now != NULL)
			cout << " --> ";
	}
}
//====================================================================================
//������Ϸ����ʵ����
class game_function
{
	friend class maze;
private:
	game_linklist way;
	linknode node[X_MAX+1][Y_MAX+1];//λ�ýڵ�
	
public:
	game_function();//��ʼ���ڵ�����
	void init_find_way();//��ʼ��Ѱ·����
	bool find_way(int now_x, int now_y, int end_x, int end_y,char** map,int row,int col);//Ѱ·����
	void display_way();//���·��
	const int dx[4] = { 0,0,-1,1 };//���������ƶ�˫����
	const int dy[4] = { -1,1,0,0 };
}game;
game_function::game_function()
{
	for (int i=0;i<X_MAX;i++)
	{
		for(int j=0;j<Y_MAX;j++)
		{
			node[i][j].x = i;  
			node[i][j].y = j;
		}
	}
}
void game_function::init_find_way()
{
	find_way(1, 1, Maze.row - 2, Maze.col - 2, Maze.map, Maze.row, Maze.col);

}
bool game_function::find_way(int now_x, int now_y, int end_x, int end_y,char** map,int row,int col)
{
	if(now_x<0||now_x>row||now_y<0||now_y>col|| node[now_x][now_y].mark ||map[now_x][now_y] == '#')
	{
		return  false;//�����ϰ�����߳���
	}
	else
	{
		node[now_x][now_y].mark = true;
	}
	//�յ㴦��
	if(now_x==end_x&&now_y==end_y)
	{
		way.Insert(way.Length(), node[now_x][now_y]);
		map[now_x][now_y] = 'x';
		return true;
	}
	//��������
	for(int i=0;i<4;i++)
	{
		if(find_way(now_x+dx[i],now_y+dy[i],end_x,end_y,map,row,col))
		{
			map[now_x][now_y] = 'x';
			way.Insert(way.Length(), node[now_x][now_y]);
			return true;
		}

	}
	return false;

}
void game_function::display_way()
{
	cout << endl << endl;
	for (int i = 0; i <Maze. row; i++)
	{
		for (int j = 0; j < Maze.col; j++)
		{
			cout <<Maze. map[i][j] << " ";
		}
		cout << endl;
	}
		cout << endl;
		cout << "�Թ�·��" << endl;
		cout << endl;
		way.ListDisplay();
	

}
//====================================================================================
//������ʵ��
int main()
{
	Maze.init_maze();
	Maze.check_map();
	game.init_find_way();
	game.display_way();
	return 0;
}
//�������
/*
10 10
##########
#0##0#000#
#00000#0##
#####0####
#00000000#
##0#0#0#0#
#00#00#00#
#0###0#0##
#00#0#000#
##########
5 5
#####
#000#
#000#
#000#
#####
4 4
####
#0##
#00#
####
*/