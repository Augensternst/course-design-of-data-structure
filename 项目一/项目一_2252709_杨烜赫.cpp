#include<iostream>
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
	bool Init_linklist(int n);            //��������Ŀ�����Ϣ
	void Print(link_node* head);            //��ӡ������Ϣ    
	bool Research();                   //�ڱ�������������Ϣ
	bool Insert();                          //�ڱ�����ӿ�����Ϣ
	bool Modify();                     //�ڱ����޸����п�����Ϣ
	bool Remove();                   //�ڱ���ɾ��������Ϣ
	bool Statistics();               //ͳ�ƿ�����Ϣ 
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
		cout << "����������Ҫ��" << endl;
		return false;
	}
	else
	{
		cout << "���������뿼���Ŀ��ţ��������Ա����䣬�Լ��������!" << endl;
		stu_num = n;
		link_node* pnew;
		link_node* pcurrent = first;
		for (int i = 0; i < n; i++)
		{
			pnew = new link_node;
			if (pnew == nullptr)
			{
				cout << "�ڴ�������" << endl;
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
	cout << "����" << "    " << "����" << "    " << "�Ա�" << "    " << "����" << "    " << "�������" << endl;
	for (int i = 0; i < stu_num; i++)
	{
		cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
		current = current->next;
	}
}
bool List::Insert()
{
	int pos;
	cout << "��������Ҫ����Ŀ�����λ�ã�" << endl;
	cin >> pos;

	if (pos < 1 || pos > stu_num + 1)
	{
		cout << "����λ����Ч������������" << endl;
		return false;
	}

	while (true) // ѭ��ֱ��������Ч�Ŀ���
	{
		cout << "��������Ҫ���뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
		link_node* pnew = new link_node;
		if (pnew == nullptr)
		{
			cout << "�ڴ�������" << endl;
			return false;
		}
		cin >> pnew->id >> pnew->name >> pnew->gender >> pnew->age >> pnew->category;

		// ��鿼���Ƿ��Ѿ�����
		link_node* current = first->next;
		bool id_exists = false;
		while (current != nullptr)
		{
			if (current->id == pnew->id)
			{
				cout << "���� " << pnew->id << " �Ѵ��ڣ����������룡" << endl;
				id_exists = true;
				break;
			}
			current = current->next;
		}

		if (id_exists)
		{
			delete pnew; // �ͷ��½ڵ���ڴ�
			cin.clear(); // ������뻺�����Ĵ�����
			cin.ignore(1024, '\n'); // ���Ի�����ʣ�������
			continue; // ���¿�ʼѭ��
		}

		// ִ�в������
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
	cout << "������Ҫɾ���Ŀ����Ŀ���" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;
	link_node* previous = nullptr;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << current->id << "    " << current->name << "    " << current->gender << "    " << current->age << "   " << current->category << endl;

			if (previous == nullptr)
			{
				// ɾ��ͷ�ڵ�
				first = current->next;
			}
			else
			{
				// ��������ɾ���ڵ�
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
	cout << "δ�ҵ��ÿ��ţ�����������" << endl;
	return false;
}
bool List::Research()
{
	cout << "������Ҫ���ҵĿ����Ŀ���" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "����" << "    " << "����" << "    " << "�Ա�" << "    " << "����" << "    " << "�������" << endl;
			cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
			return true; // �ҵ�ƥ�俼�ţ�����true��ʾ�ɹ�
		}

		current = current->next;
	}

	// δ�ҵ�ƥ�俼�ţ������Ѻ���ʾ
	cout << "δ�ҵ��ÿ��ţ�����������" << endl;
	return false;
}
bool List::Modify()
{
	cout << "������Ҫ�޸ĵĿ�����Ϣ��ԭ�п���" << endl;
	int stu_id;
	cin >> stu_id;

	link_node* current = first;

	while (current != nullptr)
	{
		if (stu_id == current->id)
		{
			cout << "����" << "    " << "����" << "    " << "�Ա�" << "    " << "����" << "    " << "�������" << endl;
			cout << current->id << "       " << current->name << "    " << current->gender << "      " << current->age << "      " << current->category << endl;
			cout << "�������޸ĺ�ÿ����Ŀ��ţ��������Ա����估�������" << endl;
			cin >> current->id >> current->name >> current->gender >> current->age >> current->category;
			cout << "�޸ĺ���Ϊ��" << endl;
			Print(first);
			return true; // �ҵ�ƥ�俼�Ų��ɹ��޸�
		}
		current = current->next;
	}
	// δ�ҵ�ƥ�俼�ţ������Ѻ���ʾ
	cout << "δ�ҵ��ÿ��ţ�����������" << endl;
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

	// ͳ��������Ա�
	for (int i = 0; i < stu_num; i++)
	{
		total_age += current->age;
		if (strcmp(current->gender, "��") == 0)
			man++;
		if (strcmp(current->gender, "Ů") == 0)
			woman++;
		current = current->next;
	}

	// ����ƽ�����䣨ʹ�ø�����������
	if (stu_num > 0)
	{
		average_age = static_cast<double>(total_age) / stu_num;
	}

	cout << "ͳ�ƽ�����£�" << endl;
	cout << "ƽ������Ϊ��" << average_age << endl;
	cout << "�п�������Ϊ��" << man << "��Ů��������Ϊ��" << woman << endl;

	// ���³�ʼ��currentΪ����ͷ
	current = first->next;

	// ʹ���������洢�������Ͷ�Ӧ������
	const int max_categories = 50;
	char* categories[max_categories] = { nullptr };
	int category_counts[max_categories] = { 0 };

	for (int i = 0; i < stu_num; i++)
	{
		char* category = current->category;
		if (category != nullptr)
		{
			// ���Ҹ�����Ƿ��Ѿ�����
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
			// �������𲻴��������
			if (!found)
			{
				cout << "������� " << category << " ����������������������ԡ�" << endl;
			}
		}
		current = current->next;
	}

	// ����������Ͷ�Ӧ������
	for (int i = 0; i < max_categories; i++)
	{
		if (categories[i] != nullptr)
		{
			cout << "������� " << categories[i] << ": " << category_counts[i] << " ��" << endl;
		}
	}

	return true;
}


List examinee;
int input_stu_num()
{
	int n = 0;
	
	cout << "�����뽨������ϵͳ��" << endl;
	cout << "�����뿼��������";
	while (1)
	{
		cin >> n;
		if (n <= 0 || !cin.good())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl;
			cout << "�����������,����������" << endl;
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
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ��ѯ��4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������" << endl;
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
			cout << "��������,��лʹ�ã�" << endl;
			return;
		}
		default:
			cout << "�޴˲��������������룺" << endl;
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