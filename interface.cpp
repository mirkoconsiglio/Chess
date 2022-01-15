#include "interface.h"

void clearScreen() {
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = {0, 0};
	
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;
	
	// Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	
	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;
	
	// Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;
	
	// Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

[[maybe_unused]] string str(char c) {
	string ret = string(1, c);
	return ret;
}

string to_upper(const string &str) {
	string ret;
	for (char c: str) ret.push_back(toupper(c));
	return ret;
}

[[maybe_unused]] string to_lower(const string &str) {
	string ret;
	for (char c: str) ret.push_back(tolower(c));
	return ret;
}

void menu() {
	string input;
	bool end = false;
	
	do {
		cout << "Enter game: ";
		cin >> input;
		input = to_upper(input);
		
		if (input == "EXIT" || input == "QUIT") end = true;
		else if (input == "CHESS") Chess game;
		else if (input == "SHOGI") Shogi game;
//        else if (input == "SHATRANJ") Shatranj game;
//        else if (input == "CHATURANGA") Chaturanga game;
//        else if (input == "XIANGQI") Xiangqi game;
//        else if (input == "SITTUYIN") Sittuyin game;
//        else if (input == "MAKRUK") Makruk game;
//        else if (input == "JANGGI") Janggi game;
		else cout << "Invalid choice\n";
	} while (!end);
}

