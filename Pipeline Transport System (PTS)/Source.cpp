#include "Menu.h"
#include "Utilities.h"

using namespace std;


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
    "0. Exit" };

    const int view_main_size = 5;
    const string view_main[view_main_size] = {
    "-> View Objects",
    "     1. View Pipe",
    "     2. View Station",
    "     3. View All",
    "     0. Return"
    };

    /*const int save_menu_size = 5;
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
    };*/

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
            AddPipe(pipes);
            BackToMenu();
            break;
        }
        case 2:
        {
            AddStation(stations);
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
                ViewAll(pipes, stations);
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
            SaveToFile("data.pts", pipes, stations);
            BackToMenu();
            break;
        }
        case 7:
        {
            LoadFromFile("data.pts", pipes, stations);
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
