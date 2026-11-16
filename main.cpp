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

    
    std::string name1, name2;
    std::cout << "Доступные имена: Ваня, Лёша, Катя, Вова, Лена, Оля, Петя, Стёпа, Настя, Дима, Маша" << std::endl;
    std::cout << "Введите первое имя: ";
    std::cin >> name1;
    std::cout << "Введите второе имя: ";
    std::cin >> name2;

    if (check_relation(net, name1, name2)) {
        std::cout << "Да, они связаны через друзей!\n";
    }
    else {
        std::cout << "Нет, связи между ними нет.\n";
    }

    return 0;   
}
