#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <Windows.h>


bool check_relation(const std::vector<std::pair<std::string, std::string>>& net, const std::string& first, const std::string& second) {

    // граф (список смежности)
    std::map<std::string, std::set<std::string>> graph;
    for (const auto& edge : net) {
        graph[edge.first].insert(edge.second);
        graph[edge.second].insert(edge.first);
    }

    // если кого-то из пользователей нет в графе
    if (graph.find(first) == graph.end() || graph.find(second) == graph.end()) {
        return first == second;
    }

    // обход графа в ширину
    std::queue<std::string> q;
    std::set<std::string> visited;

    q.push(first);
    visited.insert(first);

    while (!q.empty()) {
        std::string current_user = q.front();
        q.pop();

        if (current_user == second) {
            return true;
        }

        for (const std::string& friend_name : graph[current_user]) {
            if (visited.find(friend_name) == visited.end()) {
                visited.insert(friend_name);
                q.push(friend_name);
            }
        }
    }

    return false;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::vector<std::pair<std::string, std::string>> net = {
      {"Ваня", "Лёша"}, {"Лёша", "Катя"},
      {"Ваня", "Катя"}, {"Вова", "Катя"},
      {"Лёша", "Лена"}, {"Оля", "Петя"},
      {"Стёпа", "Оля"}, {"Оля", "Настя"},
      {"Настя", "Дима"}, {"Дима", "Маша"}
    };


    std::cout << std::boolalpha;
    std::cout << "Петя и Стёпа знакомы? " << check_relation(net, "Петя", "Стёпа") << "\n";
    std::cout << "Ваня и Дима знакомы? " << check_relation(net, "Ваня", "Дима") << "\n";
    std::cout << "Вова и Лена знакомы? " << check_relation(net, "Вова", "Лена") << "\n";
    return 0;
}
