#include <iostream>

#include "CGAOptimizer.h"

using namespace std;

int main() {
    CMax3SatProblem problem;

    problem.load("D:\\C++_test\\max3sat\\350\\m3s_350_15.txt");

    cout << problem.getVec_clauses().size();
    for (int i = 0; i < problem.getVec_clauses().size(); i++)
    {
        problem.getVec_clauses()[i]->displayClause();
    }
    

    
    CGAOptimizer optimizer;

    if (optimizer.initialize("D:\\C++_test\\max3sat\\350\\m3s_350_15.txt")) {
        
        for (int i = 0; i < 20; i++) {
            optimizer.runIteration();
            optimizer.showTheBest();
        }
    }
    return 0;
}

