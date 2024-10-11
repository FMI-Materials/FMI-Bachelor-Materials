#include <fstream>
#include <iostream>
#include <random>
#include <utility>

#include "mutation.h"
#include "chromosome.h"
#include "general.h"

Mutation::Mutation(std::istream &in, bool generate_population) {
    read(in);
    if(generate_population)
        generate_initial_population();
}

void Mutation::read(std::istream &in) {
    scanf("N: %d\nDOMAIN: [%d,%d]\nPARAMETERS: %d %d %d\nP: %d\nPR: %f\nPM: %f\nSTEPS: %d", &n, &domain.a, &domain.b, &params[0], &params[1], &params[2], &p, &pc, &pm, &steps);
}

int Mutation::get_steps() const {
    return steps;
}

void Mutation::set_debug(bool d){
    DEBUG = d;
}

void Mutation::print_population(std::ostream &out){
    if(population.size()!=n) {
        out << "Population not yet set!";
        return;
    }
    for(int i=0;i<n;++i){
        out<<(i+1)<<": "<<population[i].get_string_genome();
        out<<" x= "<<population[i].get_value()<<" f="<<fitness(population[i].get_value());
        out<<'\n';
    }
}

LD Mutation::f(LD x) {
    //return pow(x, 2)*params[0] + x*params[1] + params[2];
    return pow(x, 3) + 3 * pow(x, 2) - 4*x + 7;
}

LD Mutation::fitness(LD x) {
    return f(x);
}

void Mutation::add_chromosome(std::vector<bool> genes){
    population.emplace_back(Chromosome(domain, p, std::move(genes)));
}

void Mutation::add_chromosome(){
    population.emplace_back(Chromosome(domain, p));
}

void Mutation::generate_initial_population() {
    population.clear();
    for(int i=0;i<n;++i)
        add_chromosome();
}

LD Mutation::calculate_total_performance(){
    LD total = 0;
    for(auto &entity: population)
        total += fitness(entity.get_value());
    return total;
}

Chromosome Mutation::get_max_chromosome(){
    Chromosome best = population[0];
    LD maximum = INT_MIN;
    for(auto &entity: population){
        LD ft = fitness(entity.get_value());
        if(ft > maximum){
            maximum = ft;
            best = entity;
        }
    }
    return best;
}

LD Mutation::get_max_performance(){
    return fitness(get_max_chromosome().get_value());
}

LD Mutation::get_max_x(){
    return get_max_chromosome().get_value();
}

LD Mutation::get_avg_performance(){
    return get_total_performance() / n;
}

LD Mutation::get_total_performance(){
    if(tp!=0)
        return tp;
    tp = calculate_total_performance();
    return tp;
}

void Mutation::set_selection_probabilities(){
    for(int i=0;i<n;++i){
        LD p = fitness(population[i].get_value()) / get_total_performance();
        population[i].set_selection_probability(p);
    }

    if(DEBUG){
        std::cout<<"\nSelection probability: \n";
        for(int i=0;i<n;++i){
            std::cout<<(i+1)<<" probability: "<<population[i].get_selection_probability();
            std::cout<<'\n';
        }
    }
}

void Mutation::set_selection_interval(){
    q.clear();
    q.reserve(n+2);
    LD sum = 0;
    for(int i=0;i<n;++i){
        sum += population[i].get_selection_probability();
        q.emplace_back(sum);
    }
    q.emplace_back(0);
    q.emplace_back(1);
    sort(q.begin(), q.end());

    if(DEBUG){
        std::cout<<"\nSelection interval: \n";
        for(auto &i: q)
            std::cout<<i<<' ';
    }
}

int Mutation::search_chromosome_on_q(float u){
    int l = 1, r = n-1;
    while(l<=r){
        int m = (r + l)/2;
        if(q[m-1]<=u && q[m+1]>=u)
            return m;
        else if(q[m]>u)
            r = m - 1;
        else
            l = m + 1;
    }
    return l-1;
}

std::vector<Chromosome> Mutation::get_selected_population(){

    set_selection_probabilities();
    set_selection_interval();

    std::vector<Chromosome> new_population;
    for(int i=0;i<n-1;++i){
        float u = Mutation::get_random_u();

        int c_id = search_chromosome_on_q(u);

        if(DEBUG)
            std::cout<<"u="<<u<<"; choose chromosome: "<<c_id+1<<'\n';

        new_population.emplace_back(population[c_id]);
    }
    return new_population;
}

float Mutation::get_random_u(){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0, 1);
    return distr(eng);
}

