#pragma once
#include <iostream>
#include <exception>

using namespace std;

class BadInputException : public exception {
public:
    virtual const char* what() const throw() {
        return "Bad input";
    }
};