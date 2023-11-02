#include "PTS.h"
#include "Menu.h"
#include "Log.h"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>
using namespace std;
using namespace chrono;


redirect_stream_wrapper<istream> cin_in(cin);

void MainMenu(PTS& pts) {
    static const int main_menu_size = 9;
    static const std::string main_menu[main_menu_size] = {
    "1. Add Pipe",
    "2. Add Station",
    "3. View Objects",
    "4. Edit Pipes",
    "5. Edit Stations",
    "6. Save",
    "7. Load",
    "0. Exit"
    };
    Print(main_menu, main_menu_size);
    int menu = GetCorrectNumber(cin, 0, 7, ">> ", "");
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
        //exit(1);
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
        exit(0);
        //return;
    }
    }
}


int main(int argc, char* argv[]) {

    PTS pts;

    filesystem::create_directory(".saves\\");
    pts.set_save_directory(".saves\\");

    filesystem::create_directory(".logs\\");
    redirect_stream_wrapper cerr_out(cerr);
    zoned_time now{ current_zone(), system_clock::now() };
	string time = format("{:%d_%m_%Y_%H_%M_%OS}", now);
	ofstream log_out(".logs\\" + time + ".log");
	if (log_out) {
		cerr_out.redirect(log_out);
	}
    
    if (argc == 2) {
        ifstream log_in(".logs\\" + (string)argv[1]);
        if (log_in) {
            cin_in.redirect(log_in);

            while (!cin.eof()) {
                MainMenu(pts);
            }

            cin_in.~redirect_stream_wrapper();

        }
        log_in.close();
    }

    while (true) {
        MainMenu(pts);
    }    
}
