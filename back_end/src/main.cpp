#include <iostream>       // 用于输入输出
#include <unordered_map>  // 用于哈希表存储节点映射
#include <vector>         // 用于存储路径和集合
#include <climits>        // 用于INT_MAX和INT_MIN
#include <sstream>        // 用于字符串流处理
#include <string>         // 用于字符串操作
#include <stack>          // 用于路径回溯
using namespace std;

struct nodeinfo
{
    int meter = 0;  // 距离，单位：米
    int time = 0;   // 时间，单位：分钟
};

// 全局变量声明
int num;                        // 节点数量
char node[40] = { '#' };       // 节点字符数组
nodeinfo* pic[40][40] = { nullptr };  // 邻接矩阵存储图
unordered_map<char, int> nodeIndex;   // 节点字符到索引的映射
unordered_map<char, string> nodeNames; // 节点字符到名称的映射

// 初始化节点名称映射
void initNodeNames() {
    // 节点代号与实际名称的对应关系
    nodeNames['A'] = "静远楼";
    nodeNames['B'] = "耘慧楼";
    nodeNames['C'] = "尔雅楼";
    nodeNames['D'] = "实验楼";
    nodeNames['E'] = "学生公寓A";
    nodeNames['F'] = "学生公寓B";
    nodeNames['G'] = "学生公寓C";
    nodeNames['H'] = "一食堂";
    nodeNames['I'] = "二食堂";
    nodeNames['J'] = "图书馆";
    nodeNames['K'] = "太阳石广场";
    nodeNames['L'] = "聚龙湖";
    nodeNames['M'] = "龙首湖";
    nodeNames['N'] = "运动场";
    nodeNames['O'] = "校医院";
    // 可根据需要继续添加更多节点
}

// 显示节点字符和地点对应关系
void displayNodeMap() {
    cout << "          节点字符与地点对应表" << endl;
    cout << "=========================================" << endl;
    cout << "字符 | 地点名称" << endl;

    // 显示预设的节点名称（按预定义的顺序）
    cout << "  A  | 静远楼" << endl;
    cout << "  B  | 耘慧楼" << endl;
    cout << "  C  | 尔雅楼" << endl;
    cout << "  D  | 实验楼" << endl;
    cout << "  E  | 学生公寓A" << endl;
    cout << "  F  | 学生公寓B" << endl;
    cout << "  G  | 学生公寓C" << endl;
    cout << "  H  | 一食堂" << endl;
    cout << "  I  | 二食堂" << endl;
    cout << "  J  | 图书馆" << endl;
    cout << "  K  | 太阳石广场" << endl;
    cout << "  L  | 聚龙湖" << endl;
    cout << "  M  | 龙首湖" << endl;
    cout << "  N  | 运动场" << endl;
    cout << "  O  | 校医院" << endl;
}


