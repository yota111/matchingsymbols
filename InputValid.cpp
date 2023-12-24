#pragma once
#include <iostream>

using namespace std;

class InputValid {
private:
	bool validateNum(int num) {
		if (cin.fail() || num > 101 || num <= 0) {
			return false;
		}
		return true;
	}
	bool validateChoice(int num) {
		if (cin.fail() || num > 20 || num < 0) {
			return false;
		}
		return true;
	}
	bool validateName(string name) {
		if (name.length() <= 3 || name.length() >= 20) {
			return false;
		}
		for (int i = 0;i < name.length();i++) {
			if (!(name[i] >= 65 && name[i] <= 122)) {
				return false;
			}
		}
		return true;
	}
	bool validatePassword(string password) {
		for (int i = 0;i < password.length();i++) {
			if (!(password[i] >= 48 && password[i] <= 57)) {
				return false;
			}
		}
		return true;
	}
	bool validateSymbol(char symbol) {
		if (!(symbol == 35 || symbol == 36 || symbol == 37 || symbol == 38 || symbol == 64)) {
			return false;
		}
		return true;
	}
	bool validateRow(int num) {
		if (cin.fail() || num < 0 || num > 5) {
			return false;
		}
		return true;
	}
	bool validateColumn(int num) {
		if (cin.fail() || num < 0 || num > 6) {
			return false;
		}
		return true;
	}
public:
	string inputNametag() {
		string name;
		while (true) {
			cout << "Enter nametag: ";
			cin >> name;
			if (!(validateName(name))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl;
				continue;
			}
			break;
		}
		cout << "\n";
		return name;

	}
	string inputUsername() {
		string name;
		while (true) {
			cout << "Enter username: ";
			cin >> name;
			if (!(validateName(name))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl;
				continue;
			}
			break;
		}
		cout << "\n";
		return name;
	}
	string inputPassword() {
		string password;
		while (true) {
			cout << "Enter password: ";
			cin >> password;
			if (!(validatePassword(password))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl;
				continue;
			}
			break;
		}
		cout << "\n";
		return password;
	}
	int inputId() {
		int num;
		while (true) {
			cout << "Enter id: ";
			cin >> num;
			if (!(validateNum(num))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input" << endl;
			}
			else {
				cout << "\n";
				return num;
			}
		}
	}
	int inputChoice() {
		int num;
		while (true) {
			cout << "Enter choice: ";
			cin >> num;
			if (!(validateChoice(num))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid choice";
				cout << "\n";
			}
			else {
				cout << "\n";
				return num;
			}
		}
	}
	int inputRow() {
		int num;
		while (true) {
			cout << "Enter row: ";
			cin >> num;
			if (!(validateNum(num))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid row number";
			}
			else {
				cout << "\n";
				return num;
			}
		}
	}
	int inputColumn() {
		int num;
		while (true) {
			cout << "Enter column: ";
			cin >> num;
			if (!(validateNum(num))) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid column number";
			}
			else {
				cout << "\n";
				return num;
			}
		}
	}
};