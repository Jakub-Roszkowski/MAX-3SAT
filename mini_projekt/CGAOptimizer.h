#pragma once

#include <vector>
#include "CGAIndividual.h"
#include "CMax3SatProblem.h"
#include "Random.h"

#define  DEFAULT_POPULATION_SIZE 10
#define  DEFAULT_CROSSOVER_PROBABILITY 70
#define  DEFAULT_MUTATION_PROBABILITY 1
#define  DEFAULT_TOURNAMENT_SIZE 2

using namespace std;

class CGAOptimizer {
public:

    CGAOptimizer();

    CGAOptimizer(int population_size, int crossover_probability, int mutation_probability);

    ~CGAOptimizer();

    bool initialize(string path);

    void runIteration();

    CGAIndividual* tournament(vector<CGAIndividual*> somePopulation);

    void showTheBest();
    CGAIndividual* getBestFound() { return bestFound; };
    void findBestSolution();
    CMax3SatProblem getProblem() { return problem; };
private:
    int population_size;
    int crossover_probability;
    int mutation_probability;

    vector<CGAIndividual*> vec_population;

    CMax3SatProblem problem;
    CGAIndividual* bestFound;
};
