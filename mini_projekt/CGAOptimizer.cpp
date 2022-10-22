#include "CGAOptimizer.h"
#include <iostream>


CGAOptimizer::CGAOptimizer() {
    population_size = DEFAULT_POPULATION_SIZE;
    crossover_probability = DEFAULT_CROSSOVER_PROBABILITY;
    mutation_probability = DEFAULT_MUTATION_PROBABILITY;
    bestFound = nullptr;
}

CGAOptimizer::CGAOptimizer(int population_size, int crossover_probability, int mutation_probability) {
    this->population_size = population_size;
    this->crossover_probability = crossover_probability;
    this->mutation_probability = mutation_probability;
    bestFound = nullptr;
}

CGAOptimizer::~CGAOptimizer() {
    for (int i = 0; i < (int)vec_population.size(); i++)
        delete vec_population[i];
    delete bestFound;
}


bool CGAOptimizer::initialize(string path) {

    if (!problem.load(path)) return false;

    for (int i = 0; i < population_size; i++) {
        bool* gens = new bool[problem.get_sizeProblem()];

        for (int j = 0; j < problem.get_sizeProblem(); j++) {
            int random = rand() % 2;
            gens[j] = random;
        }
        vec_population.push_back(new CGAIndividual(gens, problem.get_sizeProblem()));
    }
    bestFound = new CGAIndividual(*vec_population[0]);
    return true;
}


CGAIndividual* CGAOptimizer::tournament(vector<CGAIndividual*> somePopulation) {
    bool* isInTournament = new bool[population_size];
    for (int j = 0; j < population_size; j++)
        isInTournament[j] = false;

    std::vector<CGAIndividual*> areInTournament;
    int i = 0;
    CGAIndividual* actual = nullptr;

    while (i < DEFAULT_TOURNAMENT_SIZE) {
        int index = Random::generateRandomInt(0, population_size);;

        if (!isInTournament[index]) {
            actual = somePopulation.at(index);
            isInTournament[index] = true;
            areInTournament.push_back(actual);
            i++;
        }
    }

    CGAIndividual* winner = areInTournament[0];
    double actualResult = winner->getFitness(problem);

    for (int j = 1; j < DEFAULT_TOURNAMENT_SIZE; j++) {
        double act = areInTournament.at(j)->getFitness(problem);

        if (act > actualResult) {
            actualResult = act;
            winner = areInTournament.at(j);
        }
    }

    delete[] isInTournament;
    areInTournament.clear();
    actual = NULL;

    return winner;
}


void CGAOptimizer::runIteration() {

    vector<CGAIndividual*> newPopulation;

    CGAIndividual* father = nullptr;
    CGAIndividual* mother = nullptr;
    CGAIndividual* child1 = nullptr;
    CGAIndividual* child2 = nullptr;

    while (newPopulation.size() < vec_population.size()) {

        father = tournament(vec_population);
        mother = tournament(vec_population);

        while (mother == father)
            mother = tournament(vec_population);

        int probability = Random::generateRandomInt(0, 101);

        if (probability < crossover_probability) {
            bool** children = father->crossover(*mother);
            child1 = new CGAIndividual(children[0], problem.get_sizeProblem());
            child2 = new CGAIndividual(children[1], problem.get_sizeProblem());

            children[0] = NULL;
            children[1] = NULL;
            delete[] children;
            children = NULL;

            child1->mutation(mutation_probability);
            child2->mutation(mutation_probability);

            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
        else {
            child1 = new CGAIndividual(*father);
            child2 = new CGAIndividual(*mother);

            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }
    }

    for (int i = 0; i < population_size; i++)
        delete vec_population[i];

    vec_population = newPopulation;
    findBestSolution();
}

void CGAOptimizer::findBestSolution()
{
    double currentBestFitness = bestFound->getFitness(problem);

    for (int i = 1; i < vec_population.size(); i++)
    {
        if (vec_population.at(i)->getFitness(problem) > currentBestFitness)
        {
            delete bestFound;
            bestFound = new CGAIndividual(*vec_population[i]);
            currentBestFitness = bestFound->getFitness(problem);
        }
    }
}

void CGAOptimizer::showTheBest() {
    cout << "\nNajlepsze rozwiazanie: " << bestFound->getFitness(problem);
}
