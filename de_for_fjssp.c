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
#include <omp.h>
#include <stdbool.h>
#include "readInstance.h"


int convert_string_argv_to_int (char** argv, int position);
void run_diferential_evolution_for_fjssp (char *filename, int max_generations, int NP, float F, float CR);
double** init_matrix (int number_rows, int number_columns);
void free_matrix (double **matrix, int number_rows);
void set_all_matrix_values_to (double **matrix, int number_rows, int number_columns, double value);
double** init_matrix_with_value (int number_rows, int number_columns, double value);
double* init_array (int size);
double* init_array_with_value (int size, double value);
void set_all_array_values_to (double *array, int size, double value);
void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D, int *number_operations_per_job, int number_of_jobs);
void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR, int *number_operations_per_job, int number_of_jobs);
void mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D, float F, float CR);
void DE_select (double *individual, double *fitness_of_individual, double *trial_vector, double *fitness_of_trial_vector, int D);
void copy_population (double **source, double **destination, int NP, int D);
void copy_individual (double *source, double *destination, int D);
double evaluate (double *individual, int D, int *number_operations_per_job, int number_of_jobs);
double rosenbrock_function (double *individual, int D);
void print_population (double **population, int NP, int D);
double best_fitness_of_population (double *individuals_fitness, int NP);
int* init_int_array (int size);
void decode_solution (double *individual, int D, int *number_operations_per_job, int number_of_jobs);
void swap_double (double *a, double *b);
void swap_int (int *a, int *b);
void bubbleSort (double *array, int *id_array, int n);

//#define F 0.9
//#define CR 0.1
//#define D 10
//#define NP 10

int main (int argc, char **argv) {
    int max_generations, NP;
    char *filename;
    float F, CR;
    if (argc == 6) {
        filename = argv[1];
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
    run_diferential_evolution_for_fjssp (filename, max_generations, NP, F, CR);
}

int convert_string_argv_to_int (char** argv, int position) {
    char *p;
    int num;
    errno = 0;
    long conv = strtol(argv[position], &p, 10);

    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || *p != '\0' || conv > INT_MAX) {
        printf ("usar: ./differentialEvolution.out D NP max_generations F(*100) CR(*100)");
        printf ("usar: ./differentialEvolution.out D NP max_generations F(*100) CR(*100)");
        exit (1);
    } else {
        num = conv;    
    }
    return num;
}

void run_diferential_evolution_for_fjssp (char *filename, int max_generations, int NP, float F, float CR) {
    int D;
    int **job_data, **job_id_x_operation_id;
    int *number_operations_per_job;
    int number_of_machines, number_of_jobs, number_of_operations = 0;
    readInstanceFJJ (filename, &job_data, &number_of_machines, &number_of_jobs, &number_operations_per_job, &job_id_x_operation_id, &number_of_operations);
    D = number_of_operations;

    int count = 0, generation_of_best_fitness = 0;
    double **population = init_matrix (NP, D);
    double *individuals_fitness = init_array (NP);
    double *lower_bound = init_array_with_value (D, -1);
    double *upper_bound = init_array_with_value (D, 1);
    double best_global_fitness = DBL_MAX, this_population_best_fitness;

    initialize_individuals_randomly (population, lower_bound, upper_bound, individuals_fitness, NP, D, number_operations_per_job, number_of_jobs);
    // printf("number_of_jobs: %d\n", number_of_jobs);
    // printf("number_of_machines: %d\n", number_of_machines);
    // printf("number_of_operations: %d\n", number_of_operations);
    // printf("job_data\n");
    //     int row, columns;
    //     for (row=0; row<number_of_operations; row++) {
    //         for (columns=0; columns<number_of_machines; columns++) {
    //             printf("%d     ", job_data[row][columns]);
    // //decode_solution (population[row], D);
    //         }
    //         printf("\n");
    //     }
    // printf("job_id_x_operation_id\n");
    //     for (row=0; row<number_of_operations; row++) {
    //         for (columns=0; columns<2; columns++) {
    //             printf("%d     ", job_id_x_operation_id[row][columns]);
    // //decode_solution (population[row], D);
    //         }
    //         printf("\n");
    //     }

    // //imprimir operation_id
    //     printf("\n");
    // printf("number_operations_per_job\n");
    // int i;
    // for (i=0; i<number_of_jobs; i++) {
    //     printf("%d     ", number_operations_per_job[i]);
    // }
    // printf("\n");

    

    // printf("population inicial");
    // print_population (population, NP, D);
    // printf("\n");

    /* Halt after max_generations generations. */
    while (count < max_generations) { 
        mutate_recombine_evaluate_and_select (population, individuals_fitness, NP, D, F, CR, number_operations_per_job, number_of_jobs);

        this_population_best_fitness = best_fitness_of_population (individuals_fitness, NP);
        //printf("this_population_best_fitness: %f \n", this_population_best_fitness);
        //printf("best_global_fitness: %f \n", best_global_fitness);

        if (this_population_best_fitness < best_global_fitness) {
            best_global_fitness = this_population_best_fitness;
            generation_of_best_fitness = count;
        }
        count++;
    }

    // printf("population final");
    // print_population (population, NP, D);

    //printf("Mejor fitness %f encontrado en la generacion %d\n", best_global_fitness, generation_of_best_fitness);
    printf("%d %d %f %f %d %f %d\n", D, NP, F, CR, max_generations, best_global_fitness, generation_of_best_fitness);
    
    free_matrix (population, NP);
    free (individuals_fitness);
    individuals_fitness = NULL;
    free (lower_bound);
    lower_bound = NULL;
    free (upper_bound);
    upper_bound = NULL;
}

