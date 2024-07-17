#include <iostream>


using namespace std;

const int MAX_SIZE = 1000;

// 定义节点类型
enum Node_Type { Number, Operator };

// 节点信息结构体
struct Node_Info {
    double num_value; // 数值
    char op_char;     // 操作符
    Node_Type type;   // 节点类型

    Node_Info() : num_value(0), op_char('\0'), type(Number) {}
};

// 表达式树节点结构体
struct Expr_Tree_Node {
    Expr_Tree_Node* left_child;  // 左子节点
    Expr_Tree_Node* right_child; // 右子节点
    Node_Info data;              // 节点数据

    Expr_Tree_Node() : left_child(nullptr), right_child(nullptr), data() {}
    Expr_Tree_Node(double num) : left_child(nullptr), right_child(nullptr), data() {
        data.num_value = num;
        data.type = Number;
    }
    Expr_Tree_Node(char op) : left_child(nullptr), right_child(nullptr), data() {
        data.op_char = op;
        data.type = Operator;
    }
};

// 检查字符是否为操作符
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 获取操作符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 将中缀表达式转换为后缀表达式
void infix_to_postfix(char infix[], char postfix[]) {
    char stack[MAX_SIZE]; // 栈存储操作符
    int top = -1;         // 栈顶指针
    int index = 0;        // 后缀表达式的当前索引

    for (int i = 0; infix[i] != '\0'; ++i) {
        char c = infix[i];

        if (isdigit(c) || c == '.') {
            postfix[index++] = c; // 直接添加数字到后缀表达式
        }
        else if (c == '(') {
            stack[++top] = c; // 左括号入栈
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[index++] = ' '; // 添加空格分隔符
                postfix[index++] = stack[top--]; // 添加栈中操作符到后缀表达式
            }
            top--; // 弹出 '('
        }
        else {
            postfix[index++] = ' '; // 添加空格分隔符
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[index++] = stack[top--]; // 弹出栈中优先级更高的操作符
                postfix[index++] = ' ';
            }
            stack[++top] = c; // 当前操作符入栈
        }
    }

    while (top != -1) { // 栈中剩余操作符添加到后缀表达式
        postfix[index++] = ' ';
        postfix[index++] = stack[top--];
    }
    postfix[index] = '\0'; // 字符串结束符
}

// 从后缀表达式构建表达式树
Expr_Tree_Node* construct_tree(char postfix[]) {
    Expr_Tree_Node* stack[MAX_SIZE]; // 栈存储表达式树节点
    Expr_Tree_Node* node;
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char c = postfix[i];

        if (c == ' ') continue; // 忽略空格

        if (!is_operator(c)) {
            char number[20]; // 存储数字字符串
            int j = 0;
            // 读取完整的数字（包括小数点）
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                number[j++] = postfix[i++];
            }
            number[j] = '\0';
            node = new Expr_Tree_Node(atof(number)); // 创建数字节点
            stack[++top] = node; // 节点入栈
        }
        else {
            node = new Expr_Tree_Node(c); // 创建操作符节点
            node->right_child = stack[top--]; // 设置右子节点
            node->left_child = stack[top--];  // 设置左子节点
            stack[++top] = node; // 节点入栈
        }
    }
    return stack[top]; // 返回树的根节点
}

// 前序遍历打印表达式树
void pre_order(Expr_Tree_Node* node) {
    if (node == nullptr) return;
    if (node->data.type == Operator) cout << node->data.op_char << " ";
    else cout << node->data.num_value << " ";
    pre_order(node->left_child);
    pre_order(node->right_child);
}

// 中序遍历打印表达式树
void in_order(Expr_Tree_Node* node, bool is_root = true) {
    if (node == nullptr) return;
    bool needs_parentheses = !is_root && node->data.type == Operator &&
        node->left_child && node->left_child->data.type == Operator &&
        precedence(node->data.op_char) > precedence(node->left_child->data.op_char);

    if (needs_parentheses) cout << "(";

    in_order(node->left_child, false);

    if (node->data.type == Operator) cout << node->data.op_char << " ";
    else cout << node->data.num_value << " ";

    in_order(node->right_child, false);

    if (needs_parentheses) cout << ")";
}

// 后序遍历打印表达式树
void post_order(Expr_Tree_Node* node) {
    if (node == nullptr) return;
    post_order(node->left_child);
    post_order(node->right_child);
    if (node->data.type == Operator) cout << node->data.op_char << " ";
    else cout << node->data.num_value << " ";
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    cout << "请输入表达式(请使用英文括号)： ";
    cin.getline(infix, MAX_SIZE);

    infix_to_postfix(infix, postfix);

    Expr_Tree_Node* root = construct_tree(postfix);
    cout << "波兰表达式： ";
    pre_order(root);
    cout << endl << "中缀表达式： ";
    in_order(root);
    cout << endl << "逆波兰表达式：";
    post_order(root);
    cout << endl;
    system("pause");
    return 0;
}
