/* 
 * This implements the NPE/rand/1/bin optimization algorithm for minimization problems.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

#define F 0.9
#define CR 0.1

int convert_string_argv_to_int (char** argv, int position);
void run_diferential_evolution (int max_generations, int D, int NP);
double** init_matrix (int number_rows, int number_columns);
void free_matrix (double **matrix, int number_rows);
double* init_array (int size);
double* init_array_with_value (int size, double value);
void set_all_array_values_to (double *array, int size, double value);
void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D);
void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D);
void mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D);
void evaluate_and_select (double *individual, double *fitness_of_individual, double *trial_vector, double *individual_for_next_population, int D);
void copy_population (double **source, double **destination, int NP, int D);
void copy_individual (double *source, double *destination, int D);
double evaluate (double *individual, int D);
double rosenbrock_function (double *individual, int D);
void print_population (double **population, int NP, int D);
double best_fitness_of_population (double *individuals_fitness, int NP);


int main (int argc, char **argv) {
	int max_generations;
	int D, NP;

	if (argc == 4) {
		D = convert_string_argv_to_int (argv, 1);
		NP = convert_string_argv_to_int (argv, 2);
		max_generations = convert_string_argv_to_int (argv, 3);
	}
	else {
		printf ("usar: ./differentialEvolution.out D NP max_generations");
		exit (1);
	}

	//double *lower_bound = init_array_with_value (D, -1);
	//rand48 is uniform[0,1]
	srand48(time(NULL));
	run_diferential_evolution (max_generations, D, NP);
}

int convert_string_argv_to_int (char** argv, int position) {
	char *p;
	int num;
	errno = 0;
	long conv = strtol(argv[position], &p, 10);

	// Check for errors: e.g., the string does not represent an integer
	// or the integer is larger than int
	if (errno != 0 || *p != '\0' || conv > INT_MAX) {
	    printf ("usar: ./differentialEvolution.out D NP max_generations");
		exit (1);
	} else {
	    num = conv;    
	}
	return num;
}

void run_diferential_evolution (int max_generations, int D, int NP) {
	int count = 0, generation_of_best_fitness = 0;
	double **population = init_matrix (NP, D);
	//double population[NP][D] = {{0}};
	double *individuals_fitness = init_array (NP);
	//double individuals_fitness[NP] = {0};
	double *lower_bound = init_array_with_value (D, -1);
	//double lower_bound[D] = {[0 ... (D-1)] = -1};
	double *upper_bound = init_array_with_value (D, 1);
	//double upper_bound[D] = {[0 ... (D-1)] = 1};
	double best_global_fitness = DBL_MAX, this_population_best_fitness;

	initialize_individuals_randomly (population, lower_bound, upper_bound, individuals_fitness, NP, D);

	printf("population inicial");
	print_population (population, NP, D);
	printf("\n");

	/* Halt after max_generations generations. */
	while (count < max_generations) { 
		mutate_recombine_evaluate_and_select (population, individuals_fitness, NP, D);

		this_population_best_fitness = best_fitness_of_population (individuals_fitness, NP);
		printf("this_population_best_fitness: %f \n", this_population_best_fitness);
		printf("best_global_fitness: %f \n", best_global_fitness);

		if (this_population_best_fitness < best_global_fitness) {
			best_global_fitness = this_population_best_fitness;
			generation_of_best_fitness = count;
		}
		count++;
	}

	printf("population final");
	print_population (population, NP, D);

	printf("Mejor fitness %f encontrado en la generacion %d\n", best_global_fitness, generation_of_best_fitness);
	
	free_matrix (population, NP);
	free (individuals_fitness);
	individuals_fitness = NULL;
	free (lower_bound);
	lower_bound = NULL;
	free (upper_bound);
	upper_bound = NULL;
}

double** init_matrix (int number_rows, int number_columns) {
	double **matrix = malloc (number_rows * sizeof(double*));
	if (matrix  == NULL) {
		printf ("Problemas reservando memoria");
		exit (1);
	}
	for (int i=0; i<number_rows; i++) {
	    for (int j=0; j<number_columns; j++) {
	    	matrix[i] = init_array (number_columns);
	    }
	}
	return matrix;
}

void free_matrix (double **matrix, int number_rows) {
	for (int i=0; i<number_rows; i++) {
		free (matrix[i]);
		matrix[i] = NULL;
	}
	free (matrix);
	matrix = NULL;
}

