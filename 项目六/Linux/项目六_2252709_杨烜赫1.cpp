// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using namespace std;
//使用孩子兄弟树，先建立节点
struct node
{
	char name[50];
	node* firstchild;
	node* firstbrother;
	node* parent;
	node()
	{
		memset(name, 0, sizeof(name));
		firstchild = nullptr;
		firstbrother = nullptr;
		parent = nullptr;
	}
	// 有参构造函数
	node(const char* newName, node* newFirstChild = nullptr, node* newFirstBrother = nullptr, node* newParent = nullptr)
	{
		strncpy(name, newName, sizeof(name) - 1); // 避免字符串溢出
		name[sizeof(name) - 1] = '\0'; // 确保字符串以 null 终止
		firstchild = newFirstChild;
		firstbrother = newFirstBrother;
		parent = newParent;
	}
};
//建立族谱树
class relation_tree
{
private:
	node* root;
	void delete_tree(node* current);
public:
	relation_tree()
	{
		root = nullptr;
	}
	~relation_tree()
	{
		
	}
	node* search(node* current, const char* name);
	void build_root();//建立根节点
	void build_tree();//建立一个子树
	void display_tree(const char* name);//展示当前节点的孩子
	void add_family();//建立新的家庭
	void delete_family();//解散家庭
	void modify_name();//修改家庭成员姓名
};

void relation_tree::delete_tree(node* current)
{
	if(current==nullptr)
	{
		return;

	}
	if(current->firstchild!=nullptr)
	{
		delete_tree(current->firstchild);
		node* temp = current->firstchild;
		while (temp->firstbrother!=nullptr)
		{
			delete_tree(temp->firstbrother);
			temp = temp->firstbrother;
		}
		delete[]current;
	}
}
node* relation_tree::search(node* current, const char* self_name)
{
	if (!current)
	{
		return nullptr;
	}

	if (strcmp(current->name, self_name) == 0)
	{
		return current;
	}

	node* find = nullptr;

	for (node* s = current->firstchild; s != nullptr; s = s->firstbrother)
	{
		find = search(s, self_name);

		if (find != nullptr)
		{
			return find;
		}
	}

	return nullptr;
}
void relation_tree::build_root()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	char name[50];
	cin >> name;
	//为根节点建立空间
	root = new node(name);
	//错误处理
	if(root==nullptr)
	{
		cerr << "内存分配错误" << endl;
		exit(1);
	}
	//给出祖先名字
	cout << "此家谱祖先名字是：" << root->name << endl;
}

