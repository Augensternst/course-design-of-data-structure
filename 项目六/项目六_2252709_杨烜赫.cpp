// ReSharper disable All
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using namespace std;
//ʹ�ú����ֵ������Ƚ����ڵ�
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
	// �вι��캯��
	node(const char* newName, node* newFirstChild = nullptr, node* newFirstBrother = nullptr, node* newParent = nullptr)
	{
		strncpy(name, newName, sizeof(name) - 1); // �����ַ������
		name[sizeof(name) - 1] = '\0'; // ȷ���ַ����� null ��ֹ
		firstchild = newFirstChild;
		firstbrother = newFirstBrother;
		parent = newParent;
	}
};
//����������
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
	void build_root();//�������ڵ�
	void build_tree();//����һ������
	void display_tree(const char* name);//չʾ��ǰ�ڵ�ĺ���
	void add_family();//�����µļ�ͥ
	void delete_family();//��ɢ��ͥ
	void modify_name();//�޸ļ�ͥ��Ա����
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
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	char name[50];
	cin >> name;
	//Ϊ���ڵ㽨���ռ�
	root = new node(name);
	//������
	if(root==nullptr)
	{
		cerr << "�ڴ�������" << endl;
		exit(1);
	}
	//������������
	cout << "�˼������������ǣ�" << root->name << endl;
}

void relation_tree::build_tree()
{
	cout << "�����Ҫ������ͥ���˵�����:";
	char name[50];
	cin >> name;
	node* father = search(root, name);
	if(father==nullptr)
	{
		cout << "�������ڲ����ڸü�ͥ��Ա��" << endl;
		return;
	}
	if(father->firstchild!=nullptr)
	{
		cout << "�ó�Ա�Ѿ���������ͥ��" << endl;
		return;
	}
	cout << "������" << name << "�Ķ�Ů�ĸ���:";
	int child_num;
	while(1)
	{
		cin >> child_num;
		if(child_num<0||!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "�������󣬶�Ů��������Ϊ������" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	cout << "����������" << name << "��Ů��������";
	char child_name[50];
	while(true)
	{
		cin >> child_name;
		if(search(root, child_name)==nullptr)
		{
			father->firstchild = new node(child_name);
			if(father->firstchild==nullptr)
			{
				cerr << "�ڴ�������" << endl;
				exit(1);

			}
			father->firstchild->parent = father;
			break;

		}
		if(search(root, child_name)!=nullptr)
		{
			cout << "��һλ��Ա�Ѿ����ڣ�����������" << endl;
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
					cerr << "�ڴ�������" << endl;
					exit(1);
				}
				current->firstbrother->parent = father;
				break;
			}
			else
			{
				cout << "����Ϊ" << child_name << "��Ա�����ظ������������룡" << endl;
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
	if (current != nullptr && current->firstchild != nullptr) // ȷ��current����������Ů
	{
		cout << name << "�ĵ�һ����Ů�У�";
		node* child = current->firstchild;
		while (child != nullptr) // ����������Ů
		{
			cout << child->name << ' ';
			child = child->firstbrother; // �ƶ�����һ���ֵܽڵ�
		}
		cout << endl;
	}
	else
	{
		cout << name << "û����Ů���߲������ڼ����С�" << endl;
	}
}


void relation_tree::add_family()
{
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	char parentName[50];
	cin >> parentName;
	node* parent = search(root, parentName);
	if (parent == nullptr)
	{
		cout << "�����в����ڸó�Ա��Ϣ" << endl;
		return;
	}

	while (true)
	{
		cout << "������" << parentName << "����Ӷ��ӣ���Ů������������";
		char childName[50];
		cin >> childName;

		if (search(root, childName) != nullptr)
		{
			cout << "�ó�Ա�Ѿ����ڣ����������룡" << endl;
			cin.clear(); // ����������е��������
			cin.ignore(1000, '\n'); // ����֮ǰ�Ĵ�������
			continue; // ����ѭ�����ȴ��µ�����
		}

		// �����Ƿ�������Ů���������Ů
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

		cout << parentName << "���¶��ӣ���Ů����" << childName << "����ӡ�" << endl;
		display_tree(parentName); // ��ʾ���º�ļ�ͥ��Ա
		break; // �ɹ���Ӻ��˳�ѭ��
	}
}

void relation_tree::delete_family()
{
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	char name[50];
	cin >> name;
	node* father = search(root, name);
	if(father==nullptr)
	{
		cout << "�������ڲ����ڸü�ͥ��Ա��" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;
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
	cout << "������Ҫ�����������˵�Ŀǰ����:";
	char name[50];
	cin >> name;
	node* current = search(root, name);
	if(current==nullptr)
	{
		cout << "�������ڲ����ڸü�ͥ��Ա��" << endl;
		return;
	}
	cout << "��������ĺ��������";
	while (true)
	{
		char new_name[50];
		cin >> new_name;
		if (search(root, new_name) == nullptr)
		{
			cout << current->name << "�Ѿ���������Ϊ��" << new_name << endl;
			strcpy(current->name, new_name);
			break;
		}
		else
		{
			cout << "�������Ѿ���ʹ�ã�������µ�������";
			cin.clear();
			cin.ignore(1024, '\n');

		}
	}
}
char Choice()
{
	cout << endl << "��ѡ��Ҫִ�еĲ�����";
	char ret = '\0';

	// ���������ַ�����A-E��Ҫ���û���������
	while (true)
	{
		cin >> ret;
		if (cin.fail() || ret < 'A' || ret > 'E') // ������������Ͳ�ͬ�����ֲ���Ҫ��Χ��
		{
			cin.clear();
			cin.ignore(1024, '\n');                           // ���������
			cout << "����������������룺";                                // ���������������ʾ
			continue;
		}
		break;
	}
	return ret;
}
 int main()
{
	 printf("**           ���׹���ϵͳ            **\n");
	 printf("=======================================\n");
	 printf("**        ��ѡ��Ҫִ�е�ѡ��:        **\n");
	 printf("**           A --- ���Ƽ���          **\n");
	 printf("**           B --- ��Ӽ�ͥ��Ա      **\n");
	 printf("**           C --- ��ɢ�ֲ���ͥ      **\n");
	 printf("**           D --- ���ļ�ͥ��Ա����  **\n");
	 printf("**           E --- �˳�����          **\n");
	 printf("***************************************\n");
	 relation_tree tree;
	 tree.build_root();
	 while(true)
	 {
		 char choice = Choice();
		switch(choice)
		{
		case 'A':
			// ���Ѿ����ڵĽڵ�Ϊ������һ����
			tree.build_tree();
			break;
		case 'B':
			// Ϊ�Ѿ����ڵĽڵ����һ������
			tree.add_family();
			break;
		case 'C':
			// ɾ���Ѿ����ڵĽڵ�Ϊ����һ����
			tree.delete_family();
			break;
		case 'D':
			// Ϊ�Ѿ����ڵĽڵ������Ϣ
			tree.modify_name();
			break;
		case 'E':
			// �˳�����
			cout << endl;
			system("pause");
			return 0;
		}
	 }
}