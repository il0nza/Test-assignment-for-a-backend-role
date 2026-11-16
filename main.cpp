#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <Windows.h>
#include "Input.h"


bool check_relation(const std::vector<std::pair<std::string, std::string>>& net, std::string& first, std::string& second) {
    first = Input::toLower(first);
    second = Input::toLower(second);

    // граф (список смежности)
    std::map<std::string, std::set<std::string>> graph;
    for (const auto& edge : net) {
        std::string u1 = Input::toLower(edge.first);
        std::string u2 = Input::toLower(edge.second);

        graph[u1].insert(u2);
        graph[u2].insert(u1);
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
    setlocale(LC_ALL, "Russian");

    std::vector<std::pair<std::string, std::string>> net = {
      {"Ваня", "Лёша"}, {"Лёша", "Катя"},
      {"Ваня", "Катя"}, {"Вова", "Катя"},
      {"Лёша", "Лена"}, {"Оля", "Петя"},
      {"Стёпа", "Оля"}, {"Оля", "Настя"},
      {"Настя", "Дима"}, {"Дима", "Маша"}
    };
        
    std::cout << "Доступные имена: Ваня, Лёша, Катя, Вова, Лена, Оля, Петя, Стёпа, Настя, Дима, Маша" << std::endl;
    
    std::string name1 = Input::readString("Первое имя: ");
    std::string name2 = Input::readString("Второе имя: ");

    if (check_relation(net, name1, name2)) {
        std::cout << "Связь есть!\n";
    }
    else {
        std::cout << "Связи нет.\n";
    }

    return 0;   
}
