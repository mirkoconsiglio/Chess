#ifndef ASCII_CHESS_CPP_GENERAL_H
#define ASCII_CHESS_CPP_GENERAL_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void clearScreen();

[[maybe_unused]] string str(char c);

string to_upper(const string &str);

[[maybe_unused]] string to_lower(const string &str);

#endif //ASCII_CHESS_CPP_GENERAL_H
