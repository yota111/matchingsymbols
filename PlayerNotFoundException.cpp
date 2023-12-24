#pragma once
#include <iostream>
#include <exception>
#include "BadInputException.cpp"

using namespace std;

class PlayerNotFoundException : public exception {
public:
    virtual const char* what() const throw() {
        return "Player not found";
    }
};