#include <iostream>
#include <vector>

using namespace std;

int diameters[] = { 500, 700, 1400 };

struct Pipe {
    string name;
    double lenght;
    int diameter;
    bool in_repair;
};

struct Station {
    string name;
    int num_workshops;
    int workshops_in_operation;
    double efficiency;
};

void InputPipe(vector<Pipe>& pipes) {
    Pipe p;
    cout << "\n----- Input Pipe ------" << endl;

    cout << "name: ";
    cin >> p.name;

    bool correct_answer = true;

    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "lenght (km): ";
        cin >> p.lenght;
        if (cin.fail()) {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (p.lenght <= 0) {
            cout << "**The number must be positive, please repeat\n";
            correct_answer = false;
        }
    } while (!correct_answer);

    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "diameter (500/700/1400 mm): ";
        cin >> p.diameter;
        if (cin.fail()) {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (find(begin(diameters), end(diameters), p.diameter) == end(diameters)) {
            cout << "**The number must be 500, 700 or 1400, please repeat\n";
            correct_answer = false;
        }            
    } while (!correct_answer);

    char choice;
    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "in repair? (Y/n): ";
        cin >> choice;
        if (tolower(choice) == 'y') {
            p.in_repair = true;
        }
        else if (tolower(choice) == 'n') {
            p.in_repair = false;
        }
        else {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
    } while (!correct_answer);
    
    pipes.push_back(p);
}

void ViewPipes(const vector<Pipe>& pipes) {
    cout << "\n-------- Pipes --------" << endl;

    if (pipes.capacity() == 0) {
        cout << "*The system hasn't pipes\n";
        return;
    }

    for (int i = 0; i < pipes.capacity(); i++) {
        cout << "\n\tPipe " << i + 1 << endl
            << "name - " << pipes[i].name << endl
            << "lenght - " << pipes[i].lenght << " km" << endl
            << "diameter - " << pipes[i].diameter << " mm" << endl
            << "in repair - " << pipes[i].in_repair << endl;
    }
}

void InputStation(vector<Station>& stations) {
    Station s;
    cout << "\n---- Input Station ----" << endl;

    cout << "name: ";
    cin >> s.name;

    bool correct_answer = true;

    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "number workshops: ";
        cin >> s.num_workshops;
        if (cin.fail()) {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (s.num_workshops <= 0) {
            cout << "**The number must be positive, please repeat\n";
            correct_answer = false;
        }
    } while (!correct_answer);

    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "workshops in operation: ";
        cin >> s.workshops_in_operation;
        if (cin.fail()) {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (s.workshops_in_operation < 0) {
            cout << "**The number must be non-negative, please repeat\n";
            correct_answer = false;
        }
        else if (s.workshops_in_operation > s.num_workshops) {
            cout << "**The number must be in the range 0.." << s.num_workshops << ", please repeat\n";
            correct_answer = false;
        }
    } while (!correct_answer);

    do {
        correct_answer = true;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "efficiency: ";
        cin >> s.efficiency;
        if (cin.fail()) {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (s.efficiency < 0 || s.efficiency > 1) {
            cout << "**The number must be in the range 0..1, please repeat\n";
            correct_answer = false;
        }
    } while (!correct_answer);

    stations.push_back(s);
}

void ViewStations(const vector<Station>& stations) {
    cout << "\n------ Stations -------" << endl;

    if (stations.capacity() == 0) {
        cout << "*The system hasn't pipes\n";
        return;
    }

    for (int i = 0; i < stations.capacity(); i++) {
        cout << "\n\tStation " << i + 1 << endl
            << "name - " << stations[i].name << endl
            << "number workshops - " << stations[i].num_workshops << endl
            << "workshops in operation - " << stations[i].workshops_in_operation << endl
            << "efficiency - " << stations[i].efficiency << endl;
    }
}

int main()
{
    vector<Pipe> pipes = {};
    vector<Station> stations = {};
    InputPipe(pipes);
    InputStation(stations);
    ViewPipes(pipes);
    ViewStations(stations);
    return 0;
}