// Dijkstra算法 - 计算最短距离路径
vector<char> dijkstraDistance(char start, char end) {
    int startIdx = nodeIndex[start];
    int endIdx = nodeIndex[end];

    vector<int> dist(num, INT_MAX);  // 存储到各节点的最短距离
    vector<int> parent(num, -1);     // 存储路径中的前驱节点
    vector<bool> visited(num, false); // 标记节点是否已访问

    dist[startIdx] = 0;  // 起点到自身的距离为0

    for (int count = 0; count < num - 1; count++) {
        int u = -1;
        int minDist = INT_MAX;

        // 选择未访问节点中距离最小的
        for (int i = 0; i < num; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;  // 所有可达节点都已处理
        visited[u] = true;

        // 更新邻居节点的距离
        for (int v = 0; v < num; v++) {
            if (pic[u][v] != nullptr && !visited[v]) {
                int weight = pic[u][v]->meter;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // 构建路径
    vector<char> path;
    if (dist[endIdx] == INT_MAX) {
        return path;  // 空路径表示不可达
    }

    // 从终点回溯到起点
    int current = endIdx;
    stack<char> tempPath;
    while (current != -1) {
        tempPath.push(node[current]);
        current = parent[current];
    }

    // 反转路径
    while (!tempPath.empty()) {
        path.push_back(tempPath.top());
        tempPath.pop();
    }

    return path;
}

// Dijkstra算法 - 计算最省时路径
vector<char> dijkstraTime(char start, char end) {
    int startIdx = nodeIndex[start];
    int endIdx = nodeIndex[end];

    vector<int> time(num, INT_MAX);   // 存储到各节点的最短时间
    vector<int> parent(num, -1);      // 存储路径中的前驱节点
    vector<bool> visited(num, false); // 标记节点是否已访问

    time[startIdx] = 0;  // 起点到自身的时间为0

    for (int count = 0; count < num - 1; count++) {
        int u = -1;
        int minTime = INT_MAX;

        for (int i = 0; i < num; i++) {
            if (!visited[i] && time[i] < minTime) {
                minTime = time[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < num; v++) {
            if (pic[u][v] != nullptr && !visited[v]) {
                int weight = pic[u][v]->time;
                if (time[u] != INT_MAX && time[u] + weight < time[v]) {
                    time[v] = time[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    vector<char> path;
    if (time[endIdx] == INT_MAX) {
        return path;
    }

    int current = endIdx;
    stack<char> tempPath;
    while (current != -1) {
        tempPath.push(node[current]);
        current = parent[current];
    }

    while (!tempPath.empty()) {
        path.push_back(tempPath.top());
        tempPath.pop();
    }

    return path;
}

// 计算路径总距离
int calculateTotalDistance(const vector<char>& path) {
    int total = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = nodeIndex[path[i]];
        int v = nodeIndex[path[i + 1]];
        if (pic[u][v] != nullptr) {
            total += pic[u][v]->meter;
        }
    }
    return total;
}

// 计算路径总时间
int calculateTotalTime(const vector<char>& path) {
    int total = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = nodeIndex[path[i]];
        int v = nodeIndex[path[i + 1]];
        if (pic[u][v] != nullptr) {
            total += pic[u][v]->time;
        }
    }
    return total;
}

// 显示路径信息
void displayPath(const vector<char>& path, bool showDistance = true, bool showTime = true) {
    if (path.empty()) {
        cout << "路径不存在或无法到达！" << endl;
        return;
    }

    cout << "路径: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (nodeNames.find(path[i]) != nodeNames.end()) {
            cout << "(" << nodeNames[path[i]] << ")";
        }
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    if (showDistance) {
        cout << "总距离: " << calculateTotalDistance(path) << " 米" << endl;
    }
    if (showTime) {
        cout << "总时间: " << calculateTotalTime(path) << " 分钟" << endl;
    }
}

// 多点路径规划
vector<char> multiPointPath(const vector<char>& points) {
    vector<char> fullPath;

    for (size_t i = 0; i < points.size() - 1; i++) {
        vector<char> segment = dijkstraDistance(points[i], points[i + 1]);

        if (segment.empty()) {
            cout << "从 " << points[i] << " 到 " << points[i + 1] << " 无法到达！" << endl;
            return vector<char>();
        }

        // 如果不是第一段，去掉重复的起点
        if (!fullPath.empty()) {
            fullPath.pop_back();
        }

        // 添加这段路径
        for (char c : segment) {
            fullPath.push_back(c);
        }
    }

    return fullPath;
}

// 深度优先搜索，用于连通性检测
void dfs(int u, vector<bool>& visited) {
    visited[u] = true;

    for (int v = 0; v < num; v++) {
        if (pic[u][v] != nullptr && !visited[v]) {
            dfs(v, visited);
        }
    }
}

// 连通性检测功能
void connectivityCheck() {
    if (num == 0) {
        cout << "图中没有节点！" << endl;
        return;
    }

    vector<bool> visited(num, false);

    // 从第一个节点开始DFS遍历
    dfs(0, visited);

    // 检查是否所有节点都被访问
    bool isConnected = true;
    vector<char> disconnectedNodes;

    for (int i = 0; i < num; i++) {
        if (!visited[i]) {
            isConnected = false;
            disconnectedNodes.push_back(node[i]);
        }
    }

    if (isConnected) {
        cout << "图是连通的！所有节点都可以相互到达。" << endl;
    }
    else {
        cout << "图不是连通的！" << endl;
        cout << "无法到达的节点: ";
        for (char c : disconnectedNodes) {
            cout << c;
            if (nodeNames.find(c) != nodeNames.end()) {
                cout << "(" << nodeNames[c] << ")";
            }
            cout << " ";
        }
        cout << endl;
    }
}

// 关键路径分析（最长路径）
vector<char> criticalPathAnalysis(char start, char end) {
    int startIdx = nodeIndex[start];
    int endIdx = nodeIndex[end];

    // 使用动态规划找最长路径（基于距离）
    vector<int> dist(num, INT_MIN);
    vector<int> parent(num, -1);

    dist[startIdx] = 0;

    // 多次松弛操作（处理正权重）
    for (int k = 0; k < num - 1; k++) {
        for (int u = 0; u < num; u++) {
            if (dist[u] == INT_MIN) continue;

            for (int v = 0; v < num; v++) {
                if (pic[u][v] != nullptr) {
                    int weight = pic[u][v]->meter;
                    if (dist[u] + weight > dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // 构建路径
    vector<char> path;
    if (dist[endIdx] == INT_MIN) {
        return path;  // 空路径表示不可达
    }

    // 从终点回溯到起点
    int current = endIdx;
    stack<char> tempPath;
    while (current != -1) {
        tempPath.push(node[current]);
        current = parent[current];
    }

    while (!tempPath.empty()) {
        path.push_back(tempPath.top());
        tempPath.pop();
    }

    return path;
}

// 显示系统菜单
void showMenu() {
    cout << "\n=========================================" << endl;
    cout << "  辽宁工程技术大学校园导航系统" << endl;
    cout << "=========================================" << endl;
    cout << "1. 查询最短距离路径" << endl;
    cout << "2. 查询最省时路径" << endl;
    cout << "3. 多点路径规划" << endl;
    cout << "4. 路径连通性检测" << endl;
    cout << "5. 关键路径分析（最长路径）" << endl;
    cout << "6. 显示所有节点" << endl;
    cout << "7. 退出系统" << endl;
    cout << "=========================================" << endl;
    cout << "请选择功能 (1-7): ";
}

// 显示所有节点信息
void displayAllNodes() {
    cout << "\n当前图中的节点：" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < num; i++) {
        cout << i + 1 << ". " << node[i] << " - ";
        if (nodeNames.find(node[i]) != nodeNames.end()) {
            cout << nodeNames[node[i]];
        }
        else {
            cout << "未命名节点";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
}

// 初始化节点数组
int init(char* node)
{
    for (int i = 0; i < 40; i++)
    {
        node[i] = '#';
    }
    int num = 0;
    cout << "请输入节点数: ";
    cin >> num;
    cout << "请输入节点的内容符号（用单个字符表示，如A,B,C）:" << endl;
    for (int i = 0; i < num; i++)
    {
        cin >> node[i];
    }
    return num;
}

// 创建图结构
void creat(char* node, nodeinfo* pic[][40], int num)
{
    char temp = '#';
    string b;

    // 建立节点字符到索引的映射
    for (int i = 0; i < num; i++)
    {
        nodeIndex[node[i]] = i;
    }

    // 初始化邻接矩阵
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            pic[i][j] = nullptr;
        }
    }

    cin.ignore();

    // 输入边的信息
    for (int i = 0; i < num; i++)
    {
        cout << "请输入与 " << node[i] << " 相连的节点（用空格分隔，如A B C）: ";
        getline(cin, b);
        stringstream a(b);
        while (a >> temp)
        {
            nodeinfo* site;
            site = new nodeinfo;
            cout << "请输入" << node[i] << "到" << temp << "的距离(米)和时间(分钟): ";
            cin >> site->meter >> site->time;
            cin.ignore();
            int j = nodeIndex[temp];
            pic[i][j] = site;
        }
    }
    cout << "校园地图数据存储成功！" << endl;
}

// 主函数
int main()
{
    cout << "=========================================" << endl;
    cout << "  辽宁工程技术大学校园导航系统初始化" << endl;
    cout << "=========================================" << endl;

    // 初始化节点名称映射
    initNodeNames();

    //展示图表
    displayNodeMap();

    // 初始化图结构
    num = init(node);
    creat(node, pic, num);

    // 进入主菜单循环
    int choice;
    char start, end;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: { // 最短距离路径
            cout << "请输入起点和终点（用空格分隔，如A B）: ";
            cin >> start >> end;
            vector<char> path = dijkstraDistance(start, end);
            cout << "\n最短距离路径：" << endl;
            displayPath(path, true, true);
            break;
        }
        case 2: { // 最省时路径
            cout << "请输入起点和终点（用空格分隔，如A B）: ";
            cin >> start >> end;
            vector<char> path = dijkstraTime(start, end);
            cout << "\n最省时路径：" << endl;
            displayPath(path, true, true);
            break;
        }
        case 3: { // 多点路径规划
            int pointCount;
            cout << "请输入要经过的节点数量: ";
            cin >> pointCount;
            vector<char> points(pointCount);
            cout << "请按顺序输入节点（用空格分隔）: ";
            for (int i = 0; i < pointCount; i++) {
                cin >> points[i];
            }
            vector<char> path = multiPointPath(points);
            cout << "\n多点路径规划：" << endl;
            if (!path.empty()) {
                displayPath(path, true, true);
            }
            break;
        }
        case 4: { // 连通性检测
            cout << "\n路径连通性检测：" << endl;
            connectivityCheck();
            break;
        }
        case 5: { // 关键路径分析
            cout << "请输入起点和终点（用空格分隔，如A B）: ";
            cin >> start >> end;
            vector<char> path = criticalPathAnalysis(start, end);
            cout << "\n关键路径分析（最长路径）：" << endl;
            if (!path.empty()) {
                displayPath(path, true, true);
                cout << "说明：关键路径是从起点到终点的最长路径，适用于需要" << endl;
                cout << "      全面考察校园或规划最长游览路线的情况。" << endl;
            }
            else {
                cout << "无法找到从 " << start << " 到 " << end << " 的路径！" << endl;
            }
            break;
        }
        case 6: { // 显示所有节点
            displayAllNodes();
            break;
        }
        case 7: { // 退出系统
            cout << "\n感谢使用辽宁工程技术大学校园导航系统！" << endl;
            cout << "祝您在校园中学习生活愉快！" << endl;
            break;
        }
        default: {
            cout << "无效的选择，请重新输入！" << endl;
            break;
        }
        }

        if (choice != 7) {
            cout << "\n按Enter键继续...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 7);

    // 释放动态分配的内存
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            if (pic[i][j] != nullptr) {
                delete pic[i][j];
            }
        }
    }

    return 0;
}