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

// есть ли человек в списке связей?
bool userExists(const std::vector<std::pair<std::string, std::string>>& net, const std::string& target) {
    std::string lowerTarget = Input::toLower(target);
    for (const auto& edge : net) {
        if (Input::toLower(edge.first) == lowerTarget || Input::toLower(edge.second) == lowerTarget) {
            return true;
        }
    }
    return false;
}


std::string readValidName(const std::vector<std::pair<std::string, std::string>>& net, const std::string& prompt) {
    while (true) {
        std::string name = Input::readString(prompt);
        if (userExists(net, name)) {
            return name;
        }
        std::cout << "\033[31mОшибка:\033[0m такого человека нет в списке друзей! Попробуйте снова.\n";
    }
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
    
    std::string name1 = readValidName(net, "Первое имя: ");
    std::string name2 = readValidName(net, "Второе имя: ");

    if (check_relation(net, name1, name2)) {
        std::cout << "Связь есть!\n";
    }
    else {
        std::cout << "Связи нет.\n";
    }

    return 0;   
}
