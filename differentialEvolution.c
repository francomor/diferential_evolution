/* 
 * This implements the DE/rand/1/bin optimization algorithm for minimization problems.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>


#define F 0.9
#define CR 0.1
#define NP 10
#define D 10


void run_diferential_evolution (int max_generations);
double random_uniform_zero_to_one ();
void initialize_individuals_randomly (double population[][D], double lower_bound[], double upper_bound[], double individuals_fitness[]);
void mutate_recombine_evaluate_and_select (double population[][D], double individuals_fitness[]);
void mutate_and_recombine (double population[][D], int individual_index, double trial_vector[]);
void evaluate_and_select (double individual[], double *fitness_of_individual, double trial_vector[], double individual_for_next_population[]);
void copy_population (double source[][D], double destination[][D]);
void copy_individual (double source[], double destination[]);
double evaluate (double individual[]);
double rosenbrock_function (double individual[]);
void print_population (double population[][D]);
double best_fitness_of_population (double individuals_fitness[]);


void main () {
	int max_generations = 2;
	run_diferential_evolution (max_generations);
}

void run_diferential_evolution (int max_generations) {
	int count = 0, generation_of_best_fitness = 0;
	double population[NP][D] = {{0}};
	double individuals_fitness[NP] = {0};
	double lower_bound[D] = {[0 ... (D-1)] = -1};
	double upper_bound[D] = {[0 ... (D-1)] = 1};
	double best_global_fitness = DBL_MAX, this_population_best_fitness;

	initialize_individuals_randomly (population, lower_bound, upper_bound, individuals_fitness);

	printf("population inicial");
	print_population (population);
	printf("\n");

	/* Halt after max_generations generations. */
	while (count < max_generations) { 
		mutate_recombine_evaluate_and_select (population, individuals_fitness);

		this_population_best_fitness = best_fitness_of_population (individuals_fitness);
		printf("this_population_best_fitness: %f \n", this_population_best_fitness);
		printf("best_global_fitness: %f \n", best_global_fitness);

		if (this_population_best_fitness < best_global_fitness) {
			best_global_fitness = this_population_best_fitness;
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

void initialize_individuals_randomly (double population[][D], double lower_bound[], double upper_bound[], double individuals_fitness[]) {
	for (int i=0; i<NP; i++) {  
	    for (int j=0; j<D; j++) {
	        population[i][j] = lower_bound[j] + random_uniform_zero_to_one() * (upper_bound[j] - lower_bound[j]);
	    }
	    individuals_fitness[i] = evaluate(population[i]);
	}
}

void mutate_recombine_evaluate_and_select (double population[][D], double individuals_fitness[]) {
	double next_population[NP][D] = {{0}};

	/* Start loop through population. */
    for (int i=0; i<NP; i++) {
		double trial_vector[D] = {0};
        mutate_and_recombine (population, i, trial_vector);
        evaluate_and_select (population[i], &individuals_fitness[i], trial_vector, next_population[i]);
        
    }
    /********** End of population loop; swap arrays **********/
    copy_population (next_population, population);
}

void mutate_and_recombine (double population[][D], int individual_index, double trial_vector[]) {
	int a, b, c, k;
    /* Randomly pick 3 vectors, all different from individual_index */ 
    do a = random_uniform_zero_to_one()*NP; while (a==individual_index); 
    do b = random_uniform_zero_to_one()*NP; while (b==individual_index || b==a);
    do c = random_uniform_zero_to_one()*NP; while (c==individual_index || c==a || c==b);
    /* Randomly pick an index for forced evolution change */
    k = random_uniform_zero_to_one()*D;

    /* Load D parameters into trial_vector[]. */
    for (int j=0; j<D; j++) {
        /* Perform D-1 binomial trials. */
        if ((random_uniform_zero_to_one() < CR) || j==k) {
            /* Source for trial_vector[j] is a random vector plus weighted differential */
            trial_vector[j] = population[c][j] + F * (population[a][j] - population[b][j]);
        } else {
            /* or trial_vector parameter comes from population[individual_index][j] itself. */
            trial_vector[j] = population[individual_index][j];
        }
    }
}

void evaluate_and_select (double individual[], double *fitness_of_individual, double trial_vector[], double individual_for_next_population[]) {
	double fitness_of_trial_vector;
    fitness_of_trial_vector = evaluate(trial_vector);

    printf("*fitness_of_trial_vector %f\n", fitness_of_trial_vector);
    printf("*fitness_of_individual %f\n", *fitness_of_individual);
    
    if (fitness_of_trial_vector <= *fitness_of_individual) {
		copy_individual (trial_vector, individual_for_next_population);
        *fitness_of_individual = fitness_of_trial_vector;
    } else {            
		copy_individual (individual, individual_for_next_population);
    }
}

void copy_individual (double source[], double destination[]){
    for (int j=0; j<D; j++) {
        destination[j] = source[j];
    }
}

void copy_population (double source[][D], double destination[][D]){
    for (int i=0; i<NP; i++) {
        copy_individual (source[i], destination[i]);
    } 
}

double evaluate (double individual[]) {
	return rosenbrock_function (individual);
}

double rosenbrock_function (double individual[]) {
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

double best_fitness_of_population (double individuals_fitness[]) {
	double best_fitness = DBL_MAX;
	for (int i=0; i<NP; i++) {
		printf("individuals_fitness[%d] %f\n", i, individuals_fitness[i]);
        if (individuals_fitness[i] < best_fitness) {
			best_fitness = individuals_fitness[i];
		}
	}
	return best_fitness;
}