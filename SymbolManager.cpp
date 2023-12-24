#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unordered_map>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "Symbol.cpp"
#include "OtherSymbol.cpp"
#include "BadInputException.cpp"

using namespace std;

class SymbolManager {
private:
    Symbol*** symbols;
    int numRows;
    int numColumns;
    int count;
public:
    SymbolManager() {
        count = 0;
        numRows = 5;
        numColumns = 6;
        symbols = new Symbol * *[numRows];
        for (int count = 0; count < numRows; count++) {
            symbols[count] = new Symbol * [numColumns];
        }
        generate();
    }
    ~SymbolManager() {
        for (int i = 0; i < numRows; ++i) {
            delete[] symbols[i];
        }
        delete[] symbols;
    }
    int getRows() const {
        return numRows;
    }
    int getColumns() const {
        return numColumns;
    }
    int getCount()const {
        return count;
    }
    void setCount(int count) {
        if(count < 0) {
            throw BadInputException();
        }
        this->count = count;
    }
    char symbol(int row, int column) {
        return symbols[row - 1][column - 1]->getSymbol();
    }
    void match(int row, int column, bool match) {
        symbols[row - 1][column - 1]->setMatch(match);
    }
    bool getMatching(int row, int column) {
        return symbols[row - 1][column - 1]->getMatch();
    }
    void generate() {
        srand(time(0));
        unordered_map<int, int> repeatedNumber;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                int randnum = rand() % 5 + 1;
                if (repeatedNumber[randnum] < 6) {
                    repeatedNumber[randnum]++;
                    if (randnum == 1) {
                        symbols[i][j] = new OtherSymbol('&');
                    }
                    if (randnum == 2) {
                        symbols[i][j] = new OtherSymbol('%');
                    }
                    if (randnum == 3) {
                        symbols[i][j] = new OtherSymbol('$');
                    }
                    if (randnum == 4) {
                        symbols[i][j] = new OtherSymbol('#');
                    }
                    if (randnum == 5) {
                        symbols[i][j] = new OtherSymbol('@');
                    }
                }
                else {
                    j--;
                }
            }
        }
    }
    void viewAll() {
        for (int i = 0;i < 5;i++) {
            cout << i + 1 << "  ";
            for (int j = 0;j < 6;j++) {
                cout << *symbols[i][j] << "  ";
            }
            cout << endl;
        }
    }
    void rules() {
        cout << "Rules" << endl;
        cout << "";
    }
   

};