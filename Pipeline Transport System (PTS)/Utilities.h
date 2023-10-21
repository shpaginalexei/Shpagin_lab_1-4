#pragma once
#include "Pipe.h"
#include "Station.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>


template <typename T>
T GetCorrectNumValue(const std::string message, T min, T max, const std::string error_message) {
    bool correct_answer = false;
    T x;
    while (!correct_answer) {
        std::cout << message;
        std::cin >> x;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cout << "**Invalid input, please repeat\n";
        }
        else if (x <= min || x > max) {
            std::cout << error_message;
        }
        else {
            correct_answer = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return x;
}

template <typename T>
T GetCorrectYesNoValue(const std::string message) {
    bool correct_answer = false;
    std::string x;
    while (!correct_answer) {
        std::cout << message;
        std::getline(std::cin, x);
        if (!(x == "y" || x == "n" || x == "Y" || x == "N")) {
            std::cout << "**The enter must be Y or N, please repeat\n";
        }
        else {
            correct_answer = true;
        }
        _flushall();
    }

    return (x == "y" || x == "Y" ? true : false);
}

template<typename T>
int GetCorrectID(const std::unordered_map<int, T>& map) {
    bool correct_answer = false;
    int x;
    while(!correct_answer) {
        std::cout << "Select one ID: ";
        std::cin >> x;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cout << "**Invalid input, please repeat\n";
        }
        else if (!map.contains(x)) {
            std::cout << "**No such id exists, please repeat\n";
        }
        else {
            correct_answer = true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return x;
}

template<typename T1, typename T2>
using filter = bool (*) (T1& obj, T2 par);

template<typename T1, typename T2>
std::unordered_set<int> SearchByFilter(std::unordered_map<int, T1>& map, filter<T1, T2> f, T2 par) {
    std::unordered_set<int> IDs;
    for (auto& [id, obj] : map) {
        if (f(obj, par)) {
            IDs.insert(id);
        }
    }
    return IDs;
}
