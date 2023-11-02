#pragma once
#include "Pipe.h"
#include "Station.h"
#include "Log.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>


#define INPUTLINE(in, str) getline(in >> ws, str); \
                           cerr << str << endl;


extern redirect_stream_wrapper<std::istream> cin_in;


void InputLine(std::istream&, std::string&);

std::unordered_set<int> SelectIDs(const std::unordered_set<int>&, int);

template <typename T>
T GetCorrectNumber(std::istream& in, T min, T max,
    const std::string welcome_message, const std::string error_message="") {
    bool correct_answer = false;
    T value = 0;
    while (!correct_answer) {

        std::cout << welcome_message;

        if (cin_in.redirected) {
            int offset = 0;
            while (in.peek() != '\n' && in.peek() != EOF) {
                in.seekg(1, std::ios::cur);
                offset++;
            }
            in.seekg(2, std::ios::cur);
            if (in.peek() == EOF) {
                cin_in.redirect_back();
                std::cout << std::string(welcome_message.size(), '\b');
                continue;
            }
            in.seekg(-offset - 2, std::ios::cur);
        }
        
        in >> std::ws;
        in >> value;


        if (cin_in.redirected) {
            std::cout << value << std::endl;
        }

        if (std::cin.fail() || !(std::cin.peek() == ' ' || std::cin.peek() == '\n')) {
            std::cout << "**Invalid input, please repeat\n";
        }
        else if (!(min <= value && value <= max)) { 
            if (error_message == "") {
                std::cout << "**The number must be in range " << min << ".." << max << ", please repeat\n";
            }
            else {
                std::cout << error_message;
            }
        }
        else { 
            correct_answer = true;
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cerr << value << std::endl;
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
