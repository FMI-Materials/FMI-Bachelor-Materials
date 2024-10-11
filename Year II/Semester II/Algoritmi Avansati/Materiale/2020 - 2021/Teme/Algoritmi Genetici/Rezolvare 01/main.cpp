#include <iostream>
#include <cstdio>
#include <iomanip>

#include "algorithm/mutation.h"

/// Test how many times the algorithm has a better end result after m mutations
float get_accuracy(int tries){
    int better = 0;
    auto* mutation = new Mutation(std::cin);
    for(int i=0;i<tries;++i){
        mutation->generate_initial_population();
        LD initial_performance = mutation->get_max_performance();
        for(int t=1;t<mutation->get_steps();t++)
            mutation->mutate();
        LD final_performance = mutation->get_max_performance();
        if(final_performance>initial_performance)
            better++;
    }
    return (float) better / (float) tries;
}

int main() {
    freopen("data/settings.txt", "r", stdin);
    freopen("data/evolutie.txt", "w", stdout);

    //std::cout<<"accuracy: "<<get_accuracy(100)*100<<"%";

    /// Initiate first mutation, read settings from file
    auto* mutation = new Mutation(std::cin);
    /// Set debug mode on (print steps)
    mutation->set_debug(true);
    /// Mutate population
    mutation->mutate();

    std::cout<<"\nMax Evolution ("<<mutation->get_steps()<<" steps): \n";
    for(int t=1;t<mutation->get_steps();t++){
        /// Set debug mode off
        mutation->set_debug(false);
        /// Show max and average performance
        std::cout<<"X: "<<std::setprecision(16)<<mutation->get_max_x()<<' ';
        std::cout<<std::setprecision(16)<<"MAX: "<<mutation->get_max_performance()<<' ';
        std::cout<<std::setprecision(16)<<"AVG: "<<mutation->get_avg_performance()<<'\n';
        /// Mutate
        mutation->mutate();
    }

    return 0;
}
