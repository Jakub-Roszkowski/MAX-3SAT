#include "CMax3SatProblem.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

CMax3SatProblem::CMax3SatProblem() {
    int sizeProblem = 0;
}

CMax3SatProblem::~CMax3SatProblem() {
    for (int i = 0; i < (int)vec_clauses.size(); i++) {
        delete vec_clauses.at(i);
    }
}

bool CMax3SatProblem::load(string path) {
    ifstream file;
    file.open(path);
    string line;
    string line2;

    char separator = ' ';
    vector<string> lineHelper;
    vector<string> lineHelper2;
    string val;
    string val2;

    int maxi = 0;

    if (!file) return false;

    while (getline(file, line)) {
        
        stringstream streamD(line);
        while (getline(streamD, val, separator))
            lineHelper.push_back(val);

        if (max(max(stoi(lineHelper[1]), stoi(lineHelper[3])), max(stoi(lineHelper[1]), stoi(lineHelper[5]))) > maxi) {
            maxi = max(max(stoi(lineHelper[1]), stoi(lineHelper[3])), max(stoi(lineHelper[1]), stoi(lineHelper[5])));
        };

     
        getline(file, line2);
        stringstream streamD2(line2);
        while (getline(streamD2, val2, separator))
            lineHelper2.push_back(val2);

        if (max(max(stoi(lineHelper2[1]), stoi(lineHelper2[3])), max(stoi(lineHelper2[1]), stoi(lineHelper2[5]))) > maxi) {
            maxi = max(max(stoi(lineHelper2[1]), stoi(lineHelper2[3])), max(stoi(lineHelper2[1]), stoi(lineHelper2[5])));
        }

        Clause* clause = new Clause(
            stoi(lineHelper[1]),
            stoi(lineHelper[3]),
            stoi(lineHelper[5]),
            stoi(lineHelper2[1]),
            stoi(lineHelper2[3]),
            stoi(lineHelper2[5])
        );


        vec_clauses.push_back(clause);
        lineHelper.clear();
        lineHelper2.clear();
        
    }
    sizeProblem = maxi + 1;
    lineHelper.clear();
    lineHelper2.clear();
    file.close();
    return true;
}

double CMax3SatProblem::compute(bool* solution) {
    double goodClauses = 0;

    

    for (int i = 0; i < (int)vec_clauses.size(); i++) {
        int nr1 = vec_clauses[i]->getFirst();
        int nr2 = vec_clauses[i]->getSecond();
        int nr3 = vec_clauses[i]->getThird();
        int nr4 = vec_clauses[i]->getFourth();
        int nr5 = vec_clauses[i]->getFifth();
        int nr6 = vec_clauses[i]->getSixth();
        if ((nr1 >= 0 && solution[abs(nr1)]) || (nr2 >= 0 && solution[abs(nr2)]) || (nr3 >= 0 && solution[abs(nr3)]) || (nr4 >= 0 && solution[abs(nr4)]) || (nr5 >= 0 && solution[abs(nr5)]) || (nr6 >= 0 && solution[abs(nr6)])) {
            goodClauses++;
     
        }
        else if ((nr1 < 0 && !solution[abs(nr1)]) || (nr2 < 0 && !solution[abs(nr2)]) || (nr3 < 0 && !solution[abs(nr3)]) || (nr4 < 0 && !solution[abs(nr4)]) || (nr5 < 0 && !solution[abs(nr5)]) || (nr6 < 0 && !solution[abs(nr6)])) {
            goodClauses++;
        }
    }
    return goodClauses / vec_clauses.size();
}