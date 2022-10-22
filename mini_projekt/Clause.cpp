#include "Clause.h"
#include <iostream>

using namespace std;

Clause::Clause() {
    first = 0;
    second = 0;
    third = 0;
    fourth = 0;
    fifth = 0;
    sixth = 0;
}

Clause::Clause(int first, int second, int third, int fourth, int fifth, int sixth) {
    this->first = first;
    this->second = second;
    this->third = third;
    this->fourth = fourth;
    this->fifth = fifth;
    this->sixth = sixth;
}

Clause::~Clause() {
}