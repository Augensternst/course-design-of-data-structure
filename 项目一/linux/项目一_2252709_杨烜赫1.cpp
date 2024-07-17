#include<iostream>
#include<cstring>
using namespace std;
class List
{
private:
	class link_node
	{
	public:
		int id = 0;
		char name[50] = { 0 };
		char gender[10] = { 0 };
		int age = 0;
		char category[50] = { 0 };
		link_node* next = nullptr;
	};
	link_node* first;
	int stu_num = 0;
public:

	List();
	~List() { make_empty(); };
	void make_empty();
	bool Init_linklist(int n);            //创建最初的考生信息
	void Print(link_node* head);            //打印考生信息    
	bool Research();                   //在表中搜索考生信息
	bool Insert();                          //在表中添加考生信息
	bool Modify();                     //在表中修改已有考生信息
	bool Remove();                   //在表中删除考生信息
	bool Statistics();               //统计考生信息 
};
List::List()
{
	first = new link_node;
}
void List::make_empty()
{
	link_node* q;
	while (first->next != NULL)
	{
		q = first->next;
		first->next = q->next;
		delete q;
	}
}
bool List::Init_linklist(int n)
{
	if (n <= 0)
	{
		cout << "人数不符合要求" << endl;
		return false;
	}
	else
	{
		cout << "请依次输入考生的考号，姓名，性别，年龄，以及报考类别!" << endl;
		stu_num = n;
		link_node* pnew;
		link_node* pcurrent = first;
		for (int i = 0; i < n; i++)
		{
			pnew = new link_node;
			if (pnew == nullptr)
			{
				cout << "内存分配错误" << endl;
				return false;
			}
			cin >> pnew->id >> pnew->name >> pnew->gender >> pnew->age >> pnew->category;
			pnew->next = nullptr;
			pcurrent->next = pnew;
			pcurrent = pnew;
		}
		Print(first);
		return true;

	}
}
void List::Print(link_node* first)
{
	link_node* current = first->next;
	cout << endl;
	cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
	for (int i = 0; i < stu_num; i++)
	{
		cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
		current = current->next;
	}
}
bool List::Insert()
{
	int pos;
	cout << "请输入你要插入的考生的位置：" << endl;
	cin >> pos;

	if (pos < 1 || pos > stu_num + 1)
	{
		cout << "插入位置无效，请重新输入" << endl;
		return false;
	}

	while (true) // 循环直到输入有效的考号
	{
		cout << "请输入你要插入考生的考号，姓名，性别，年龄以及报考类别：" << endl;
		link_node* pnew = new link_node;
		if (pnew == nullptr)
		{
			cout << "内存分配错误" << endl;
			return false;
		}
		cin >> pnew->id >> pnew->name >> pnew->gender >> pnew->age >> pnew->category;

		// 检查考号是否已经存在
		link_node* current = first->next;
		bool id_exists = false;
		while (current != nullptr)
		{
			if (current->id == pnew->id)
			{
				cout << "考号 " << pnew->id << " 已存在，请重新输入！" << endl;
				id_exists = true;
				break;
			}
			current = current->next;
		}

		if (id_exists)
		{
			delete pnew; // 释放新节点的内存
			cin.clear(); // 清除输入缓冲区的错误标记
			cin.ignore(1024, '\n'); // 忽略缓冲区剩余的输入
			continue; // 重新开始循环
		}

		// 执行插入操作
		if (pos == 1)
		{
			pnew->next = first->next;
			first->next = pnew;
		}
		else
		{
			current = first->next;
			for (int i = 1; i < pos - 1; ++i)
			{
				current = current->next;
			}
			pnew->next = current->next;
			current->next = pnew;
		}

		stu_num++;
		Print(first);
		return true;
	}
}


