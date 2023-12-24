#pragma once
#include<iostream>
#include <sstream>
#include "BaseSymbol.cpp"
#include "BadInputException.cpp"

using namespace std;

class Symbol : public BaseSymbol {
private:
	char symbol;
	bool match;
	int id;
public:
	Symbol() {
		match = false;
		symbol = '*';
		id = 0;
	}
	Symbol(char symbol) {
		match = false;
		setSymbol(symbol);
	}
	void setMatch(bool match) {
		this->match = match;
	}
	bool getMatch() {
		return this->match;
	}
	virtual void setSymbol(char symbol) {
		this->symbol = symbol;
	}
	virtual char getSymbol() {
		return this->symbol;
	}
	void setId(int id) {
		if (id < 0) {
			throw BadInputException();
		}
		this->id = id;
	}
	int getId() const {
		return this->id;
	}
	virtual string toString() {
		stringstream ss;
		ss << symbol;
		return ss.str();
	}
	friend ostream& operator<<(ostream& out, Symbol& other) {
		out << other.toString();
		return out;
	}

};