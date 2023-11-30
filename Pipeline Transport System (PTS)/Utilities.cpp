#include "Utilities.h"
#include <string>

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
