#include "Utilities.h"
#include <sstream>
#include <algorithm>

using namespace std;


void InputLine(istream& in, string& str) {
    if (in.peek() == '\n' || in.peek() == EOF) {
        cin_in.redirect_back();
    }
    getline(in >> ws, str);
    if (cin_in.redirected) {
        cout << str << endl;
    }
    cerr << str << endl;
}

std::unordered_set<int> SelectIDs(istream& in, const std::unordered_set<int>& all_IDs) {
    if (in.peek() == '\n' || in.peek() == EOF) {
        cin_in.redirect_back();
    }
    std::unordered_set<int> IDs;
    std::string str = " ";
    string line = " ";
    while (line.back() != '#') {
        getline(cin, line);
        str += " " + line;
    }
    std::stringstream s{ str };
    std::string buf;
    while (!s.eof()) {
        s >> buf;
        if (std::all_of(buf.begin(), buf.end(), ::isdigit) 
            && all_IDs.contains(stoi(buf))) {
            IDs.insert(stoi(buf));
        }
        else {
            s.clear();
            s.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        }
    }
    if (cin_in.redirected) {
        cout << str << endl;
    }
    cerr << str << endl;
    return IDs;
}