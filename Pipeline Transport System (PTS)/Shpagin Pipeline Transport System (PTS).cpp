#include "PTS.h"
#include "Menu.h"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>

using namespace std;
using namespace chrono;


int main() {
    filesystem::create_directory(".logs\\"); // create dir for logs
	redirect_output_wrapper cerr_out(cerr);
    zoned_time now{ current_zone(), system_clock::now() }; // GMT+3 "Europe/Moscow"
	string time = format("{:%d_%m_%Y %H_%M_%OS}", now);
	ofstream logfile(".logs\\" + time + ".log");
	if (logfile) {
		cerr_out.redirect(logfile);
	}

    PTS pts;
 
    filesystem::create_directory(".saves\\"); // create dir for saves
    pts.set_save_path(".saves\\");

    const int main_menu_size = 9;
    const std::string main_menu[main_menu_size] = {
    "1. Add Pipe",
    "2. Add Station",
    "3. View Objects",
    "4. Edit Pipes",
    "5. Edit Stations",
    "6. Save",
    "7. Load",
    "0. Exit"
    };

    while (true) {
        Print(main_menu, main_menu_size);
        int menu = GetCorrectNumber(cin, 0, 8, ">> ", "**The number must be in the range 0..8, please repeat\n");
        system("cls");
        switch (menu) {
        case 1:
        {
            cout << "-> Add Pipe" << endl;
            pts.add(PTS::PIPE);
            BackToMenu();
            break;
        }
        case 2:
        {
            cout << "-> Add Station" << endl;
            pts.add(PTS::STATION);
            BackToMenu();
            break;
        }
        case 3:
        {
            ViewMenu(pts);
            break;
        }
        case 4:
        {
            EditMenu(pts, PTS::PIPE);
            break;
        }
        case 5:
        {
            EditMenu(pts, PTS::STATION);
            break;
        }
        case 6:
        {
            cout << "-> Save" << endl;
            if (CheckBeforeSave(pts)) {
                pts.save_to_file();
            }
            BackToMenu();
            break;
        }
        case 7:
        {
            cout << "-> Load" << endl;
            if (CheckBeforeLoad(pts)) {
                pts.load_from_file();
            }
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
