/* 
 * This implements the NPE/rand/1/bin optimization algorithm for minimization problems.
 *
 * Franco Morero
 * 2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <omp.h>


void run_diferential_evolution (int max_generations, int D, int NP, float F, float CR);
void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D);
void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR);
void mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D, float F, float CR);
void DE_select (double *individual, double *fitness_of_individual, double *trial_vector, double *fitness_of_trial_vector, int D);
double evaluate (double *individual, int D);
double rosenbrock_function (double *individual, int D);
void copy_population (double **source, double **destination, int NP, int D);
void copy_individual (double *source, double *destination, int D);
void print_population (double **population, int NP, int D);
double best_fitness_of_population (double *individuals_fitness, int NP);
double** init_matrix_with_value (int number_rows, int number_columns, double value);
double** init_matrix (int number_rows, int number_columns);
void set_all_matrix_values_to (double **matrix, int number_rows, int number_columns, double value);
void free_matrix (double **matrix, int number_rows);
double* init_array_with_value (int size, double value);
double* init_array (int size);
void set_all_array_values_to (double *array, int size, double value);
int convert_string_argv_to_int (char** argv, int position);

//#define F 0.9
//#define CR 0.1
//#define D 10
//#define NP 10
#define NUM_THREADS 4


int main (int argc, char **argv) {
	int max_generations;
	int D, NP;
	float F, CR;

	if (argc == 6) {
		D = convert_string_argv_to_int (argv, 1);
		NP = convert_string_argv_to_int (argv, 2);
		max_generations = convert_string_argv_to_int (argv, 3);
		F =  (convert_string_argv_to_int (argv, 4) / 100.0);
		CR = (convert_string_argv_to_int (argv, 5) / 100.0);
	}
	else {
		printf ("usar: ./differentialEvolution.out D NP max_generations F(*100) CR(*100)");
		exit (1);
	}

	//rand48 is uniform[0,1]
	srand48(time(NULL));
	omp_set_num_threads(NUM_THREADS);
	run_diferential_evolution (max_generations, D, NP, F, CR);
}

void run_diferential_evolution (int max_generations, int D, int NP, float F, float CR) {
	int count = 0, generation_of_best_fitness = 0;
	double **population = init_matrix (NP, D);
	double *individuals_fitness = init_array (NP);
	double *lower_bound = init_array_with_value (D, -1);
	double *upper_bound = init_array_with_value (D, 1);
	double best_global_fitness = DBL_MAX, this_population_best_fitness;

	initialize_individuals_randomly (population, lower_bound, upper_bound, individuals_fitness, NP, D);

	//printf("init population");
	//print_population (population, NP, D);
	//printf("\n");

	while (count < max_generations) { 
		mutate_recombine_evaluate_and_select (population, individuals_fitness, NP, D, F, CR);

		this_population_best_fitness = best_fitness_of_population (individuals_fitness, NP);
		if (this_population_best_fitness < best_global_fitness) {
			best_global_fitness = this_population_best_fitness;
			generation_of_best_fitness = count;
		}
		count++;
	}

	//printf("final population");
	//print_population (population, NP, D);

	printf("%d %d %f %f %d %f %d\n", D, NP, F, CR, max_generations, best_global_fitness, generation_of_best_fitness);
	
	free_matrix (population, NP);
	free (individuals_fitness);
	individuals_fitness = NULL;
	free (lower_bound);
	lower_bound = NULL;
	free (upper_bound);
	upper_bound = NULL;
}

void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D) {
	int i, j;
	for (i=0; i<NP; i++) {
	    for (j=0; j<D; j++) {
	        population[i][j] = lower_bound[j] + drand48() * (upper_bound[j] - lower_bound[j]);
	    }
	    individuals_fitness[i] = evaluate(population[i], D);
	}
}

void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR) {
	//trial populations is used as nex population in select
	double **trial_population = init_matrix_with_value (NP, D, 0);
	double *trials_fitness = init_array (NP);
	int i;

	#pragma omp parallel
    {
        #pragma omp for
	    for (i=0; i<NP; i++) {
	        mutate_and_recombine (population, i, trial_population[i], NP, D, F, CR);
	    	trials_fitness[i] = evaluate (trial_population[i], D);
	    }
	}
    for (i=0; i<NP; i++) {
        DE_select (population[i], &individuals_fitness[i], trial_population[i], &trials_fitness[i], D);
    }
    copy_population (trial_population, population, NP, D);

	free_matrix (trial_population, NP);
	free (trials_fitness);
	trials_fitness = NULL;
}

void mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D, float F, float CR) {
	int a, b, c, k, j;
    /* Randomly pick 3 vectors, all different from individual_index */ 
    do a = drand48() * NP; while (a == individual_index); 
    do b = drand48() * NP; while (b == individual_index || b == a);
    do c = drand48() * NP; while (c == individual_index || c == a || c == b);
    /* Randomly pick an index for forced evolution change */
    k = drand48() * D;

    /* Load D parameters into trial_vector[]. */
    for (j=0; j<D; j++) {
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

void DE_select (double *individual, double *fitness_of_individual, double *trial_vector, double *fitness_of_trial_vector, int D) {
    if (*fitness_of_trial_vector <= *fitness_of_individual) {
        *fitness_of_individual = *fitness_of_trial_vector;
    } else {            
		copy_individual (individual, trial_vector, D);
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
	int i;
	for (i=0; i<D-1; i++) {
		x1 = individual[i];
		x2 = individual[i+1];
		diff_x1 = x1 - 1.0;
		fitness = fitness + (100.0 * ((x2 - x1 * x1) * (x2 - x1 * x1))) + (diff_x1 * diff_x1);
	}
	return fitness;
}

void copy_population (double **source, double **destination, int NP, int D) {
	int i;
    for (i=0; i<NP; i++) {
        copy_individual (source[i], destination[i], D);
    } 
}

void copy_individual (double *source, double *destination, int D) {
    int j;
    for (j=0; j<D; j++) {
        destination[j] = source[j];
    }
}

void print_population (double **population, int NP, int D) {
	int row, columns;
	for (row=0; row<NP; row++) {
	    for (columns=0; columns<D; columns++) {
	        printf("%f     ", population[row][columns]);
	        }
	    printf("\n");
	 }
}

double best_fitness_of_population (double *individuals_fitness, int NP) {
	double best_fitness = DBL_MAX;
	int i;
	for (i=0; i<NP; i++) {
        if (individuals_fitness[i] < best_fitness) {
			best_fitness = individuals_fitness[i];
		}
	}
	return best_fitness;
}

double** init_matrix_with_value (int number_rows, int number_columns, double value) {
	double **matrix = init_matrix (number_rows, number_columns);
	set_all_matrix_values_to (matrix, number_rows, number_columns, value);
	return matrix;
}

double** init_matrix (int number_rows, int number_columns) {
	double **matrix = (double **) malloc (number_rows * sizeof(double*));
	int i, j;
	if (matrix  == NULL) {
		printf ("Found problems in memory allocation");
		exit (1);
	}
	for (i=0; i<number_rows; i++) {
    	matrix[i] = init_array (number_columns);
	}
	return matrix;
}

void set_all_matrix_values_to (double **matrix, int number_rows, int number_columns, double value) {
	int i;
	for (i=0; i<number_rows; i++) {
		set_all_array_values_to (matrix[i], number_columns, value);
	}
}

void free_matrix (double **matrix, int number_rows) {
	int i;
	for (i=0; i<number_rows; i++) {
		free (matrix[i]);
		matrix[i] = NULL;
	}
	free (matrix);
	matrix = NULL;
}

double* init_array_with_value (int size, double value) {
	double *array = init_array (size);
	set_all_array_values_to (array, size, value);
	return array;
}

double* init_array (int size) {
	double *array = (double *) malloc (size * sizeof(double));
	if (array  == NULL) {
		printf ("Found problems in memory allocation");
		exit (1);
	}
	return array;
}

void set_all_array_values_to (double *array, int size, double value) {
	int i;
	for (i=0; i<size; i++) {
		array[i] = value;
	}
}

int convert_string_argv_to_int (char** argv, int position) {
	char *p;
	int num;
	errno = 0;
	long conv = strtol(argv[position], &p, 10);

	if (errno != 0 || *p != '\0' || conv > INT_MAX) {
	    printf ("use: ./differentialEvolution.out D NP max_generations F(*100) CR(*100)");
		exit (1);
	} else {
	    num = conv;    
	}
	return num;
}