#include "CGAIndividual.h"
#include <iostream>
#include "Random.h"

CGAIndividual::CGAIndividual() {
}

CGAIndividual::CGAIndividual(bool* newGen, int size) {
    genotype = newGen;

    problem_size = size;
}


CGAIndividual::CGAIndividual(const CGAIndividual& other) {
    bool* newGenotype = new bool[other.problem_size];

    problem_size = other.problem_size;

    for (int i = 0; i < problem_size; i++)
        newGenotype[i] = other.genotype[i];

    genotype = newGenotype;
}

CGAIndividual::~CGAIndividual() {
    delete[] genotype;
}

bool** CGAIndividual::crossover(CGAIndividual& other) {

    int random;
    bool** results = new bool* [2];

    for (int i = 0; i < 2; i++)
        results[i] = new bool[problem_size];

    for (int i = 0; i < problem_size; i++) {
        random = Random::generateRandomInt(0, 2);

        if (random == 0) {
            results[0][i] = genotype[i];
            results[1][i] = other.genotype[i];
        }
        else {
            results[0][i] = other.genotype[i];
            results[1][i] = genotype[i];
        }
    }
    return results;
}

void CGAIndividual::mutation(int probability) {
    int random;

    for (int i = 0; i < problem_size; i++) {
        random = Random::generateRandomInt(0, 101);

        if (random < probability)
            genotype[i] = !genotype[i];
    }
}


double CGAIndividual::getFitness(CMax3SatProblem& problem) {
    return problem.compute(genotype);
}



