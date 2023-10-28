#pragma once
#include "Pipe.h"
#include "Station.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>


template <typename T>
T GetCorrectNumber(std::istream& in, T min, T max,
    const std::string welcome_message, const std::string error_message) {
    bool correct_answer = false;
    T value;
    while (!correct_answer) {
        std::cout << welcome_message;
        in >> std::ws;
        in >> value;
        if (std::cin.fail() || std::cin.peek() != '\n') { std::cout << "**Invalid input, please repeat\n"; }
        else if (!(min <= value && value < max))        { std::cout << error_message; }
        else                                            { correct_answer = true; }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

template <typename T>
std::unordered_set<int> GetKeys(const std::unordered_map<int, T>& group) {
    std::unordered_set<int> Keys;
    for (auto& [key, value] : group) 
        Keys.insert(key); 
    return Keys;
}

template<typename T1, typename T2>
using filter = bool (*) (const T1& obj, const T2 par);

template<typename T1, typename T2>
std::unordered_set<int> search_by_filter(const std::unordered_map<int, T1>& group, filter<T1, T2> f, const T2 par) {
    std::unordered_set<int> IDs;
    for (auto& [id, obj] : group) {
        if (f(obj, par)) { IDs.insert(id); }
    }
    return IDs;
}
