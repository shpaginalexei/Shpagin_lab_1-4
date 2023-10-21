#include "App.h"
#include "Utilities.h"
#include <conio.h>

using namespace std;


void ViewText(const string menu[], const int size) {
    for (size_t i{}; i < size; i++) {
        cout << menu[i] << endl;
    }
    cout << "\n";
}

void BackToMenu() {
    cout << "\n\nPlease, press Enter to return to menu...";
    while (_getch() != 13) {
        continue;
    }
    system("cls");
}


int main() {
    const int logo_size = 6;
    const std::string logo[logo_size] = {
    "______ _____ _____ ",
    "| ___ \\_   _/  ___|",
    "| |_/ / | | \\ `--. ",
    "|  __/  | |  `--. \\",
    "| |     | | /\\__/ /",
    "\\_|     \\_/ \\____/ "
    };

    const int main_menu_size = 9;
    const std::string main_menu[main_menu_size] = {
    "1. Add Pipe",
    "2. Add Station",
    "3. View Objects",
    "4. Edit Pipes",
    "5. Edit Stations",
    "6. Search",
    "7. Save",
    "8. Load",
    "0. Exit"
    };

    const int view_menu_size = 5;
    const std::string view_menu[view_menu_size] = {
    "-> View Objects",
    "     1. View Pipes",
    "     2. View Stations",
    "     3. View All",
    "     0. Return"
    };

    const int search_menu_size = 4;
    const std::string search_menu[search_menu_size] = {
    "-> Search",
    "     1. Search Pipes",
    "     2. Search Stations",
    "     0. Return"
    };

    const int edit_pipe_menu_size = 5;
    const std::string edit_pipe_menu[edit_pipe_menu_size] = {
    "-> Edit Pipes",
    "     1. Edit one Pipe",
    "     2. Edit some Pipes",
    "     3. Remove Pipe",
    "     0. Return"
    };

    const int edit_station_menu_size = 5;
    const std::string edit_station_menu[edit_station_menu_size] = {
    "-> Edit Stations",
    "     1. Edit one Station",
    "     2. Edit some Stations",
    "     3. Remove Station",
    "     0. Return"
    };

    App app;

    while (true) {
        ViewText(logo, logo_size);
        ViewText(main_menu, main_menu_size);
        int menu_choice = GetCorrectNumValue<int>(">> ", -1, 8, "**The number must be in the range 0..8, please repeat\n");
        system("cls");
        ViewText(logo, logo_size);
        switch (menu_choice) {
        case 1:
        {
            cout << "-> Add Pipe" << endl;
            //app.add_pipe();
            app.add_to(app.pipes);
            BackToMenu();
            break;
        }
        case 2:
        {
            cout << "-> Add Station" << endl;
            //app.add_station();
            app.add_to(app.stations);
            BackToMenu();
            break;
        }
        case 3:
        {
            ViewText(view_menu, view_menu_size);
            int view_choice = GetCorrectNumValue<int>(">> ", -1, 3, "**The number must be in the range 0..3, please repeat\n");
            system("cls");
            ViewText(logo, logo_size);
            switch (view_choice) {
            case 1:
            {
                cout << "-> View Objects" << endl
                    << "     -> Pipes" << endl;
                //app.view_pipes();
                app.view(app.pipes);
                BackToMenu();
                break;
            }
            case 2:
            {
                cout << "-> View Objects" << endl
                    << "     -> Stations" << endl;
                //app.view_stations();
                app.view(app.stations);
                BackToMenu();
                break;
            }
            case 3:
            {
                cout << "-> View Objects" << endl
                    << "     -> Pipes" << endl;
                //app.view_pipes();
                app.view(app.pipes);
                cout << "\n-> View Objects" << endl
                    << "     -> Stations" << endl;
                //app.view_stations();
                app.view(app.stations);
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
            cout << "-> Edit Pipes" << endl;
            //app.edit_pipes();
            app.edit(app.pipes);
            BackToMenu();
            break;
        }
        case 5:
        {
            cout << "-> Edit Stations" << endl;
            //app.edit_stations();
            app.edit(app.stations);
            BackToMenu();
            break;
        }
        case 6:
        {
            ViewText(search_menu, search_menu_size);
            int search_choice = GetCorrectNumValue<int>(">> ", -1, 2, "**The number must be in the range 0..2, please repeat\n");
            system("cls");
            ViewText(logo, logo_size);
            switch (search_choice) {
            case 1:
            {
                cout << "-> Search" << endl
                    << "     -> Pipes" << endl;
                //app.search_pipes();
                app.search(app.pipes);
                BackToMenu();
                break;
            }
            case 2:
            {
                cout << "-> Search" << endl
                    << "     -> Stations" << endl;
                //app.search_stations();
                app.search(app.stations);
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
            cout << "-> Save" << endl;
            app.save_to_file();
            BackToMenu();
            break;
        }
        case 8:
        {
            cout << "-> Load" << endl;
            app.load_from_file();
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
