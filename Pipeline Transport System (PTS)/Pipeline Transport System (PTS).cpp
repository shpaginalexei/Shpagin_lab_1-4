#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

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
    int efficiency;
};

template <typename T>
T GetCorrectNumValue(const string message, T min, T max, const string error_message) {
    bool correct_answer = true;
    T x;
    do {
        correct_answer = true;
        cout << message;
        cin >> x;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "**Invalid input, please repeat\n";
            correct_answer = false;
        }
        else if (x <= min || x > max) {
            cout << error_message;
            correct_answer = false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!correct_answer);

    return x;
}

bool GetCorrectYesNoValue(const string message) {
    bool correct_answer = true;
    string x;
    do {
        correct_answer = true;
        cout << message;
        cin >> x;
        if (!(x == "y" || x == "n" || x == "Y" || x == "N")) {
            cout << "**The number must be Y or N, please repeat\n";
            correct_answer = false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!correct_answer);

    return (x == "y" || x == "Y" ? true : false);
}

void InputPipe(vector<Pipe>& pipes) {
    Pipe p;
    cout << "-> Add Pipe" << endl;

    cout << "\nname: ";
    cin >> p.name;

    p.lenght = GetCorrectNumValue<double>("lenght (km): ", 0.0, INT_MAX, 
        "**The number must be positive, please repeat\n");

    p.diameter = GetCorrectNumValue<int>("diameter (mm): ", 0, INT_MAX, 
        "**The number must be positive, please repeat\n");

    p.in_repair = GetCorrectYesNoValue("in repair? (Y/n): ");
    
    pipes.push_back(p);

    cout << "\n";
}

void InputStation(vector<Station>& stations) {
    Station s;
    cout << "-> Add Station" << endl;

    cout << "\nname: ";
    cin >> s.name;

    s.num_workshops = GetCorrectNumValue<int>("number workshops: ", 0, INT_MAX,
        "**The number must be positive, please repeat\n");

    s.workshops_in_operation = GetCorrectNumValue<int>("workshops in operation: ", -1, s.num_workshops,
        "**The number must be in the range 0.." + std::to_string(s.num_workshops) + ", please repeat\n");

    s.efficiency = GetCorrectNumValue<int>("efficiency (%): ", -1, 100,
        "**The number must be in the range 0..100, please repeat\n");

    stations.push_back(s);

    cout << "\n";
}

void ViewPipes(const vector<Pipe>& pipes) {
    cout << "-> View Pipes" << endl;

    if (pipes.capacity() == 0) {
        cout << "\n*The system hasn't pipes\n";
        return;
    }

    int i = 1;
    for (auto p: pipes) {
        cout << "\n\tPipe " << i << endl
            << "name - " << p.name << endl
            << "lenght - " << p.lenght << " km" << endl
            << "diameter - " << p.diameter << " mm" << endl
            << "in repair - " << (p.in_repair ? "yes" : "no") << endl;
        i++;
    }

    cout << "\n";
}

void ViewStations(const vector<Station>& stations) {
    cout << "-> View Stations" << endl;

    if (stations.capacity() == 0) {
        cout << "\n*The system hasn't stations\n";
        return;
    }

    int i = 1;
    for (auto s: stations) {
        cout << "\n\tStation " << i << endl
            << "name - " << s.name << endl
            << "number workshops - " << s.num_workshops << endl
            << "workshops in operation - " << s.workshops_in_operation << endl
            << "efficiency - " << s.efficiency << "%" << endl;
        i++;
    }

    cout << "\n";
}

void EditPipe(vector<Pipe>& pipes) {
    cout << "-> Edit Pipe" << endl;

    if (pipes.capacity() == 0) {
        cout << "\n*The system hasn't pipes\n";
        return;
    }

    cout << '\n';
    int x = GetCorrectNumValue<int>("What Pipe do you want to edit (1-" + std::to_string(pipes.capacity()) + ")?: ", 0, pipes.capacity(),
        "**The number must be in the range 1.." + std::to_string(pipes.capacity()) + ", please repeat\n") - 1;
    Pipe& p = pipes[x];

    cout << "\n\tPipe " << x + 1 << endl
        << "..." << endl
        << "in repair - " << (p.in_repair ? "yes" : "no") << endl;
    
    bool confirm = GetCorrectYesNoValue("\nAre you sure to change this parameter (Y/n)?: ");
    if (confirm)
        p.in_repair = !p.in_repair;

    cout << "\n\tPipe " << x << endl
        << "..." << endl
        << "in repair - " << (p.in_repair ? "yes" : "no") << endl;
}

void ViewText(const string menu[], int size) {
    for (size_t i{}; i < size; i++) {
        cout << menu[i] << endl;
    }
    cout << endl;
}

void BackToMenu() {
    cout << "\nPlease, press Enter to return to menu...";
    while (_getch() != 13) {
        continue;
    }
    system("cls");
}

int main()
{
    const int logo_size = 6;
    const string logo[logo_size] = {
    "______ _____ _____ ",
    "| ___ \\_   _/  ___|",
    "| |_/ / | | \\ `--. ",
    "|  __/  | |  `--. \\",
    "| |     | | /\\__/ /",
    "\\_|     \\_/ \\____/ "
    };
    /*const int logo1_size = 6;
   const string logo1[logo1_size] = {
   " ___   _____  ___   ",
   "(  _`\\(_   _)(  _`\\ ",
   "| |_) ) | |  | (_(_)",
   "| ,__/' | |  `\\__ \\ ",
   "| |     | |  ( )_) |",
   "(_)     (_)  `\\____)",
   };
   const int logo2_size = 11;
   const string logo2[logo2_size] = {
   "                                  ___     ",
   "      ___           ___          /  /\\    ",
   "     /  /\\         /__/\\        /  /::\\   ",
   "    /  /::\\        \\  \\:\\      /__/:/\\:\\  ",
   "   /  /:/\\:\\        \\__\\:\\    _\\_ \\:\\ \\:\\ ",
   "  /  /::\\ \\:\\       /  /::\\  /__/\\ \\:\\ \\:\\",
   " /__/:/\\:\\_\\:\\     /  /:/\\:\\ \\  \\:\\ \\:\\_\\/",
   " \\__\\/  \\:\\/:/    /  /:/__\\/  \\  \\:\\_\\:\\  ",
   "      \\  \\::/    /__/:/        \\  \\:\\/:/  ",
   "       \\__\\/     \\__\\/          \\  \\::/   ",
   "                                 \\__\\/    "
   };*/

    const int main_menu_size = 8;
    const string main_menu[main_menu_size] = {
    "1. Add Pipe",
    "2. Add Station", 
    "3. View All Objects",
    "4. Edit Pipe",
    "5. Edit Station",
    "6. Save",
    "7. Load",
    "0. Exit"};

    const int obj_menu_size = 4;
    const string obj_menu[obj_menu_size] = {
    "-> View All Objects",
    "     1. View Pipe",
    "     2. View Station",
    "     0. Return"
    };
    
    vector<Pipe> pipes = {};
    vector<Station> stations = {};

    while (true) {
        ViewText(logo, logo_size);
        ViewText(main_menu, main_menu_size);
        int choice = GetCorrectNumValue<int>(">> ", -1, 7, "**The number must be in the range 0..7, please repeat\n");
        system("cls");
        ViewText(logo, logo_size);
        switch (choice) {
            case 1:
            {
                InputPipe(pipes);
                BackToMenu();
                break;
            }
            case 2:
            {
                InputStation(stations);
                BackToMenu();
                break;
            }
            case 3:
            {
                ViewText(obj_menu, obj_menu_size);
                int choice2 = GetCorrectNumValue<int>(">> ", -1, 2, "**The number must be in the range 0..2, please repeat\n");
                system("cls");
                ViewText(logo, logo_size);
                switch (choice2) {
                    case 1:
                    {
                        ViewPipes(pipes);
                        BackToMenu();
                        break;
                    }
                    case 2:
                    {
                        ViewStations(stations);
                        BackToMenu();
                        break;
                    }
                    case 0:
                    default:
                    {
                        system("cls");
                        break;
                    }
                }                
                break;
            }
            case 4:
            {
                EditPipe(pipes);
                BackToMenu();
                break;
            }
            case 5:
            {
                cout << "-> Edit Station\n" << endl;
                BackToMenu();
                break;
            }
            case 6:
            {
                cout << "-> Save\n" << endl;
                BackToMenu();
                break;
            }
            case 7:
            {
                cout << "-> Load\n" << endl;
                BackToMenu();
                break;
            }
            case 0:
            default:
            {
                system("cls");
                return 0;
            }
        }
    }
}
