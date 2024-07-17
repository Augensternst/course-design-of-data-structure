// ReSharper disable All
#include<iostream>
using namespace std;
//地图大小定义
const int X_MAX = 100;
const int Y_MAX = 100;
//====================================================================================
//迷宫初始化
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
		cout << "请输入迷宫的行数和列数：" << endl;
		cin >> row >> col;
		if (row <= 0 || col <= 0 || !cin.good()) {
			cout << "输入行列不合法，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		map = new char* [row];
		for (int i = 0; i < row; i++) {
			map[i] = new char[col];
		}
		cout << "请输入迷宫，以0表示空地，#表示围墙：" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> map[i][j];
			}
		}
		// 检查迷宫有效性
		if (!check_map()) {
			for (int i = 0; i < row; i++) {
				delete[] map[i];
			}
			delete[] map;
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入迷宫不符合规定，请重新输入！" << endl;
			continue;
		}

		cout << "迷宫初始化成功！" << endl;
		// 打印迷宫
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
	// 检查周围一圈是否为围墙
	for (int i = 0; i < row; i++) {
		if (map[i][0] != '#' || map[i][col - 1] != '#') return false;
	}
	for (int j = 0; j < col; j++) {
		if (map[0][j] != '#' || map[row - 1][j] != '#') return false;
	}

	// 检查起始点是否为空地
	if (map[1][1] != '0' || map[row - 2][col - 2] != '0') {
		cout << "迷宫起始或终点坐标不合法，请重新输入" << endl;
		return false;
	}
	return true;
}
//====================================================================================
//节点定义
struct linknode
{
	//记录行列坐标
	int x;
	int y;
	//搜索记号
	bool mark;
	//指针域
	linknode* next;
	//记录展示节点坐标
	void print_coordinate()
	{
		cout << '<' << x << ',' << y << '>';
	}
	//节点初始化
	linknode(int x_=0,int y_=0): x(x_), y(y_), mark(false)
	{
		next = nullptr;
	}
};
//建立链表类和链表函数 
class game_linklist
{
	friend game_linklist;
private:
	linknode* head;           // 链表头指针
public:
	game_linklist();             //构造函数，创建空链表
	~game_linklist();			//析构函数，删除表空间
	bool Insert(int i, linknode& e);//在表中第i个位置插入元素
	linknode* Getlink(int i);       //按位查找，获取第i个节点地址
	int Length();			//测表长
	void ListDisplay();		//遍历输出表中元素
};
game_linklist::game_linklist() {
	//构造函数，创建空链表
	head = new linknode;
	// 若失败则给出提示，保证健壮性
	if (head == nullptr)
	{
		cerr << "内存分配错误！" << endl;
		system("pause");
		exit(1);
	}
	head->next = nullptr;
}
game_linklist::~game_linklist() {
	//析构函数，删除表空间
	while (head) {
		const linknode* p = head;
		head = head->next;
		delete p;
	}
	head = nullptr;
}
bool game_linklist::Insert(int i, linknode& e) {
	// 创建一个新的节点
	linknode* s = new linknode(e);
	if (s == nullptr) {
		cerr << "内存分配错误！" << endl;
		exit(1);
	}

	// 插入到链表头部
	s->next = head->next;
	head->next = s;
	return true;
}

linknode* game_linklist::Getlink(int i) {
	//按位查找，获取第i个元素的值
	linknode* p;
	p = head->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i)
		throw "查找位置异常！";
	else
		return p;
}
int game_linklist::Length() {
	//测表长
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
//建立游戏功能实现类
class game_function
{
	friend class maze;
private:
	game_linklist way;
	linknode node[X_MAX+1][Y_MAX+1];//位置节点
	
public:
	game_function();//初始化节点坐标
	void init_find_way();//初始化寻路函数
	bool find_way(int now_x, int now_y, int end_x, int end_y,char** map,int row,int col);//寻路函数
	void display_way();//输出路径
	const int dx[4] = { 0,0,-1,1 };//定义棋子移动双数组
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
		return  false;//到达障碍物或者出界
	}
	else
	{
		node[now_x][now_y].mark = true;
	}
	//终点处理
	if(now_x==end_x&&now_y==end_y)
	{
		way.Insert(way.Length(), node[now_x][now_y]);
		map[now_x][now_y] = 'x';
		return true;
	}
	//四周搜索
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
		cout << "迷宫路径" << endl;
		cout << endl;
		way.ListDisplay();
	

}
//====================================================================================
//主函数实现
int main()
{
	Maze.init_maze();
	Maze.check_map();
	game.init_find_way();
	game.display_way();
	return 0;
}
//检测数据
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