#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

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
        //cin >> x;
        getline(cin, x);
        if (!(x == "y" || x == "n" || x == "Y" || x == "N")) {
            cout << "**The number must be Y or N, please repeat\n";
            correct_answer = false;
        }
        _flushall();
        /*cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
    } while (!correct_answer);

    return (x == "y" || x == "Y" ? true : false);
}

void InputPipe(vector<Pipe>& pipes) {
    Pipe p;
    cout << "-> Add Pipe" << endl;

    //p.in_repair = GetCorrectYesNoValue("in repair? (Y/n): ");

    cout << "\nname: ";
    // cin >> p.name;
    getline(cin, p.name);

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
    // cin >> s.name;
    getline(cin, s.name);

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
    cout << "-> View Objects" << endl
        << "     -> Pipes" << endl;

    if (pipes.capacity() == 0) {
        cout << "\n*The system hasn't pipes\n\n";
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
    cout << "-> View Objects" << endl
        << "     -> Stations" << endl;

    if (stations.capacity() == 0) {
        cout << "\n*The system hasn't stations\n\n";
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
        cout << "\n*The system hasn't pipes\n\n";
        return;
    }

    cout << '\n';
    int x = -1;
    if (pipes.capacity() == 1) {
        cout << "*Only one Pipe in system\n" << endl;
        if (GetCorrectYesNoValue("Do you want to edit this Pipe (Y/n)?: "))
            x = 0;
        else {
            cout << '\n';
            return;
        }            
    }
    else
        x = GetCorrectNumValue<int>("What Pipe do you want to edit (1-" + std::to_string(pipes.capacity()) + ")?: ", 0, pipes.capacity(),
            "**The number must be in the range 1.." + std::to_string(pipes.capacity()) + ", please repeat\n") - 1;
    Pipe& p = pipes[x];

    cout << "\n\tPipe " << x + 1 << endl
        << "..." << endl
        << "in repair - " << (p.in_repair ? "yes\n" : "no\n") << endl;
    
    bool confirm = GetCorrectYesNoValue("Are you sure to change this parameter (Y/n)?: ");
    if (confirm)
        p.in_repair = !p.in_repair;

    cout << "\n\tPipe " << x + 1 << endl
        << "..." << endl
        << "in repair - " << (p.in_repair ? "yes\n" : "no\n") << endl;
}

void EditStation(vector<Station>& stations) {
    cout << "-> Edit Station" << endl;

    if (stations.capacity() == 0) {
        cout << "\n*The system hasn't stations\n\n";
        return;
    }

    cout << '\n';
    int x = -1;
    if (stations.capacity() == 1) {
        cout << "*Only one Station in system\n" << endl;
        if (GetCorrectYesNoValue("Do you want to edit this Station (Y/n)?: "))
            x = 0;
        else {
            cout << '\n';
            return;
        }
    }
    else
        x = GetCorrectNumValue<int>("What Station do you want to edit (1-" + std::to_string(stations.capacity()) + ")?: ", 0, stations.capacity(),
            "**The number must be in the range 1.." + std::to_string(stations.capacity()) + ", please repeat\n") - 1;
    Station& s = stations[x];

    cout << "\n\tStation " << x + 1 << endl
        << "..." << endl
        << "number workshops - " << s.num_workshops << endl
        << "workshops in operation - " << s.workshops_in_operation << '\n' << endl;

    bool confirm = GetCorrectYesNoValue("Are you sure to change this parameter (Y/n)?: ");
    if (confirm) {
        if (s.workshops_in_operation > 0 && s.workshops_in_operation < s.num_workshops) {
            int count = GetCorrectNumValue("Start (1) or stop (0) the workshop?: ", -1, 1,
                "**The number must be in the range 0..1, please repeat\n");
            count == 1 ? s.workshops_in_operation++ : s.workshops_in_operation--;
        }
        else if (s.workshops_in_operation == 0) {
            if (GetCorrectYesNoValue("Start one workshop (Y/n)?: "))
                s.workshops_in_operation++;
        }
        else if ((int)s.workshops_in_operation == (int)s.num_workshops) {
            if (GetCorrectYesNoValue("Stop one workshop (Y/n)?: "))
                s.workshops_in_operation--;
        }
    }
    cout << "\n\tStation " << x + 1 << endl
        << "..." << endl
        << "number workshops - " << s.num_workshops << endl
        << "workshops in operation - " << s.workshops_in_operation << '\n' << endl;
}

void SavePipes(const vector<Pipe>& pipes, const string& file_name) {
    cout << "-> Save" << endl
        << "     -> Save Pipe" << endl;

    ofstream file;
    file.open(file_name + ".txt", ios::out);
    int count = 0;
    if (file.is_open()) {
        for (Pipe obj : pipes) {
            file << obj.name << ';'
                 << obj.lenght << ';'
                 << obj.diameter << ';'
                 << obj.in_repair << '\n';
            count++;
        }
        cout << '\n' << count << " Pipes saved successfully!\n" << endl;
    }
    file.close();    
}

void SaveStations(const vector<Station>& stations, const string& file_name) {
    cout << "-> Save" << endl
        << "     -> Save Stations" << endl;

    ofstream file;
    file.open(file_name + ".txt", ios::out);
    if (file.is_open()) {
        int count = 0;
        for (Station obj : stations) {
            file << obj.name << ';'
                 << obj.num_workshops << ';'
                 << obj.workshops_in_operation << ';'
                 << obj.efficiency << '\n';
            count++;
        }
        cout << '\n' << count << " Stations saved successfully!\n" << endl;
    }
    file.close();    
}

void LoadPipes(vector<Pipe>& pipes, const string& file_name) {
    cout << "-> Load" << endl
        << "     -> Load Pipe" << endl;
    pipes.clear();

    ifstream file;
    file.open(file_name + ".txt", ios::in);
    string line;    
    if (file.is_open()) {
        int count = 0;
        while (getline(file, line)) {
            Pipe p;
            istringstream iss(line);

            string token;
            int i = 0;
            while (getline(iss, token, ';')) {
                if (i == 0) p.name = token;
                if (i == 1) p.lenght = stod(token);
                if (i == 2) p.diameter = stoi(token);
                if (i == 3) p.in_repair = stoi(token);
                i++;
            }
            pipes.push_back(p);
            count++;
        }
        cout << '\n' << count << " Pipes loaded successfully!\n" << endl;
    }   
    file.close();    
}

void LoadStations(vector<Station>& stations, const string& file_name) {
    cout << "-> Load" << endl
        << "     -> Load Stations" << endl;
    stations.clear();

    ifstream file;
    file.open(file_name + ".txt", ios::in);
    string line;
    
    if (file.is_open()) {
        int count = 0;
        while (getline(file, line)) {
            Station s;
            istringstream iss(line);

            string token;
            int i = 0;
            while (getline(iss, token, ';')) {
                if (i == 0) s.name = token;
                if (i == 1) s.num_workshops = stoi(token);
                if (i == 2) s.workshops_in_operation = stoi(token);
                if (i == 3) s.efficiency = stoi(token);
                i++;
            }
            stations.push_back(s);
            count++;
        }
        cout << '\n' << count << " Stations loaded successfully!\n" << endl;
    }
    file.close();    
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
    "3. View Objects",
    "4. Edit Pipe",
    "5. Edit Station",
    "6. Save",
    "7. Load",
    "0. Exit"};

    const int view_main_size = 5;
    const string view_main[view_main_size] = {
    "-> View Objects",
    "     1. View Pipe",
    "     2. View Station",
    "     3. View All",
    "     0. Return"
    };

    const int save_menu_size = 5;
    const string save_menu[save_menu_size] = {
    "-> Save",
    "     1. Save Pipe",
    "     2. Save Station",
    "     3. Save All",
    "     0. Return"
    };

    const int load_menu_size = 5;
    const string load_menu[load_menu_size] = {
    "-> Load",
    "     1. Load Pipe",
    "     2. Load Station",
    "     3. Load All",
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
                ViewText(view_main, view_main_size);
                int choice2 = GetCorrectNumValue<int>(">> ", -1, 3, "**The number must be in the range 0..3, please repeat\n");
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
                    case 3:
                    {
                        ViewPipes(pipes);
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
                EditStation(stations);
                BackToMenu();
                break;
            }
            case 6:
            {
                ViewText(save_menu, save_menu_size);
                int choice3 = GetCorrectNumValue<int>(">> ", -1, 3, "**The number must be in the range 0..3, please repeat\n");
                system("cls");
                ViewText(logo, logo_size);
                switch (choice3) {
                    case 1:
                    {
                        SavePipes(pipes, "pipes");
                        BackToMenu();
                        break;
                    }
                    case 2:
                    {
                        SaveStations(stations, "stations");
                        BackToMenu();
                        break;
                    }
                    case 3:
                    {
                        SavePipes(pipes, "pipes");
                        SaveStations(stations, "stations");
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
            case 7:
            {
                ViewText(load_menu, load_menu_size);
                int choice4 = GetCorrectNumValue<int>(">> ", -1, 3, "**The number must be in the range 0..3, please repeat\n");
                system("cls");
                ViewText(logo, logo_size);
                switch (choice4) {
                case 1:
                {
                    LoadPipes(pipes, "pipes");
                    BackToMenu();
                    break;
                }
                case 2:
                {
                    LoadStations(stations, "stations");
                    BackToMenu();
                    break;
                }
                case 3:
                {
                    LoadPipes(pipes, "pipes");
                    LoadStations(stations, "stations");
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
            case 0:
            default:
            {
                system("cls");
                return 0;
            }
        }
    }
}