std::vector<int> Mutation::get_crossover_marked_population(){
    std::vector<int> crossover_population;
    if(DEBUG)
        std::cout<<"\nCrossover probability: "<<pc<<"\n";
    for(int i=0;i<n;++i){
        float u = get_random_u();
        if(DEBUG)
            std::cout<<(i+1)<<": "<<population[i].get_string_genome()<<" u="<<u;
        if(u<pc){
            crossover_population.emplace_back(i);
            if(DEBUG)
                std::cout<<"<"<<pc<<" participant";
        }
        if(DEBUG)
            std::cout<<'\n';
    }
    return crossover_population;
}

std::pair<Chromosome, Chromosome> Mutation::cross_split_chromosomes(Chromosome chromosome1, Chromosome chromosome2, int i){
    auto chromosome1_genome = chromosome1.get_genome();
    auto chromosome2_genome = chromosome2.get_genome();
    auto new_chromosome1_genome = chromosome1_genome;
    auto new_chromosome2_genome = chromosome2_genome;
    for(int j=0;j<i;++j){
        new_chromosome1_genome[j] = chromosome2_genome[j];
        new_chromosome2_genome[j] = chromosome1_genome[j];
    }
    chromosome1.set_genome(new_chromosome1_genome);
    chromosome2.set_genome(new_chromosome2_genome);
    return {chromosome1, chromosome2};
}

std::vector<Chromosome> Mutation::get_crossed_population(){
    std::vector<Chromosome> crossed_population = population;
    auto marked_ids = get_crossover_marked_population();
    if(DEBUG)
        std::cout<<"\n";
    int total_size = marked_ids.size();
    if(total_size==1)
        return crossed_population;
    if(total_size%2) {
        Chromosome chromosome1 = crossed_population[0], chromosome2 = crossed_population[1], chromosome3 = crossed_population[2];
        int i_point = (int) random() % chromosome1.get_length();
        auto chromosomes_kids_1 = cross_split_chromosomes(chromosome1, chromosome2, i_point);
        auto chromosomes_kids_2 = cross_split_chromosomes(chromosomes_kids_1.second, chromosome3, i_point);
        crossed_population[0] = chromosomes_kids_1.first;
        crossed_population[1] = chromosomes_kids_1.second;
        crossed_population[2] = chromosomes_kids_2.second;
        total_size += 3;
    }
    for(int i=1;i<total_size;i+=2){
        Chromosome chromosome1 = crossed_population[i-1], chromosome2 = crossed_population[i];
        int i_point = (int) random() % chromosome1.get_length();
        auto chromosomes_kids = cross_split_chromosomes(chromosome1, chromosome2, i_point);
        crossed_population[i-1] = chromosomes_kids.first;
        crossed_population[i] = chromosomes_kids.second;
        if(DEBUG){
            std::cout<<"Crossing chromosomes "<<i<<" and "<<i+1<<":\n";
            std::cout<<chromosome1.get_string_genome()<<" "<<chromosome2.get_string_genome()<<" point "<<i_point<<"\n";
            std::cout<<"result: "<<crossed_population[i-1].get_string_genome()<<" "<<crossed_population[i].get_string_genome()<<"\n";
        }
    }

    return crossed_population;
}

std::vector<int> Mutation::get_mutation_marked_population() const{
    std::vector<int> mutation_population;
    if(DEBUG) {
        std::cout << "\nMutation probability for every genome: " << pm << "\n";
        std::cout << "The following chromosomes have been modified:"<<"\n";
    }
    for(int i=0;i<n;++i){
        float u = get_random_u();
        if(u<pc){
            mutation_population.emplace_back(i);
            if(DEBUG)
                std::cout<<i+1<<"\n";
        }
    }
    return mutation_population;
}

std::vector<Chromosome> Mutation::get_mutated_population(){
    auto mutation_ids = get_mutation_marked_population();
    auto mutated_population = population;
    for(auto &i: mutation_ids){
        int p = random() % mutated_population[i].get_length();
        auto genome = mutated_population[i].get_genome();
        genome[p] = !genome[p];
        mutated_population[i].set_genome(genome);
    }
    return mutated_population;
}

void Mutation::mutate() {

    if(DEBUG){
        std::cout<<"\nInitial population: \n";
        print_population(std::cout);
    }

    Chromosome elite = get_max_chromosome();

    /// Selection (selected n-1 population)
    population = std::move(get_selected_population());

    /// Elite selection
    population.emplace_back(elite);

    if(DEBUG){
        std::cout<<"\nAfter selection: \n";
        print_population(std::cout);
    }

    /// Cross population
    population = std::move(get_crossed_population());

    if(DEBUG){
        std::cout<<"\nAfter crossover: \n";
        print_population(std::cout);
    }

    /// Mutate population
    population = std::move(get_mutated_population());

    if(DEBUG){
        std::cout<<"\nAfter mutation: \n";
        print_population(std::cout);
    }
}
