#include "Utilities.h"
#include <string>
//#include <sstream>
//#include <algorithm>

using namespace std;


void InputLine(istream& in, string& str) {
    if (cin_in.redirected) {
        int offset = 0;
        while (in.peek() != '\n' && in.peek() != EOF) {
            in.seekg(1, std::ios::cur);
            offset++;
        }
        in.seekg(2, std::ios::cur);
        if (in.peek() == EOF) {
            cin_in.redirect_back();
        }
        in.seekg(-offset - 2, std::ios::cur);
    }

    INPUTLINE(in, str);

    if (cin_in.redirected) {
        cout << str << endl;
    }
}

unordered_set<int> SelectIDs(const unordered_set<int>& all_IDs, int max_id) {
    /*unordered_set<int> IDs;
    string str = " ";
    string line = " ";
    while (line.back() != '#') {
        getline(cin, line);
        str += line + "\n";
    }
    stringstream s{ str };
    int id;
    while (!s.eof()) {
        id = GetCorrectNumber(s, 0, max_id, "", "");
        if (all_IDs.contains(id)) {
            IDs.insert(id);
        }
        else {
            s.clear();
            s.ignore(numeric_limits<streamsize>::max(), ' ');
        }
    }
    cerr << str << endl;
    return IDs;*/

    unordered_set<int> IDs;
    int id;
    do {
        id = GetCorrectNumber(cin, 0, max_id, ">> ", "");
        if (all_IDs.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}