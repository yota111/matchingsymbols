#pragma once
#include <iostream>
#include "SymbolManager.cpp"
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "User.cpp"
#include "UserManager.cpp"
#include "InputValid.cpp"
#include "PlayerNotFoundException.cpp"
#include "BadInputException.cpp"
#include <exception>

using namespace std;

class Application {
public:
	void run() {
		int choice;
		int id = 0;
		string name;
		ifstream fin;
		ofstream fout;
		fstream fio;
		UserManager um;
		vector<User> users;
		User user;
		User user2;
		User currentUser;
		InputValid valid;
			do {
				cout << "Login Menu" << endl;
				cout << "1. Login" << endl;
				cout << "2. Register" << endl;
				cout << "0. Exit" << endl;
				choice = valid.inputChoice();
				switch (choice) {
				case 1: {
					bool flag = false;
					do {

						flag = um.userLogin(fin, user, name);
						if (flag) {
							runLogin(valid, currentUser, id, users, fio, fin, fout, um, user, name);
						}
						else {
							cout << "Invalid" << endl;
							flag = false;
						}
					} while (flag == false);
					break;
				}
				case 2:
					um.userRegister(fin, fout, user, user2);
					break;
				case 0:
					exit(0);
				}
			} while (choice != 0);
	}
	void runLogin(InputValid& valid, User& currentUser, int& id, vector<User>& users, fstream& fio, ifstream& fin, ofstream& fout, UserManager& um, User& user, string& name) {
		int choice;
		int tries = 0;
		bool flag = false;
		bool deleted = false;
		SymbolManager sm;

		users = um.getAllUser(fin, user);

		for (auto it = users.begin();it != users.end();it++) {
			if ((*it).getUsername() == name) {
				currentUser = *it;
			}
		}

		do {

			cout << "======Menu======" << endl;
			cout << "1. Matching Symbols" << endl;
			cout << "2. Edit account" << endl;
			cout << "0. Back" << endl;
			choice = valid.inputChoice();
			switch (choice) {
			case 1:
				if (flag) {
					matchingSymbols2(valid, users, flag, sm, fio, fin, fout, um, user, name, id, tries);
				}
				else {
					matchingSymbols(valid, users, flag, sm, fio, fin, fout, um, user, name, id, tries);
				}
				break;
			case 2:
				editAccount(valid, fio, fin, fout, um, user, name);
				return;
			}
		} while (choice != 0);
		return;
	}
	void matchingSymbols(InputValid& valid, vector<User>& users, bool& flag, SymbolManager& sm, fstream& fio, ifstream& fin, ofstream& fout, UserManager& um, User& user, string& name, int& id, int& count) {
		int choice;
		bool gameClear = false;
		do {
			cout << "======Matching Symbols======" << endl;
			cout << "1. Play" << endl;
			cout << "2. Rules" << endl;
			cout << "3. Leaderboard" << endl;
			cout << "4. Find player" << endl;
			cout << "5. Save" << endl;
			cout << "0. Back" << endl;
			choice = valid.inputChoice();
			switch (choice) {
			case 1:
				play(valid, sm, count, gameClear);
				flag = true;
				return;
			case 2:
				sm.rules();
				break;
			case 3:
				leaderboard(users);
				break;
			case 4:
				try {
					findPlayer(users);
				}
				catch (exception& e) {
					cerr << e.what() << endl;
				}
				break;
			case 5: {
				if (gameClear) {
					um.updateUserTries(fio, user, name, count);
				}
				else {
					cout << "You have not won yet." << endl;
				}
				break;
			}
			}
		} while (choice != 0);
		return;
	}
	void matchingSymbols2(InputValid& valid, vector<User>& users, bool& flag, SymbolManager& sm, fstream& fio, ifstream& fin, ofstream& fout, UserManager& um, User& user, string& name, int& id, int& count) {
		int choice;
		bool gameClear = false;
		do {
			cout << "======Matching Symbols======" << endl;
			cout << "1. Continue" << endl;
			cout << "2. New game" << endl;
			cout << "3. Rules" << endl;
			cout << "4. Leaderboard" << endl;
			cout << "5. Find player" << endl;
			cout << "6. Save" << endl;
			cout << "0. Back" << endl;
			choice = valid.inputChoice();
			switch (choice) {
			case 1:
				play2(valid, sm, count, gameClear);
				break;
			case 2:
				play(valid, sm, count, gameClear);
				break;
			case 3:
				sm.rules();
				break;
			case 4:
				leaderboard(users);
				break;
			case 5:
				try {
					findPlayer(users);
				}
				catch (exception& e) {
					cerr << e.what() << endl;
				}
				break;
			case 6: {
				if (gameClear) {
					um.updateUserTries(fio, user, name, count);
				}
				else {
					cout << "You have not won yet." << endl;
				}
				break;
			}
			}
		} while (choice != 0);
		flag = true;
		return;
	}
	void play(InputValid& valid, SymbolManager& sm, int& count, bool& gameClear) {
		count = 0;
		sm.generate();
		char asterisks[5][6]{};
		int row1, row2, col1, col2;
		bool match = false;
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 6;j++) {
				asterisks[i][j] = '*';
			}
		}
		while (true) {
			gameDisplay(asterisks, count);
			cout << endl;
			do {
				row1 = valid.inputRow();
				col1 = valid.inputColumn();
				if (sm.getMatching(row1, col1)) {
					cout << "Invalid" << endl;
				}
			} while (sm.getMatching(row1, col1));
			asterisks[row1 - 1][col1 - 1] = sm.symbol(row1, col1);
			gameDisplay(asterisks, count);
			do {
				row2 = valid.inputRow();
				col2 = valid.inputColumn();
				if (sm.getMatching(row2, col2)) {
					cout << "Invalid" << endl;
				}
			} while (sm.getMatching(row2, col2));
			asterisks[row2 - 1][col2 - 1] = sm.symbol(row2, col2);
			gameDisplay(asterisks, count);
			if (sm.symbol(row1, col1) == sm.symbol(row2, col2)) {
				sm.match(row1, col1, true);
				sm.match(row2, col2, true);
				asterisks[row1 - 1][col1 - 1] = ' ';
				asterisks[row2 - 1][col2 - 1] = ' ';
				match = true;
			}
			else {
				asterisks[row1 - 1][col1 - 1] = '*';
				asterisks[row2 - 1][col2 - 1] = '*';
				match = false;
			}
			count++;
			if (match) {
				cout << "Matched!" << endl;
			}
			else {
				cout << "No match" << endl;
			}
			Sleep(2000);
			gameClear = gameClearCheck(asterisks);
			if (gameClear) {
				cout << "You WON!" << endl;
				cout << "Number of tries: " << count << endl;
				break;
			}
			gameDisplay(asterisks, count);
			cout << "Press esc to go back or any key to continue" << endl;
			if (_getch() == 27) {
				break;
			}
		}
		return;
	}
	void play2(InputValid& valid, SymbolManager& sm, int& count, bool& gameClear) {
		char asterisks[5][6]{};
		int row1, row2, col1, col2;
		bool match = false;
		bool smMatch = false;
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 6;j++) {
				smMatch = sm.getMatching(i + 1, j + 1);
				if (smMatch) {
					asterisks[i][j] = ' ';
				}
				else {
					asterisks[i][j] = '*';
				}
			}
		}
		while (true) {
			gameDisplay(asterisks, count);
			cout << endl;
			do {
				row1 = valid.inputRow();
				col1 = valid.inputColumn();
				if (sm.getMatching(row1, col1)) {
					cout << "Invalid" << endl;
				}
			} while (sm.getMatching(row1, col1));
			asterisks[row1 - 1][col1 - 1] = sm.symbol(row1, col1);
			gameDisplay(asterisks, count);
			do {
				row2 = valid.inputRow();
				col2 = valid.inputColumn();
				if (sm.getMatching(row2, col2)) {
					cout << "Invalid" << endl;
				}
			} while (sm.getMatching(row2, col2));
			asterisks[row2 - 1][col2 - 1] = sm.symbol(row2, col2);
			gameDisplay(asterisks, count);
			if (sm.symbol(row1, col1) == sm.symbol(row2, col2)) {
				sm.match(row1, col1, true);
				sm.match(row2, col2, true);
				asterisks[row1 - 1][col1 - 1] = ' ';
				asterisks[row2 - 1][col2 - 1] = ' ';
				match = true;
			}
			else {
				asterisks[row1 - 1][col1 - 1] = '*';
				asterisks[row2 - 1][col2 - 1] = '*';
				match = false;
			}
			count++;
			if (match) {
				cout << "Matched!" << endl;
			}
			else {
				cout << "No match" << endl;
			}
			Sleep(2000);
			gameClear = gameClearCheck(asterisks);
			if (gameClear) {
				cout << "You WON!" << endl;
				cout << "Number of tries: " << count << endl;
				break;
			}
			gameDisplay(asterisks, count);
			cout << "Press esc to go back or any key to continue" << endl;
			if (_getch() == 27) {
				break;
			}
		}
		return;
	}
	void gameDisplay(char arr[][6], int& count) {
		system("cls");
		cout << "   " << "1  " << "2  " << "3  " << "4  " << "5  " << "6  " << endl;
		for (int i = 0;i < 5;i++) {
			cout << i + 1 << "  ";
			for (int j = 0;j < 6;j++) {
				if (i == 2 && j == 5) {
					cout << arr[i][j] << "  ";
					cout << "\t\tTries: " << count;
				}
				else {
					cout << arr[i][j] << "  ";
				}
			}
			cout << endl;
		}
	}
	void editAccount(InputValid& valid, fstream& fio, ifstream& fin, ofstream& fout, UserManager& um, User& user, string name) {
		int choice;
		cout << "1. Update user" << endl;
		cout << "2. Delete user" << endl;
		cout << "0. Back" << endl;
		choice = valid.inputChoice();
		switch (choice) {
		case 1:
			um.updateUser(fio, user, name);
			break;
		case 2:
			um.deleteUser(fin, fout, user, name);
			break;
		}
	}

	void leaderboard(vector<User>& users) {
		for (auto it = users.begin(); it != users.end();it++) {
			(*it).display2();
		}
	}

	void findPlayer(vector<User>& users) {
		InputValid valid;
		string name;
		name = valid.inputNametag();
		auto it = find_if(users.begin(), users.end(), [&name](const User& user) {
			return user.getNameTag() == name;
			});
		if (it != users.end()) {
			it->display2();
		}
		else {
			throw PlayerNotFoundException();
		}
	}

	bool gameClearCheck(char arr[][6]) {
		for (int i = 0;i < 5;i++) {
			for (int j = 0;j < 6;j++) {
				if (arr[i][j] == '*') {
					return false;
				}
			}
		}
		return true;
	}
};