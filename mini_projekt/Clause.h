#pragma once
#include <iostream>

using namespace std;

class Clause {
public:
    Clause();

    Clause(int first, int second, int third, int fourth,int fifth,int sixth);

    ~Clause();

    int getFirst() { return first; };

    int getSecond() { return second; };

    int getThird() { return third; };

    int getFourth() { return fourth; };

    int getFifth() { return fifth; };

    int getSixth() { return sixth; };

    void displayClause() {
        cout << first << " " << second << " " << third << " " << fourth << " " << fifth << " " << sixth<<endl;
    }
    

private:
    int first;
    int second;
    int third;
    int fourth;
    int fifth;
    int sixth;
};