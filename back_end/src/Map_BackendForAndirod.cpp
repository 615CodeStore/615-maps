#include "Map_BackendForAndirod.h"
#include<unordered_map>
#include <string> 
#include <vector>
#include <climits>
#include<stack>
#include <cstdio>

struct nodeinfo
{
    float meter = 0;  // 距离，单位：米
};





int num;
char node[50] = { '#' };
std::unordered_map<char, int> NodeIndex;
std::unordered_map<char, std::string> NodeNames;
nodeinfo* pic[50][50] = { nullptr };



//暂时未完成
void initNodeNames() 
{
    NodeNames['A'] = "jingyuan";
}
//暂时未完成




//计算最短路径
std::vector<char> dijkstraDistance(char start, char end) 
{
    int startIdx = NodeIndex[start];
    int endIdx = NodeIndex[end];

    std::vector<float> dist(num, FLT_MAX);  // 存储到各节点的最短距离
    std::vector<int> parent(num, -1);     // 存储路径中的前驱节点
    std::vector<bool> visited(num, false); // 标记节点是否已访问

    dist[startIdx] = 0;  // 起点到自身的距离为0

    for (int count = 0; count < num - 1; count++) {
        int u = -1;
        float minDist = FLT_MAX;

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
                float weight = pic[u][v]->meter;
                if (dist[u] != FLT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // 构建路径
    std::vector<char> path;
    if (dist[endIdx] == FLT_MAX) {
        return path;  
    }

    int current = endIdx;
    std::stack<char> tempPath;
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







// 计算路径总距离
float calculateTotalDistance(const std::vector<char>& path) 
{
    float total = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = NodeIndex[path[i]];
        int v = NodeIndex[path[i + 1]];
        if (pic[u][v] != nullptr) {
            total += pic[u][v]->meter;
        }
    }
    return total;
}






std::string outputJson(const std::vector<char>& path,float speed)
{
    if (path.empty()) {
        return "{\"error\": \"No path found\"}";
    }

    // 计算总距离
    float totalDistance = calculateTotalDistance(path);

    // 计算时间（秒），并保留两位小数
    float time = totalDistance / speed;

    // 构建JSON字符串
    std::string json = "{";

    // 起点和终点
    json += "\"start\":\"" + NodeNames[path[0]] + "\",";
    json += "\"end\":\"" + NodeNames[path.back()] + "\",";

    // 路径数组
    json += "\"path\":[";
    for (size_t i = 0; i < path.size(); i++) {
        json += "\"" + NodeNames[path[i]] + "\"";
        if (i < path.size() - 1) {
            json += ",";
        }
    }
    json += "],";

    // 距离（保留两位小数）
    char distanceStr[20];
    sprintf(distanceStr, "%.2f", totalDistance);
    json += "\"distance\":" + std::string(distanceStr) + ",";

    // 时间（保留两位小数）
    char timeStr[20];
    sprintf(timeStr, "%.2f", time);
    json += "\"time\":" + std::string(timeStr);

    json += "}";

    return json;
}






//string 转字符串
char* copyStringToC(const std::string& str)
{
    char* cstr = new char[str.length() + 1];
    char* dest = cstr;
    for (char ch : str)
    {
        *dest++ = ch;
    }
    *dest = '\0';
    return cstr;
}





const char* Culculate(char begin, char end)
{
    std::vector<char> PATH;

    PATH=dijkstraDistance(begin,end);
    std::string json = outputJson(PATH, 2.0f);//第二个参数是速度，单位米每秒
    return copyStringToC(json);
}
void FreeJsonString(char* json)
{
    if (json != nullptr) {
        delete[] json; 
    }
}