void relation_tree::build_tree()
{
	cout << "请给出要建立家庭的人的姓名:";
	char name[50];
	cin >> name;
	node* father = search(root, name);
	if(father==nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	if(father->firstchild!=nullptr)
	{
		cout << "该成员已经建立过家庭！" << endl;
		return;
	}
	cout << "请输入" << name << "的儿女的个数:";
	int child_num;
	while(1)
	{
		cin >> child_num;
		if(child_num<0||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入有误，儿女个数必须为正整数" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	cout << "请依次输入" << name << "儿女的姓名：";
	char child_name[50];
	while(true)
	{
		cin >> child_name;
		if(search(root, child_name)==nullptr)
		{
			father->firstchild = new node(child_name);
			if(father->firstchild==nullptr)
			{
				cerr << "内存分配错误" << endl;
				exit(1);

			}
			father->firstchild->parent = father;
			break;

		}
		if(search(root, child_name)!=nullptr)
		{
			cout << "第一位成员已经存在，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}
	for(int i=1;i<child_num;i++)
	{
		while(true)
		{
			cin >> child_name;
			if(search(root, child_name)==nullptr)
			{
				node* current = father->firstchild;
				while (current->firstbrother!=nullptr)
				{
					current = current->firstbrother;
				}
				current->firstbrother = new node(child_name);
				if(current->firstbrother==nullptr)
				{
					cerr << "内存分配错误" << endl;
					exit(1);
				}
				current->firstbrother->parent = father;
				break;
			}
			else
			{
				cout << "姓名为" << child_name << "成员名字重复，请重新输入！" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			
		}
	}
	display_tree(name);

}

void relation_tree::display_tree(const char* name)
{
	node* current = search(root, name);
	if (current != nullptr && current->firstchild != nullptr) // 确保current存在且有子女
	{
		cout << name << "的第一代子女有：";
		node* child = current->firstchild;
		while (child != nullptr) // 遍历所有子女
		{
			cout << child->name << ' ';
			child = child->firstbrother; // 移动到下一个兄弟节点
		}
		cout << endl;
	}
	else
	{
		cout << name << "没有子女或者不存在于家谱中。" << endl;
	}
}


void relation_tree::add_family()
{
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	char parentName[50];
	cin >> parentName;
	node* parent = search(root, parentName);
	if (parent == nullptr)
	{
		cout << "家谱中不存在该成员信息" << endl;
		return;
	}

	while (true)
	{
		cout << "请输入" << parentName << "新添加儿子（或女儿）的姓名：";
		char childName[50];
		cin >> childName;

		if (search(root, childName) != nullptr)
		{
			cout << "该成员已经存在，请重新输入！" << endl;
			cin.clear(); // 清除缓冲区中的输入错误
			cin.ignore(1000, '\n'); // 忽略之前的错误输入
			continue; // 继续循环，等待新的输入
		}

		// 根据是否已有子女来添加新子女
		if (parent->firstchild == nullptr)
		{
			parent->firstchild = new node(childName);
			parent->firstchild->parent = parent;
		}
		else
		{
			node* current = parent->firstchild;
			while (current->firstbrother != nullptr)
			{
				current = current->firstbrother;
			}
			current->firstbrother = new node(childName);
			current->firstbrother->parent = parent;
		}

		cout << parentName << "的新儿子（或女儿）" << childName << "已添加。" << endl;
		display_tree(parentName); // 显示更新后的家庭成员
		break; // 成功添加后退出循环
	}
}

void relation_tree::delete_family()
{
	cout << "请输入要解散家庭的人的姓名：";
	char name[50];
	cin >> name;
	node* father = search(root, name);
	if(father==nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;
	display_tree(father->name);
	if(father!=root)
	{
		if(father->parent->firstchild==father)
		{
			father->parent->firstchild = father->firstbrother;
		}
		else
		{
			node* current = father->parent->firstchild;
			while(true)
			{
				if(current->firstbrother==father)
				{
					break;
				}
				else
				{
					current = current->firstbrother;
				}
			}
			current->firstbrother = father->firstbrother;
		}
		delete_tree(father);
    }
	else
	{
		delete_tree(father);
	}
}

void relation_tree::modify_name()
{
	cout << "请输入要更改姓名的人的目前姓名:";
	char name[50];
	cin >> name;
	node* current = search(root, name);
	if(current==nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	while (true)
	{
		char new_name[50];
		cin >> new_name;
		if (search(root, new_name) == nullptr)
		{
			cout << current->name << "已经更改姓名为：" << new_name << endl;
			strcpy(current->name, new_name);
			break;
		}
		else
		{
			cout << "该姓名已经被使用，请更换新的姓名：";
			cin.clear();
			cin.ignore(1024, '\n');

		}
	}
}
char Choice()
{
	cout << endl << "请选择要执行的操作：";
	char ret = '\0';

	// 如果输入的字符不在A-E，要求用户继续输入
	while (true)
	{
		cin >> ret;
		if (cin.fail() || ret < 'A' || ret > 'E') // 若输入变量类型不同或数字不在要求范围内
		{
			cin.clear();
			cin.ignore(1024, '\n');                           // 清除缓存区
			cout << "输入错误，请重新输入：";                                // 给出错误输入的提示
			continue;
		}
		break;
	}
	return ret;
}
 int main()
{
	 printf("**           家谱管理系统            **\n");
	 printf("=======================================\n");
	 printf("**        请选择要执行的选择:        **\n");
	 printf("**           A --- 完善家谱          **\n");
	 printf("**           B --- 添加家庭成员      **\n");
	 printf("**           C --- 解散局部家庭      **\n");
	 printf("**           D --- 更改家庭成员姓名  **\n");
	 printf("**           E --- 退出程序          **\n");
	 printf("***************************************\n");
	 relation_tree tree;
	 tree.build_root();
	 while(true)
	 {
		 char choice = Choice();
		switch(choice)
		{
		case 'A':
			// 以已经存在的节点为根建立一棵树
			tree.build_tree();
			break;
		case 'B':
			// 为已经存在的节点添加一个儿子
			tree.add_family();
			break;
		case 'C':
			// 删除已经存在的节点为根的一棵树
			tree.delete_family();
			break;
		case 'D':
			// 为已经存在的节点更改信息
			tree.modify_name();
			break;
		case 'E':
			// 退出程序
			cout << endl;
			system("pause");
			return 0;
		}
	 }
}