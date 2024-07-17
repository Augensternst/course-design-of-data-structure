#include <iostream>
using namespace std;

// ��������������ڵ�
struct BST_Node {
    double value;           // �ڵ�����
    BST_Node* left_child;   // ����
    BST_Node* right_child;  // �Һ���

    // ���캯��
    BST_Node(double val = 0.0) : value(val), left_child(NULL), right_child(NULL) {};
};
// ������������
ostream& operator<<(ostream& os, const BST_Node& node) {
    os << node.value << "->";
    return os;
}

// ���������������
class Binary_Search_Tree {
public:
    Binary_Search_Tree() : root(NULL) {}
    ~Binary_Search_Tree() { Clear_Tree(root); }

    bool Insert_Value(double key);
    BST_Node* Find_Value(BST_Node* bst, double key);
    void Display_InOrder(BST_Node* node);
    BST_Node* Get_Root() { return root; }
    void Clear_Tree(BST_Node* node);

private:
    BST_Node* root;  // ���ڵ�

    void Create_Root_Node(double key);
    void Insert_Node(BST_Node* bst, double key);
};

// �����
void Binary_Search_Tree::Clear_Tree(BST_Node* node) {
    if (node == NULL) return;
    Clear_Tree(node->left_child);
    Clear_Tree(node->right_child);
    delete node;
}

// ����ֵ
bool Binary_Search_Tree::Insert_Value(double key) {
    if (root == NULL) {
        Create_Root_Node(key);
        return true;
    }

    if (Find_Value(root, key) == NULL) {
        Insert_Node(root, key);
        return true;
    }
    else {
        cout << "\n�ڵ� " << key << " �Ѵ���" << endl;
        return false;
    }
}

// ����ֵ
BST_Node* Binary_Search_Tree::Find_Value(BST_Node* bst, double key) {
    if (bst == NULL)
        return NULL;

    if (bst->value == key)
        return bst;

    if (bst->value < key)
        return Find_Value(bst->right_child, key);

    return Find_Value(bst->left_child, key);
}

// �������
void Binary_Search_Tree::Display_InOrder(BST_Node* node) {
    if (node == NULL) return;
    Display_InOrder(node->left_child);
    cout << *node;
    Display_InOrder(node->right_child);
}

// �������ڵ�
void Binary_Search_Tree::Create_Root_Node(double key) {
    root = new BST_Node(key);
    if (root == NULL) {
        cerr << "�ڴ�������" << endl;
        exit(1);
    }
}

// ����ڵ�
void Binary_Search_Tree::Insert_Node(BST_Node* bst, double key) {
    if (key < bst->value) {
        if (bst->left_child != NULL)
            Insert_Node(bst->left_child, key);
        else
            bst->left_child = new BST_Node(key);
    }
    else if (key > bst->value) {
        if (bst->right_child != NULL)
            Insert_Node(bst->right_child, key);
        else
            bst->right_child = new BST_Node(key);
    }
}

// �û����������ѡ��
char GetUserChoice() {
    cout << "\n��ѡ�������";
    char choice = '\0';

    while (true) {
        cin >> choice;
        if (cin.fail() || choice < '1' || choice > '4') {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "����������������룺";
            continue;
        }
        break;
    }
    return choice;
}

int main() {
    cout << "**        ����������      **" << endl;
    cout << "============================" << endl;
    cout << "**    1 -- �������������� **" << endl;
    cout << "**    2 -- ����Ԫ��       **" << endl;
    cout << "**    3 -- ��ѯԪ��       **" << endl;
    cout << "**    4 -- �˳�����       **" << endl;
    cout << "============================" << endl;

    Binary_Search_Tree bst;
    while (true) {
        char ch = GetUserChoice();
        switch (ch) {
        case '1':
            bst.Clear_Tree(bst.Get_Root());
            cout << "���������������Ԫ�ص�ֵ����0��β��" << endl;
            double key;
            while (cin >> key && key != 0.0) {
                bst.Insert_Value(key);
            }
            cout << "\n����������Ԫ�أ�" << endl;
            bst.Display_InOrder(bst.Get_Root());
            break;
        case '2':
            if (bst.Get_Root() == NULL) {
                cout << "���Ƚ���������������" << endl;
            }
            else {
                cout << "������Ҫ�����Ԫ�أ�" << endl;
                cin >> key;
                bst.Insert_Value(key);
                cout << "\n����������Ԫ�أ�" << endl;
                bst.Display_InOrder(bst.Get_Root());
            }
            break;
        case '3':
            if (bst.Get_Root() == NULL) {
                cout << "���Ƚ���������������" << endl;
            }
            else {
                cout << "������Ҫ��ѯ��Ԫ�أ�" << endl;
                cin >> key;
                if (bst.Find_Value(bst.Get_Root(), key))
                    cout << "\n" << key << " �����ڶ����������У�" << endl;
                else
                    cout << "\n" << key << " �������ڶ����������У�" << endl;
            }
            break;
        case '4':
            cout << "�˳�����" << endl;
            exit(0);
        }
    }
    return 0;
}
