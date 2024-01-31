
#ifndef TEMA2_MUTATION_H
#define TEMA2_MUTATION_H

#include <iostream>
#include <vector>

#include "general.h"
#include "chromosome.h"

class Mutation{
private:
    int n{}; /// Population size
    int p{}; /// Precision
    int steps{}; /// No of algorithm steps
    float pc{}, pm{}; /// Crossover and mutation probabilities
    LD tp{}; /// Total performance -> to be set
    domain_type domain{}; /// Defined domain
    std::vector<int> params = {0,0,0}; /// x ^ 2 * params[0] + x * params[1] + params[2]
    std::vector<Chromosome> population; /// Population - list of chromosomes
    std::vector<LD> q; /// Selection interval

    bool DEBUG = false;

    /// Generate function to maximize
    LD f(LD x);

    /// This will actually only return f in our case
    LD fitness(LD x);

    /// u in [0, 1)
    static float get_random_u();

    void set_selection_probabilities(); /// p_i = fitness(X_i) / F
    void set_selection_interval(); /// q_i = p_1 + ... + p_i
    int search_chromosome_on_q(float u); /// search <-> [q_i, q_i+1)
    std::vector<Chromosome> get_selected_population();

    std::pair<Chromosome, Chromosome> cross_split_chromosomes(Chromosome chromosome1, Chromosome chromosome2, int i);
    std::vector<int> get_crossover_marked_population();
    std::vector<Chromosome> get_crossed_population();

    std::vector<Chromosome> get_mutated_population();
    std::vector<int> get_mutation_marked_population() const;

public:

    explicit Mutation(std::istream&, bool = true);

    void set_debug(bool d);
    int get_steps() const;

    /// Read & print_population data
    void read(std::istream &in);
    void print_population(std::ostream &out);

    /// Add chromosomes
    void add_chromosome(std::vector<bool> genes);
    void add_chromosome();

    /// Generate initial population (for first generation only)
    void generate_initial_population();

    /// F = sum(1..n, fitness(X_j))
    LD calculate_total_performance();
    LD get_total_performance();

    /// AVG = F / n
    LD get_avg_performance();

    /// MAX = max f(X)
    LD get_max_performance();

    void mutate();

    Chromosome get_max_chromosome();

    long double get_max_x();
};


#endif //TEMA2_MUTATION_H
