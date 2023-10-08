#pragma once
#include "Pipe.h"
#include "Station.h"
#include <string>
#include <vector>


void ViewText(const std::string[], int);

void BackToMenu();

void AddPipe(std::vector<Pipe>&);

void AddStation(std::vector<Station>&);

void ViewPipes(std::vector<Pipe>&);

void ViewStations(std::vector<Station>&);

void ViewAll(std::vector<Pipe>&, std::vector<Station>&);

void EditPipe(std::vector<Pipe>&);

void EditStation(std::vector<Station>&);

void SaveToFile(const std::string&, std::vector<Pipe>&, std::vector<Station>&);

void LoadFromFile(const std::string&, std::vector<Pipe>&, std::vector<Station>&);
