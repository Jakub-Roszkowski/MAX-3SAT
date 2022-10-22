#pragma once
#include <string>
#include <vector>
#include "Clause.h"

using namespace std;

class CMax3SatProblem
{
public:

	CMax3SatProblem();
	~CMax3SatProblem();

	bool load(string path);
	double compute(bool* solution);

	int get_sizeProblem() { return sizeProblem; };
	vector<Clause*> getVec_clauses() { return vec_clauses; };


private:
	vector<Clause*> vec_clauses;
	int sizeProblem;

};