bool List::Remove()
{
	cout << "请输入要删除的考生的考号" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;
	link_node* previous = nullptr;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "你删除的考生信息是：" << current->id << "    " << current->name << "    " << current->gender << "    " << current->age << "   " << current->category << endl;

			if (previous == nullptr)
			{
				// 删除头节点
				first = current->next;
			}
			else
			{
				// 从链表中删除节点
				previous->next = current->next;
			}
			delete current;
			stu_num--;
			Print(first);
			return true;
		}
		previous = current;
		current = current->next;
	}
	cout << "未找到该考号，请重新输入" << endl;
	return false;
}
bool List::Research()
{
	cout << "请输入要查找的考生的考号" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
			cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
			return true; // 找到匹配考号，返回true表示成功
		}

		current = current->next;
	}

	// 未找到匹配考号，给出友好提示
	cout << "未找到该考号，请重新输入" << endl;
	return false;
}
bool List::Modify()
{
	cout << "请输入要修改的考生信息的原有考号" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "考号" << "    " << "姓名" << "    " << "性别" << "    " << "年龄" << "    " << "报考类别" << endl;
			cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
			cout << "请输入修改后该考生的考号，姓名，性别，年龄及报考类别" << endl;
			cin >> current->id >> current->name >> current->gender >> current->age >> current->category;
			cout << "修改后结果为：" << endl;
			Print(first);
			return true; // 找到匹配考号并成功修改
		}
		current = current->next;
	}
	// 未找到匹配考号，给出友好提示
	cout << "未找到该考号，请重新输入" << endl;
	return false;
}
bool List::Statistics()
{
	link_node* current = first->next;
	int total_age = 0;
	int man = 0;
	int woman = 0;
	double average_age = 0.0;

	if (current == nullptr)
	{
		return false;
	}

	// 统计年龄和性别
	for (int i = 0; i < stu_num; i++)
	{
		total_age += current->age;
		if (strcmp(current->gender, "男") == 0)
			man++;
		if (strcmp(current->gender, "女") == 0)
			woman++;
		current = current->next;
	}

	// 计算平均年龄（使用浮点数除法）
	if (stu_num > 0)
	{
		average_age = static_cast<double>(total_age) / stu_num;
	}

	cout << "统计结果如下：" << endl;
	cout << "平均年龄为：" << average_age << endl;
	cout << "男考生数量为：" << man << "，女考生数量为：" << woman << endl;

	// 重新初始化current为链表头
	current = first->next;

	// 使用数组来存储报考类别和对应的人数
	const int max_categories = 50;
	char* categories[max_categories] = { nullptr };
	int category_counts[max_categories] = { 0 };

	for (int i = 0; i < stu_num; i++)
	{
		char* category = current->category;
		if (category != nullptr)
		{
			// 查找该类别是否已经存在
			bool found = false;
			for (int j = 0; j < max_categories; j++)
			{
				if (categories[j] == nullptr)
				{
					categories[j] = category;
					category_counts[j]++;
					found = true;
					break;
				}
				else if (strcmp(categories[j], category) == 0)
				{
					category_counts[j]++;
					found = true;
					break;
				}
			}
			// 如果该类别不存在则忽略
			if (!found)
			{
				cout << "报考类别 " << category << " 超过了最大数量，将被忽略。" << endl;
			}
		}
		current = current->next;
	}

	// 输出报考类别和对应的人数
	for (int i = 0; i < max_categories; i++)
	{
		if (categories[i] != nullptr)
		{
			cout << "报考类别 " << categories[i] << ": " << category_counts[i] << " 人" << endl;
		}
	}

	return true;
}


List examinee;
int input_stu_num()
{
	int n = 0;
	
	cout << "首先请建立考生系统！" << endl;
	cout << "请输入考生人数：";
	while (1)
	{
		cin >> n;
		if (n <= 0 || !cin.good())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl;
			cout << "人数输入错误,请重新输入" << endl;
			continue;
		}
		else
			break;
	}
	return n;

}
void choice()
{
	int choice = 0;
	while (1)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查询，4为修改，5为统计，0为取消操作" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			examinee.Insert();
			break;
		case 2:
			examinee.Remove();
			break;
		case 3:
			examinee.Research();
			break;
		case 4:
			examinee.Modify();
			break;
		case 5:
			examinee.Statistics();
			break;
		case 0:
		{
			cout << "操作结束,感谢使用！" << endl;
			return;
		}
		default:
			cout << "无此操作，请重新输入：" << endl;
		}
	}
}
int main()
{
	int num=input_stu_num();
	examinee.Init_linklist(num);
	choice();
	system("pause");
	return 0;
}