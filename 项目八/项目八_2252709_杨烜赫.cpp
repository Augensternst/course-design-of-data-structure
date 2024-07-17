#include <iostream>
using namespace std;

// 网络连接的边
struct Connection {
    Connection() : start(-1), end(-1), weight(0) {}
    int start;  // 起点
    int end;    // 终点
    double weight;  // 边的权重
    bool operator<(const Connection& other) { return weight < other.weight; }
    bool operator>(const Connection& other) { return weight > other.weight; }
};

// 网络顶点
struct Node {
    Node() : label(""), root(-1) {}
    string label;  // 顶点名称
    int root;      // 顶点在并查集中的根节点
};

// 快速排序模板函数
template<typename T>
void quick_sort(T arr[], int left, int right) {
    if (left > right) return;
    T pivot = arr[(left + right) / 2];  // 选择中间值作为枢轴
    int i = left, j = right;
    while (i < j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);  // 交换两个元素
            i++;
            j--;
        }
    }
    if (left < j) quick_sort(arr, left, j);  // 对左边部分进行快速排序
    if (i < right) quick_sort(arr, i, right); // 对右边部分进行快速排序
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

    // Kruskal算法实现最小生成树
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

    // 初始化顶点
    void initialize_nodes() {
        reset_graph();

        cout << "请输入顶点的数量：";
        while (true)
        {
            cin >> node_count;
            if (node_count < 1 || node_count>1024 || !cin.good())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "顶点数量应该在1-1024之间，请重新输入：";
                continue;

            }
            else
            {
                break;
            }
        }
        nodes = new Node[node_count];

        cout << "请依次输入顶点名称：" << endl;
        for (int i = 0; i < node_count; ++i) {
            string node_name;
            cin >> node_name;
            if (find_node(node_name) != -1) {
                cout << "顶点 " << node_name << " 已存在，请重新输入：";
                i--;
            }
            else {
                nodes[i].label = node_name;
                nodes[i].root = i;
            }
        }
    }

    // 初始化边
    void initialize_edges() {
        delete[] connections;

        cin.clear();
        cin.ignore(1024, '\n');

        cout << "请输入边的数量：";
        while (true)
        {
            cin >> edge_count;
            if (edge_count < 1 || edge_count>node_count * (node_count - 1) / 2 || !cin.good())
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "边的数量不正确，请重新输入：";
                continue;
            }
            else
            {
                break;
            }
        }
        connections = new Connection[edge_count];

        cout << "请依次输入边的起点、终点和权重：" << endl;
        for (int i = 0; i < edge_count; i++) {
            cout << "输入第 " << i + 1 << " 条边信息：";
            string start, end;
            double weight;
            cin >> start >> end;
            connections[i].start = find_node(start);
            connections[i].end = find_node(end);

            if (connections[i].start == -1 || connections[i].end == -1) {
                cout << "边的信息输入错误，请重新输入：" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                i--;
                continue;
            }

            cin >> weight;
            if (cin.fail() || weight <= 0) {
                cout << "权重输入错误，请重新输入：" << endl;
                cin.clear();
                cin.ignore(1024, '\n');
                i--;
                continue;
            }
            connections[i].weight = weight;
        }
    }

    // 打印最小生成树
    void print_min_span_tree() {
        if (min_span_tree == nullptr) {
            cout << "最小生成树未生成，请先生成！" << endl << endl;
            return;
        }

        cout << "最小生成树信息如下：" << endl;
        for (int i = 0; i < min_span_tree->edge_count; i++)
            cout << "起点 <" << nodes[min_span_tree->connections[i].start].label
            << "> 终点 <" << nodes[min_span_tree->connections[i].end].label
            << "> 权重：" << min_span_tree->connections[i].weight << endl;

        cout << endl;
    }

private:
    // 重置网络图
    void reset_graph() {
        node_count = 0, edge_count = 0;
        if (connections != nullptr) delete[] connections;
        if (nodes != nullptr) delete[] nodes;
        connections = nullptr, nodes = nullptr;
    }

    // 根据名称查找顶点
    int find_node(const string& name) {
        for (int i = 0; i < node_count; i++) {
            if (nodes[i].label == name)
                return i;
        }
        return -1;
    }

    // 在并查集中查找顶点的根
    int find_root(int index) {
        if (index == nodes[index].root) return index;
        return nodes[index].root = find_root(nodes[index].root);
    }

    PowerGrid* min_span_tree;  // 指向最小生成树的指针
    int node_count, edge_count;  // 顶点数量和边的数量
    Connection* connections;  // 边的数组
    Node* nodes;  // 顶点的数组
};

// 获取用户菜单选择
char get_menu_choice() {
    cout << endl << "请选择操作：";
    char choice = '\0';

    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 'A' || choice > 'E') {
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
    cout << "**    电网造价模拟系统    **" << endl;
    cout << "============================" << endl;
    cout << "**    A---创建电网顶点    **" << endl;
    cout << "**    B---添加电网的边    **" << endl;
    cout << "**    C---构建最小生成树  **" << endl;
    cout << "**    D---显示最小生成树  **" << endl;
    cout << "**    E---退出程序       **" << endl;
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
            if (power_grid.kruskal_algorithm()) cout << "已生成最小生成树！" << endl;
            else cout << "无法生成最小生成树！";
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
