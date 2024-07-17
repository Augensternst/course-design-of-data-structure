#include <iostream>
using namespace std;

// 定义二叉搜索树节点
struct BST_Node {
    double value;           // 节点数据
    BST_Node* left_child;   // 左孩子
    BST_Node* right_child;  // 右孩子

    // 构造函数
    BST_Node(double val = 0.0) : value(val), left_child(NULL), right_child(NULL) {};
};
// 重载输出运算符
ostream& operator<<(ostream& os, const BST_Node& node) {
    os << node.value << "->";
    return os;
}

// 定义二叉搜索树类
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
    BST_Node* root;  // 根节点

    void Create_Root_Node(double key);
    void Insert_Node(BST_Node* bst, double key);
};

// 清空树
void Binary_Search_Tree::Clear_Tree(BST_Node* node) {
    if (node == NULL) return;
    Clear_Tree(node->left_child);
    Clear_Tree(node->right_child);
    delete node;
}

// 插入值
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
        cout << "\n节点 " << key << " 已存在" << endl;
        return false;
    }
}

// 查找值
BST_Node* Binary_Search_Tree::Find_Value(BST_Node* bst, double key) {
    if (bst == NULL)
        return NULL;

    if (bst->value == key)
        return bst;

    if (bst->value < key)
        return Find_Value(bst->right_child, key);

    return Find_Value(bst->left_child, key);
}

// 中序遍历
void Binary_Search_Tree::Display_InOrder(BST_Node* node) {
    if (node == NULL) return;
    Display_InOrder(node->left_child);
    cout << *node;
    Display_InOrder(node->right_child);
}

// 创建根节点
void Binary_Search_Tree::Create_Root_Node(double key) {
    root = new BST_Node(key);
    if (root == NULL) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
}

// 插入节点
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

// 用户界面与操作选择
char GetUserChoice() {
    cout << "\n请选择操作：";
    char choice = '\0';

    while (true) {
        cin >> choice;
        if (cin.fail() || choice < '1' || choice > '4') {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入错误，请重新输入：";
            continue;
        }
        break;
    }
    return choice;
}

int main() {
    cout << "**        二叉排序树      **" << endl;
    cout << "============================" << endl;
    cout << "**    1 -- 建立二叉排序树 **" << endl;
    cout << "**    2 -- 插入元素       **" << endl;
    cout << "**    3 -- 查询元素       **" << endl;
    cout << "**    4 -- 退出程序       **" << endl;
    cout << "============================" << endl;

    Binary_Search_Tree bst;
    while (true) {
        char ch = GetUserChoice();
        switch (ch) {
        case '1':
            bst.Clear_Tree(bst.Get_Root());
            cout << "请输入二叉排序树元素的值，以0结尾：" << endl;
            double key;
            while (cin >> key && key != 0.0) {
                bst.Insert_Value(key);
            }
            cout << "\n二叉排序树元素：" << endl;
            bst.Display_InOrder(bst.Get_Root());
            break;
        case '2':
            if (bst.Get_Root() == NULL) {
                cout << "请先建立二叉搜索树！" << endl;
            }
            else {
                cout << "请输入要插入的元素：" << endl;
                cin >> key;
                bst.Insert_Value(key);
                cout << "\n二叉排序树元素：" << endl;
                bst.Display_InOrder(bst.Get_Root());
            }
            break;
        case '3':
            if (bst.Get_Root() == NULL) {
                cout << "请先建立二叉搜索树！" << endl;
            }
            else {
                cout << "请输入要查询的元素：" << endl;
                cin >> key;
                if (bst.Find_Value(bst.Get_Root(), key))
                    cout << "\n" << key << " 存在于二叉搜索树中！" << endl;
                else
                    cout << "\n" << key << " 不存在于二叉搜索树中！" << endl;
            }
            break;
        case '4':
            cout << "退出程序" << endl;
            exit(0);
        }
    }
    return 0;
}