double** init_matrix (int number_rows, int number_columns) {
    double **matrix = (double **) malloc (number_rows * sizeof(double*));
    int i;
    if (matrix  == NULL) {
        printf ("Problemas reservando memoria");
        exit (1);
    }
    for (i=0; i<number_rows; i++) {
        matrix[i] = init_array (number_columns);
    }
    return matrix;
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

void set_all_matrix_values_to (double **matrix, int number_rows, int number_columns, double value) {
    int i;
    for (i=0; i<number_rows; i++) {
        set_all_array_values_to (matrix[i], number_columns, value);
    }
}

double** init_matrix_with_value (int number_rows, int number_columns, double value) {
    double **matrix = init_matrix (number_rows, number_columns);
    set_all_matrix_values_to (matrix, number_rows, number_columns, value);
    return matrix;
}

double* init_array (int size) {
    double *array = (double *) malloc (size * sizeof(double));
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
    int i;
    for (i=0; i<size; i++) {
        array[i] = value;
    }
}

void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D, int *number_operations_per_job, int number_of_jobs) {
    int i, j;
    for (i=0; i<NP; i++) {
        for (j=0; j<D; j++) {
            population[i][j] = lower_bound[j] + drand48() * (upper_bound[j] - lower_bound[j]);
        }
        individuals_fitness[i] = evaluate(population[i], D, number_operations_per_job, number_of_jobs);
    }
}

void mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR, int *number_operations_per_job, int number_of_jobs) {
    //trial populations is used as nex population in select
    double **trial_population = init_matrix_with_value (NP, D, 0);
    double *trials_fitness = init_array (NP);
    int i;

    /* Start loop through population. */
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        //printf("%d\n", omp_get_thread_num());
        #pragma omp for
        for (i=0; i<NP; i++) {
            mutate_and_recombine (population, i, trial_population[i], NP, D, F, CR);
            trials_fitness[i] = evaluate (trial_population[i], D, number_operations_per_job, number_of_jobs);
        }
    }
    for (i=0; i<NP; i++) {
        DE_select (population[i], &individuals_fitness[i], trial_population[i], &trials_fitness[i], D);
    }
        
    /********** End of population loop; swap arrays **********/
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

double evaluate (double *individual, int D, int *number_operations_per_job, int number_of_jobs) {
    decode_solution (individual, D, number_operations_per_job, number_of_jobs);
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

int* init_int_array (int size) {
    int *array = (int *) malloc (size * sizeof(int));
    if (array == NULL) {
        printf ("Problemas reservando memoria");
        exit (1);
    }
    return array;
}

void decode_solution (double *individual, int D, int *number_operations_per_job, int number_of_jobs) {
    int *operation_id = init_int_array (D); 
    int *solution_in_permutations = init_int_array (D); 
    int i;
    for (i=0; i<D; i++) {
        operation_id[i] = i + 1;
    }

    double *individual_for_work = init_array (D);
    copy_individual (individual, individual_for_work, D);

    bubbleSort (individual_for_work, operation_id, D);

    //imprimir operation_id
    printf("operation_id");
        printf("\n");
    for (i=0; i<D; i++) {
        printf("%d     ", operation_id[i]);
    }
        printf("\n");
    // //imprimir individuo
    // printf("individual_for_work\n");
    // for (i=0; i<D; i++) {
    //     printf("%f     ", individual_for_work[i]);
    // }
    //     printf("\n");

    //hay que hacer la parte de que cambie todos por los 1
    printf("number_of_jobs: %d\n", number_of_jobs);
    printf("number_operations_per_job\n");
    for (i=0; i<number_of_jobs; i++) {
        printf("%d     ", number_operations_per_job[i]);
    }
    printf("\n");

    int operation_lower_bound = 0, operation_upper_bound, k;
    for (i=0; i<number_of_jobs; i++) {
        //printf("operation_lower_bound: %d\n\n", operation_lower_bound);
        operation_upper_bound = number_operations_per_job[i] + operation_lower_bound;
        //printf("operation_upper_bound: %d\n\n", operation_upper_bound);
        for (k=0; k<D; k++) {
            if(operation_lower_bound <= operation_id[k] && operation_id[k] <= operation_upper_bound) {
                operation_id[k] = i + 1;
            }
        }
        operation_lower_bound = number_operations_per_job[i] + operation_lower_bound;
    }
    printf("\n");

  //imprimir operation_id
    printf("operation_id_mod");
        printf("\n");
    for (i=0; i<D; i++) {
        printf("%d     ", operation_id[i]);
    }
        printf("\n");

    free (operation_id);
    operation_id = NULL;
    free (individual_for_work);
    individual_for_work = NULL;
}

void swap_double (double *a, double *b) { 
    double temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void swap_int (int *a, int *b) { 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void bubbleSort (double *array, int *id_array, int n) { 
    int i, j; 
    bool swapped; 
    for (i=0; i<n-1; i++) { 
        swapped = false; 
        for (j=0; j<n-i-1; j++) { 
            if (array[j] < array[j+1]) { 
                swap_double(&array[j], &array[j+1]); 
                swap_int(&id_array[j], &id_array[j+1]); 
                swapped = true; 
            } 
        } 
  
        // IF no two elements were swapped by inner loop, then break 
        if (swapped == false) 
            break; 
    } 
} 