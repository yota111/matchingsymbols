#pragma once
#include<iostream>
#include "InputValid.cpp"

using namespace std;

class User {
	string username;
	string password;
	string nametag;
	int id;
	int count;
	int bestTry;
public:
	User() : username("Unknown"), password("Unknown"), nametag("Unknown"), id(0), count(0), bestTry(0) {}
	User(string username, string password, string nametag, int id) : username(username), password(password), nametag(nametag), id(id), count(0), bestTry(0) {}
	string getUsername() const {
		return this->username;
	}
	void setUsername(string username) {
		this->username = username;
	}
	string getPassword() {
		return this->password;
	}
	void setPassword(string password) {
		this->password = password;
	}
	string getNameTag() const {
		return this->nametag;
	}
	void setNameTag(string nametag) {
		this->nametag = nametag;
	}
	int getId() {
		return this->id;
	}
	void setId(int id) {
		this->id = id;
	}
	int getCount() {
		return this->count;
	}
	void setCount(int count) {
		this->count = count;
	}
	int getBestCount() {
		return this->bestTry;
	}
	void setBestTry(int count) {
		if (bestTry == 0) {
			this->bestTry = count;
		}
		else if (count <= bestTry) {
			this->bestTry = count;
		}
		else {
			this->bestTry = bestTry;
		}
	}
	void display() {
		cout << "Username: " << username << " Password: " << password << " ID: " << id;
	}
	void display2() {
		cout << "Name: " << nametag << "		" << "Recent record: " << count << " Tries"
			<< "		Best record: " << bestTry << " Tries" << endl;
	}
	User getUser() {
		InputValid valid;
		string username;
		string password;
		string nametag;
		int id;
		username = valid.inputUsername();
		password = valid.inputPassword();
		id = valid.inputId();
		nametag = valid.inputNametag();
		User user(username, password, nametag, id);
		return user;
	}
};