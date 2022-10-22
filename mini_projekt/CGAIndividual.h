#pragma once

#include <vector>
#include "CMax3SatProblem.h"


using namespace std;

class CGAIndividual {
public:
    CGAIndividual();

    CGAIndividual(bool* newGen, int size);

    CGAIndividual(const CGAIndividual& other);

    ~CGAIndividual();

    bool* getGenotype() { return genotype; };

    bool** crossover(CGAIndividual& other);

    void mutation(int probability);

    double getFitness(CMax3SatProblem& problem);

private:
    bool* genotype;
    int problem_size;

};
