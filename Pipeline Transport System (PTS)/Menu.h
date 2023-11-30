#pragma once
#include "PTS.h"
#include <string>


void Print(const std::string[], const int);
void BackToMenu();

void ViewMenu(PTS&);
void EditMenu(PTS&, const PTS::ObjectType);

void GraphMenu(PTS&);

bool CheckBeforeSave(PTS&);
void CheckBeforeExit(PTS&);
void CheckBeforeLoad(PTS&);
