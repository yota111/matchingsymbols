#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "User.cpp"
#include "InputValid.cpp"

using namespace std;

class UserManager {
public:
	void userRegister(ifstream& fin, ofstream& fout, User& user, User& user2) {
		InputValid valid;
		string username;
		string password;
		string nametag;
		int id;
		bool flag = false;
		do {
			username = valid.inputUsername();
			user.setUsername(username);
			password = valid.inputPassword();
			user.setPassword(password);
			id = valid.inputId();
			user.setId(id);
			nametag = valid.inputNametag();
			user.setNameTag(nametag);
			
			fin.open("users.dat", ios::in | ios::binary);
			while (fin.read(reinterpret_cast<char*>(&user2), sizeof(user2))) {
				if (user2.getUsername() == username || user2.getId() == id) {
					flag = true;
				}
				else {
					flag = false;
				}
			}
			fin.close();
		} while (flag);
		fout.open("users.dat", ios::out | ios::binary | ios::app);
		fout.write(reinterpret_cast<char*>(&user), sizeof(user));
		fout.close();
		cout << "User created" << endl;
	}

	bool userLogin(ifstream& fin, User& user, string& name) {
		InputValid valid;
		string username;
		string password;
		username = valid.inputUsername();
		password = valid.inputPassword();
		fin.open("users.dat", ios::in | ios::binary);
		if (!fin.is_open()) {
			cout << "Cannot open file";
			return false;
		}
		while ((fin.read(reinterpret_cast<char*>(&user), sizeof(user)))) {
			if (user.getUsername() == username && user.getPassword() == password) {
				name = username;
				fin.close();
				return true;
			}
		}
		fin.close();
		return false;

	}

	bool updateUser(fstream& fio, User& user, string name) {
		InputValid valid;
		fio.open("users.dat", ios::in | ios::out | ios::binary);
		while (!fio.eof()) {
			fio.read(reinterpret_cast<char*>(&user), sizeof(user));
			if (user.getUsername() == name) {
				user.display();
				cout << endl << endl;
				cout << "Enter the new user" << endl << endl;
				user.setUsername(valid.inputUsername());
				user.setPassword(valid.inputPassword());
				user.setNameTag(valid.inputNametag());
				int pos = (-1) * static_cast<int>(sizeof(user));
				fio.seekp(pos, ios::cur);
				fio.write(reinterpret_cast<char*> (&user), sizeof(user));
				cout << "User updated" << endl;
				fio.close();
				return true;
			}
		}
		fio.close();
		return false;

	}

	bool updateUserTries(fstream& fio, User& user, string& name, int& tries) {
		fio.open("users.dat", ios::in | ios::out | ios::binary);
		while (!fio.eof()) {
			fio.read(reinterpret_cast<char*>(&user), sizeof(user));
			if (user.getUsername() == name) {
				user.setCount(tries);
				user.setBestTry(tries);
				int pos = (-1) * static_cast<int>(sizeof(user));
				fio.seekp(pos, ios::cur);
				fio.write(reinterpret_cast<char*> (&user), sizeof(user));
				cout << "User updated" << endl;
				fio.close();
				return true;
			}
		}
		fio.close();
		return false;

	}

	void deleteUser(ifstream& fin, ofstream& fout, User& user, string name) {
		fin.open("users.dat", ios::in | ios::binary);
		if (!fin.is_open()) {
			cout << "Cannot open file" << endl;
		}
		fin.seekg(0, ios::beg);

		fout.open("temp.dat", ios::out | ios::binary);
		if (!fout.is_open()) {
			cout << "Cannot open file" << endl;
		}
		while (fin.read(reinterpret_cast<char*>(&user), sizeof(user))) {
			if (user.getUsername() != name) {
				fout.write(reinterpret_cast<char*>(&user), sizeof(user));
			}
		}
		fout.close();
		fin.close();
		remove("users.dat");
		rename("temp.dat", "users.dat");

		cout << "User has been deleted" << endl;
	}

	vector<User> getAllUser(ifstream& fin, User& user) {
		vector<User> users;
		fin.open("users.dat", ios::in | ios::binary);
		while (fin.read(reinterpret_cast<char*>(&user), sizeof(user))) {
			users.push_back(user);
		}
		fin.close();
		return users;
	}
};