#include "Utilities.h"

void InputLine(std::istream& in, std::string& str) {
    if (in.peek() == '\n' || in.peek() == EOF) {
        cin_in.redirect_back();
    }
    std::getline(in >> std::ws, str);
    if (cin_in.redirected) {
        std::cout << str << std::endl;
    }
    std::cerr << str << std::endl;
}