#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
//Test change

std::unordered_map<std::string, std::vector<std::string>> input(){
    std::unordered_map<std::string, std::vector<std::string>> mp;
    std::string line;


    while (std::getline(std::cin, line)) {
        if (line.empty()) break; 

        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string values_str = line.substr(pos + 1);

        // Убираем квадратные скобки
        if (!values_str.empty() && values_str.front() == '[') values_str.erase(0, 1);
        if (!values_str.empty() && values_str.back() == ']') values_str.pop_back();

        // Разделяем по запятым
        std::vector<std::string> values;
        std::stringstream ss(values_str);
        std::string value;
        while (std::getline(ss, value, ',')) {
            if (!value.empty())
                values.push_back(value);
        }

        mp[key] = values;
    }

    return mp;
}


void dfs(const std::unordered_map<std::string, std::vector<std::string>>& mp,
         const std::string& node,
         std::unordered_set<std::string>& visited,
         int depth = 0)
{
    if (visited.count(node)) return; // если уже был — выходим
    visited.insert(node);

    // Отступы
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << "Commit: " << node << "\n";

    auto it = mp.find(node);
    if (it == mp.end()) return;

    for (const auto& dep : it->second)
        dfs(mp, dep, visited, depth + 1);
}


int main() {
    std::unordered_map<std::string, std::vector<std::string>> mp = input();

    std::string line;
    std::string startNode;

    if (std::getline(std::cin, line)) {
        if (line.rfind("START", 0) == 0) {
            startNode = line.substr(6); 
            startNode.erase(std::remove_if(startNode.begin(), startNode.end(), ::isspace), startNode.end());
        }
    }

    if (startNode.empty()) {
        std::cout << "Не указан стартовый элемент (строка должна начинаться с START ...)\n";
        return 0;
    }

    std::unordered_set<std::string> visited;
    dfs(mp, startNode, visited);

    return 0;
}
