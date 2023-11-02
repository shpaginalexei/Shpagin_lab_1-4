#pragma once
#include "PTS.h"
#include <string>


void Print(const std::string[], const int);
void BackToMenu();

void ViewMenu(PTS&);
void EditMenu(PTS&, const PTS::ObjectType);
bool CheckBeforeSave(PTS&);
bool CheckBeforeLoad(PTS&);