double* init_array (int size) {
	double *array = malloc (size * sizeof(double));
	if (array  == NULL) {
		printf ("Problemas reservando memoria");
		exit (1);
	}
	return array;
}

double* init_array_with_value (int size, double value) {
	double *array = init_array (size);
	set_all_array_values_to (array, size, value);
	return array;
}

void set_all_array_values_to (double *array, int size, double value) {
	for (int i=0; i<size; i++) {
		array[i] = value;
	}
}

void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D) {
	for (int i=0; i<NP; i++) {
	    for (int j=0; j<D; j++) {
	        population[i][j] = lower_bound[j] + drand48() * (upper_bound[j] - lower_bound[j]);
	    }
	    individuals_fitness[i] = evaluate(population[i], D);
	}
}

void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D) {
	//double next_population[NP][D] = {{0}};
	double **next_population = init_matrix (NP, D);
	
	//double trial_vector[D] = {0};
	double *trial_vector = init_array (D);
	/* Start loop through population. */
    for (int i=0; i<D; i++) {
    	set_all_array_values_to (trial_vector, D, 0);
        mutate_and_recombine (population, i, trial_vector, NP, D);
        evaluate_and_select (population[i], &individuals_fitness[i], trial_vector, next_population[i], D);
        
    }
    /********** End of population loop; swap arrays **********/
    copy_population (next_population, population, NP, D);


    free (trial_vector);
	trial_vector = NULL;
	free_matrix (next_population, NP);
}

void mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D) {
	int a, b, c, k;
    /* Randomly pick 3 vectors, all different from individual_index */ 
    do a = drand48() * NP; while (a == individual_index); 
    do b = drand48() * NP; while (b == individual_index || b == a);
    do c = drand48() * NP; while (c == individual_index || c == a || c == b);
    /* Randomly pick an index for forced evolution change */
    k = drand48() * D;

    /* Load D parameters into trial_vector[]. */
    for (int j=0; j<D; j++) {
        /* Perform NP-1 binomial trials. */
        if ((drand48() < CR) || j==k) {
            /* Source for trial_vector[j] is a random vector plus weighted differential */
            trial_vector[j] = population[c][j] + F * (population[a][j] - population[b][j]);
        } else {
            /* or trial_vector parameter comes from population[individual_index][j] itself. */
            trial_vector[j] = population[individual_index][j];
        }
    }
}

void evaluate_and_select (double *individual, double *fitness_of_individual, double *trial_vector, double *individual_for_next_population, int D) {
	double fitness_of_trial_vector;
    fitness_of_trial_vector = evaluate(trial_vector, D);

    printf("*fitness_of_trial_vector %f\n", fitness_of_trial_vector);
    printf("*fitness_of_individual %f\n", *fitness_of_individual);
    
    if (fitness_of_trial_vector <= *fitness_of_individual) {
		copy_individual (trial_vector, individual_for_next_population, D);
        *fitness_of_individual = fitness_of_trial_vector;
    } else {            
		copy_individual (individual, individual_for_next_population, D);
    }
}

void copy_population (double **source, double **destination, int NP, int D) {
    for (int i=0; i<NP; i++) {
        copy_individual (source[i], destination[i], D);
    } 
}

void copy_individual (double *source, double *destination, int D) {
    for (int j=0; j<D; j++) {
        destination[j] = source[j];
    }
}

double evaluate (double *individual, int D) {
	return rosenbrock_function (individual, D);
}

double rosenbrock_function (double *individual, int D) {
	double fitness = 0.0;
	double x1;
	double x2;
	double diff_x1;
	for (int i=0; i<D-1; i++) {
		x1 = individual[i];
		x2 = individual[i+1];
		diff_x1 = x1 - 1.0;
		fitness = fitness + (100.0 * ((x2 - x1 * x1) * (x2 - x1 * x1))) + (diff_x1 * diff_x1);
	}
	return fitness;
}

void print_population (double **population, int NP, int D) {
	for (int row=0; row<NP; row++) {
	    for (int columns=0; columns<D; columns++) {
	        printf("%f     ", population[row][columns]);
	        }
	    printf("\n");
	 }
}

double best_fitness_of_population (double *individuals_fitness, int NP) {
	double best_fitness = DBL_MAX;
	for (int i=0; i<NP; i++) {
		printf("individuals_fitness[%d] %f\n", i, individuals_fitness[i]);
        if (individuals_fitness[i] < best_fitness) {
			best_fitness = individuals_fitness[i];
		}
	}
	return best_fitness;
}