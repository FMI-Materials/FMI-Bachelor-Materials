#ifndef TEMA2_CHROMOSOME_H
#define TEMA2_CHROMOSOME_H

#include <utility>
#include <vector>

#include "general.h"

class Chromosome {
private:
    int l = 0; /// Chromosome length
    domain_type domain; /// Domain
    int p; /// Precision
    LD ps{}; /// Selection probability - to be set
    std::vector<bool> genes; /// Encoded chromosome

    /// Calculate chromosome length
    /// l = log((b - a) * 10 ^ p)
    void set_length();

public:

    Chromosome(domain_type d, int p): domain(d), p(p){
        set_length();
        generate_random();
    }
    Chromosome(domain_type d, int p, std::vector<bool> genes): domain(d), p(p), genes(std::move(genes)){
        set_length();
    }

    /// Set chromosome genes
    void set_genome(std::vector<bool> genes);

    /// Get and set chromosome length
    int get_length();

    /// Decode chromosome - get value on interval
    LD get_value() const;

    /// Generate random chromosome genes
    void generate_random();

    /// Get genome as a string or as a vector
    const std::vector<bool> &get_genome() const;
    std::string get_string_genome();

    /// Get and set selection probability
    LD get_selection_probability() const;
    void set_selection_probability(LD ps);
};


#endif //TEMA2_CHROMOSOME_H
