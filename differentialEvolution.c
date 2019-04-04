/* 
 * This implements the DE/rand/1/bin optimization algorithm.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include  <float.h>
#include <limits.h>


#define F 0.9
#define CR 0.1
#define NP 10
#define D 10

double random_uniform_zero_to_one ();
void initialize_individuals (double population[][D], double lower_bound[], double upper_bound[], double individuals_cost[]);
void mutate_recombine_evaluate_and_select( double population[][D], double individuals_cost[]);
double evaluate (double individual[]);
void print_population (double population[][D]);
double best_fitness_of_population (double individuals_cost[]);

void main () {
	int i, j, count = 0, max_generations = 20, generation_of_best_fitness = 0;
	double population[NP][D] = {{0}};
	double individuals_cost[NP] = {0};
	double lower_bound[D] = {[0 ... (D-1)] = -1};
	double upper_bound[D] = {[0 ... (D-1)] = 1};
	double best_global_fitness = DBL_MAX, this_population_fitness;

	initialize_individuals (population, lower_bound, upper_bound, individuals_cost);

	printf("population inicial");
	print_population (population);
	printf("\n");

	/* Halt after max_generations generations. */
	while (count < max_generations) { 
		mutate_recombine_evaluate_and_select (population, individuals_cost);

		this_population_fitness = best_fitness_of_population (individuals_cost);
		printf("this_population_fitness: %f \n", this_population_fitness);
		printf("best_global_fitness: %f \n", best_global_fitness);

		if (this_population_fitness < best_global_fitness) {
			best_global_fitness = this_population_fitness;
			generation_of_best_fitness = count;
		}
		count++;
	}

	printf("population final");
	print_population (population);

	printf("Mejor fitness %f encontrado en la generacion %d\n", best_global_fitness, generation_of_best_fitness);

}

double random_uniform_zero_to_one () {
    return rand() / (RAND_MAX + 1.);
}

void initialize_individuals (double population[][D], double lower_bound[], double upper_bound[], double individuals_cost[]) {
	/* Initialize individuals */
	for (int i=0; i<NP; i++) {  
	    /* randomly initialize all individuals */
	    for (int j=0; j<D; j++) {
	        population[i][j] = lower_bound[j] + random_uniform_zero_to_one()*(upper_bound[j] - lower_bound[j]);
	    }
	    individuals_cost[i] = evaluate(population[i]);
	}
}

void mutate_recombine_evaluate_and_select (double population[][D], double individuals_cost[]) {
	int a, b, c, k;
	double fitness;
	double next_population[NP][D] = {{0}};

	/* Start loop through population. */
    for (int i=0; i<NP; i++) {
		double trial_vector[D] = {0};
        /********** Mutate/recombine **********/
        /* Randomly pick 3 vectors, all different from i */ 
        do a = random_uniform_zero_to_one()*NP; while (a==i); 
        do b = random_uniform_zero_to_one()*NP; while (b==i || b==a);
        do c = random_uniform_zero_to_one()*NP; while (c==i || c==a || c==b);
        
        /* Randomly pick an index for forced evolution change */
        k = random_uniform_zero_to_one()*D;
        /* Load D parameters into trial_vector[]. */
        for (int j=0; j<D; j++) {
            /* Perform D-1 binomial trials. */
            if ((random_uniform_zero_to_one() < CR) || j==k) {
                /* Source for trial_vector[j] is a random vector plus weighted differential */
                trial_vector[j] = population[c][j] + F * (population[a][j] - population[b][j]);
            } else {
                /* or trial_vector parameter comes from population[i][j] itself. */
                trial_vector[j] = population[i][j];
            }
        }
        
        /********** Evaluate/select **********/
        /* Evaluate trial_vector with your function. */ 
        fitness = evaluate(trial_vector);
        /* If trial_vector[] improves on population[i][], move trial_vector[] to next_population and store improved individuals_cost */
        if (fitness <= individuals_cost[i]) {
            for (int j=0; j<D; j++) {
                next_population[i][j] = trial_vector[j];
            }
            individuals_cost[i] = fitness;
        } else {            
            /* otherwise, move population[i][] to secondary array. */ 
            for (int j=0; j<D; j++) {
                next_population[i][j] = population[i][j];
            }
        }
    }
    /********** End of population loop; swap arrays **********/
    for (int i=0; i<NP; i++) {
        /* After each generation, move secondary array into primary array. */
        for (int j=0; j<D; j++) {
            population[i][j] = next_population[i][j];
        }
    } 
}

double evaluate (double individual[]) {
	/*----------Funcion Rosenbrock-----------*/
	double fitness = 0.0;
	double x1;
	double x2;
	
	double diff_x1;
	
	for (int i=0; i<D-1; i++) {
		x1=individual[i];
		x2=individual[i+1];
		diff_x1=x1-1.0;
		fitness=fitness+(100.0*((x2-x1*x1)*(x2-x1*x1)))+(diff_x1*diff_x1);
	}
	
	return fitness;

}

void print_population (double population[][D]) {
	for (int row=0; row<NP; row++) {
	    for (int columns=0; columns<D; columns++) {
	        printf("%f     ", population[row][columns]);
	        }
	    printf("\n");
	 }
}

double best_fitness_of_population (double individuals_cost[]) {
	double best_fitness = DBL_MAX;
	for (int i=0; i<NP; i++) {
		printf("individuals_cost %f\n", individuals_cost[i]);
        if (individuals_cost[i] < best_fitness) {
			best_fitness = individuals_cost[i];
		}
	}
	return best_fitness;
}