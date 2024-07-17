#include <iostream>


using namespace std;

const int MAX_SIZE = 1000;

// ����ڵ�����
enum Node_Type { Number, Operator };

// �ڵ���Ϣ�ṹ��
struct Node_Info {
    double num_value; // ��ֵ
    char op_char;     // ������
    Node_Type type;   // �ڵ�����

    Node_Info() : num_value(0), op_char('\0'), type(Number) {}
};

// ���ʽ���ڵ�ṹ��
struct Expr_Tree_Node {
    Expr_Tree_Node* left_child;  // ���ӽڵ�
    Expr_Tree_Node* right_child; // ���ӽڵ�
    Node_Info data;              // �ڵ�����

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

// ����ַ��Ƿ�Ϊ������
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// ��ȡ���������ȼ�
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ����׺���ʽת��Ϊ��׺���ʽ
void infix_to_postfix(char infix[], char postfix[]) {
    char stack[MAX_SIZE]; // ջ�洢������
    int top = -1;         // ջ��ָ��
    int index = 0;        // ��׺���ʽ�ĵ�ǰ����

    for (int i = 0; infix[i] != '\0'; ++i) {
        char c = infix[i];

        if (isdigit(c) || c == '.') {
            postfix[index++] = c; // ֱ��������ֵ���׺���ʽ
        }
        else if (c == '(') {
            stack[++top] = c; // ��������ջ
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[index++] = ' '; // ��ӿո�ָ���
                postfix[index++] = stack[top--]; // ���ջ�в���������׺���ʽ
            }
            top--; // ���� '('
        }
        else {
            postfix[index++] = ' '; // ��ӿո�ָ���
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[index++] = stack[top--]; // ����ջ�����ȼ����ߵĲ�����
                postfix[index++] = ' ';
            }
            stack[++top] = c; // ��ǰ��������ջ
        }
    }

    while (top != -1) { // ջ��ʣ���������ӵ���׺���ʽ
        postfix[index++] = ' ';
        postfix[index++] = stack[top--];
    }
    postfix[index] = '\0'; // �ַ���������
}

// �Ӻ�׺���ʽ�������ʽ��
Expr_Tree_Node* construct_tree(char postfix[]) {
    Expr_Tree_Node* stack[MAX_SIZE]; // ջ�洢���ʽ���ڵ�
    Expr_Tree_Node* node;
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; ++i) {
        char c = postfix[i];

        if (c == ' ') continue; // ���Կո�

        if (!is_operator(c)) {
            char number[20]; // �洢�����ַ���
            int j = 0;
            // ��ȡ���������֣�����С���㣩
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                number[j++] = postfix[i++];
            }
            number[j] = '\0';
            node = new Expr_Tree_Node(atof(number)); // �������ֽڵ�
            stack[++top] = node; // �ڵ���ջ
        }
        else {
            node = new Expr_Tree_Node(c); // �����������ڵ�
            node->right_child = stack[top--]; // �������ӽڵ�
            node->left_child = stack[top--];  // �������ӽڵ�
            stack[++top] = node; // �ڵ���ջ
        }
    }
    return stack[top]; // �������ĸ��ڵ�
}

// ǰ�������ӡ���ʽ��
void pre_order(Expr_Tree_Node* node) {
    if (node == nullptr) return;
    if (node->data.type == Operator) cout << node->data.op_char << " ";
    else cout << node->data.num_value << " ";
    pre_order(node->left_child);
    pre_order(node->right_child);
}

// ���������ӡ���ʽ��
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

// ���������ӡ���ʽ��
void post_order(Expr_Tree_Node* node) {
    if (node == nullptr) return;
    post_order(node->left_child);
    post_order(node->right_child);
    if (node->data.type == Operator) cout << node->data.op_char << " ";
    else cout << node->data.num_value << " ";
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    cout << "��������ʽ(��ʹ��Ӣ������)�� ";
    cin.getline(infix, MAX_SIZE);

    infix_to_postfix(infix, postfix);

    Expr_Tree_Node* root = construct_tree(postfix);
    cout << "�������ʽ�� ";
    pre_order(root);
    cout << endl << "��׺���ʽ�� ";
    in_order(root);
    cout << endl << "�沨�����ʽ��";
    post_order(root);
    cout << endl;
    system("pause");
    return 0;
}
