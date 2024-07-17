#include <iostream>
using namespace std;

// �������ӵı�
struct Connection {
    Connection() : start(-1), end(-1), weight(0) {}
    int start;  // ���
    int end;    // �յ�
    double weight;  // �ߵ�Ȩ��
    bool operator<(const Connection& other) { return weight < other.weight; }
    bool operator>(const Connection& other) { return weight > other.weight; }
};

// ���綥��
struct Node {
    Node() : label(""), root(-1) {}
    string label;  // ��������
    int root;      // �����ڲ��鼯�еĸ��ڵ�
};

// ��������ģ�庯��
template<typename T>
void quick_sort(T arr[], int left, int right) {
    if (left > right) return;
    T pivot = arr[(left + right) / 2];  // ѡ���м�ֵ��Ϊ����
    int i = left, j = right;
    while (i < j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);  // ��������Ԫ��
            i++;
            j--;
        }
    }
    if (left < j) quick_sort(arr, left, j);  // ����߲��ֽ��п�������
    if (i < right) quick_sort(arr, i, right); // ���ұ߲��ֽ��п�������
}

class PowerGrid {
    template<typename T>
    friend void quick_sort(T arr[], int left, int right);

public:
    PowerGrid(int v = 0, int e = 0) : node_count(v), edge_count(e) {
        nodes = nullptr, connections = nullptr;
        min_span_tree = nullptr;
        nodes = new Node[v]; connections = new Connection[e];
    }

    ~PowerGrid() {
        delete[] connections;
        delete[] nodes;
        delete min_span_tree;
    }

    // Kruskal�㷨ʵ����С������
    bool kruskal_algorithm() {
        quick_sort(connections, 0, edge_count - 1);

        delete min_span_tree;
        min_span_tree = nullptr;

        min_span_tree = new PowerGrid(node_count, node_count - 1);

        int selected_edges = 0;
        for (int i = 0; i < edge_count; i++) {
            int ancestor1 = find_root(connections[i].start);
            int ancestor2 = find_root(connections[i].end);

            if (ancestor1 != ancestor2) {
                selected_edges++;
                nodes[ancestor1].root = ancestor2;
                min_span_tree->connections[selected_edges - 1] = connections[i];
            }
            if (selected_edges == node_count - 1) {
                cout << endl;
                return true;
            }
        }

        delete min_span_tree;
        min_span_tree = nullptr;
        cout << endl;
        return false;
    }

    // ��ʼ������
    void initialize_nodes() {
        reset_graph();

        cout << "�����붥���������";
        while (true)
        {
            cin >> node_count;
            if (node_count < 1 || node_count>1024 || !cin.good())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "��������Ӧ����1-1024֮�䣬���������룺";
                continue;

            }
            else
            {
                break;
            }
        }
        nodes = new Node[node_count];

        cout << "���������붥�����ƣ�" << endl;
        for (int i = 0; i < node_count; ++i) {
            string node_name;
            cin >> node_name;
            if (find_node(node_name) != -1) {
                cout << "���� " << node_name << " �Ѵ��ڣ����������룺";
                i--;
            }
            else {
                nodes[i].label = node_name;
                nodes[i].root = i;
            }
        }
    }

    // ��ʼ����
    void initialize_edges() {
        delete[] connections;

        cin.clear();
        cin.ignore(1024, '\n');

        cout << "������ߵ�������";
        while (true)
        {
            cin >> edge_count;
            if (edge_count < 1 || edge_count>node_count * (node_count - 1) / 2 || !cin.good())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "�ߵ���������ȷ�����������룺";
                continue;
            }
            else
            {
                break;
            }
        }
        connections = new Connection[edge_count];

        cout << "����������ߵ���㡢�յ��Ȩ�أ�" << endl;
        for (int i = 0; i < edge_count; i++) {
            cout << "����� " << i + 1 << " ������Ϣ��";
            string start, end;
            double weight;
            cin >> start >> end;
            connections[i].start = find_node(start);
            connections[i].end = find_node(end);

            if (connections[i].start == -1 || connections[i].end == -1) {
                cout << "�ߵ���Ϣ����������������룺" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                i--;
                continue;
            }

            cin >> weight;
            if (cin.fail() || weight <= 0) {
                cout << "Ȩ������������������룺" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                i--;
                continue;
            }
            connections[i].weight = weight;
        }
    }

    // ��ӡ��С������
    void print_min_span_tree() {
        if (min_span_tree == nullptr) {
            cout << "��С������δ���ɣ��������ɣ�" << endl << endl;
            return;
        }

        cout << "��С��������Ϣ���£�" << endl;
        for (int i = 0; i < min_span_tree->edge_count; i++)
            cout << "��� <" << nodes[min_span_tree->connections[i].start].label
            << "> �յ� <" << nodes[min_span_tree->connections[i].end].label
            << "> Ȩ�أ�" << min_span_tree->connections[i].weight << endl;

        cout << endl;
    }

private:
    // ��������ͼ
    void reset_graph() {
        node_count = 0, edge_count = 0;
        if (connections != nullptr) delete[] connections;
        if (nodes != nullptr) delete[] nodes;
        connections = nullptr, nodes = nullptr;
    }

    // �������Ʋ��Ҷ���
    int find_node(const string& name) {
        for (int i = 0; i < node_count; i++) {
            if (nodes[i].label == name)
                return i;
        }
        return -1;
    }

    // �ڲ��鼯�в��Ҷ���ĸ�
    int find_root(int index) {
        if (index == nodes[index].root) return index;
        return nodes[index].root = find_root(nodes[index].root);
    }

    PowerGrid* min_span_tree;  // ָ����С��������ָ��
    int node_count, edge_count;  // ���������ͱߵ�����
    Connection* connections;  // �ߵ�����
    Node* nodes;  // ���������
};

// ��ȡ�û��˵�ѡ��
char get_menu_choice() {
    cout << endl << "��ѡ�������";
    char choice = '\0';

    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 'A' || choice > 'E') {
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
    cout << "**    �������ģ��ϵͳ    **" << endl;
    cout << "============================" << endl;
    cout << "**    A---������������    **" << endl;
    cout << "**    B---��ӵ����ı�    **" << endl;
    cout << "**    C---������С������  **" << endl;
    cout << "**    D---��ʾ��С������  **" << endl;
    cout << "**    E---�˳�����       **" << endl;
    cout << "============================" << endl;

    PowerGrid power_grid;
    while (true) {
        char ch = get_menu_choice();
        switch (ch) {
        case 'A':
            power_grid.initialize_nodes();
            break;
        case 'B':
            power_grid.initialize_edges();
            break;
        case 'C':
            if (power_grid.kruskal_algorithm()) cout << "��������С��������" << endl;
            else cout << "�޷�������С��������";
            break;
        case 'D':
            power_grid.print_min_span_tree();
            break;
        case 'E':
            system("pause");
            return 0;
        }
    }
}
