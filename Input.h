#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <cctype>

class Input {
public:    
    static std::string toLower(std::string str) {
        std::setlocale(LC_ALL, "");
        for (char& c : str) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return str;
    }

    static std::string readString(std::string prompt) {
        std::string name;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin >> std::ws, name);            

            bool hasDigits = false;
            for (char c : name) {
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    hasDigits = true;
                    break;
                }
            }

            if (hasDigits) {
                std::cout << "\033[31mОшибка:\033[0m в параметре '" << prompt.substr(0, prompt.length() - 2) << "' не должно быть цифр!" << std::endl;
            }
            else {               
                return toLower(name);
            }
        }
    }    
};
