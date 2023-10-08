#pragma once
#include <iostream>
#include <string>


template <typename T>
T GetCorrectNumValue(const std::string message, T min, T max, const std::string error_message) {
    bool correct_answer = true;
    T x;
    do {
        correct_answer = true;
        std::cout << message;
        std::cin >> x;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (x <= min || x > max) {
            std::cout << error_message;
            correct_answer = false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!correct_answer);

    return x;
}

template <typename T>
T GetCorrectYesNoValue(const std::string message) {
    bool correct_answer = true;
    std::string x;
    do {
        correct_answer = true;
        std::cout << message;
        std::getline(std::cin, x);
        if (!(x == "y" || x == "n" || x == "Y" || x == "N")) {
            std::cout << "**The enter must be Y or N, please repeat\n";
            correct_answer = false;
        }
        _flushall();
    } while (!correct_answer);

    return (x == "y" || x == "Y" ? true : false);
}
