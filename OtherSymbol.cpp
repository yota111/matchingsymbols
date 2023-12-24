#pragma once
#include<iostream>
#include <sstream>
#include "Symbol.cpp"

using namespace std;

class OtherSymbol : public Symbol {
private:
	char sym;
public:
	OtherSymbol() {
		sym = '*';
	}
	OtherSymbol(char symbol) {
		setSymbol(symbol);
	}
	void setSymbol(char symbol) {
		this->sym = symbol;
	}
	char getSymbol() {
		return this->sym;
	}
	string toString() {
		stringstream ss;
		ss << sym;
		return ss.str();
	}
};