/* 
 * This implements and hybrid DE NPE/rand/1/bin optimization algorithm 
 * with local search for FJSSP problem.
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
#include <stdbool.h>
#include <sys/time.h>
#include "standard/readInstance.h"
#include "standard/evaluate.h"
#include "standard/userTypeDef.h"


void run_diferential_evolution_for_fjssp (char *filename_of_FJSSP_instance, int NP, float F, float CR, double PLS);
void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
void DE_mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
void DE_mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D, float F, float CR);
void DE_select (double *individual, double *fitness_of_individual, double *trial_vector, double *fitness_of_trial_vector, int D);
double DE_evaluate (double *individual, int D, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
int* decode_solution (double *individual, int D, int *number_operations_per_job, int number_of_jobs);
int* init_permutation_vector_for_individual (double *individual, int D);
void change_permutation_vector_to_permutation_with_repetitions (int *permutation_vector, int D, int *number_operations_per_job, int number_of_jobs);
int run_local_search (double **population, int NP, int D, double PLS, double *individuals_fitness, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
int run_aggressive_local_search (double **population, int NP, int D, double PLS, double *individuals_fitness, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
bool LS_evaluate_and_select (double *individual, int D, double *fitness_of_individual, int index1, int index2, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs);
double best_fitness_of_population (double **population, double *individuals_fitness, int NP, double *best_individual, int D);
void copy_population (double **source, double **destination, int NP, int D);
void copy_individual (double *source, double *destination, int D);
void print_population (double **population, int NP, int D);
void bubbleSort (double *array, int *id_array, int n);
void swap_double (double *a, double *b);
void swap_int (int *a, int *b);
double** init_matrix_with_value (int number_rows, int number_columns, double value);
double** init_matrix (int number_rows, int number_columns);
void set_all_matrix_values_to (double **matrix, int number_rows, int number_columns, double value);
void free_matrix (double **matrix, int number_rows);
double* init_array_with_value (int size, double value);
double* init_array (int size);
void set_all_array_values_to (double *array, int size, double value);
int* init_int_array (int size);
int convert_string_argv_to_int (char** argv, int position);


#define NUM_THREADS 4

long int total_eval; //need for evaluate.h, i don't use
int main (int argc, char **argv) {
    int NP;
    char *filename_of_FJSSP_instance;
    float F, CR;
    double PLS; //probability of local search
    if (argc == 6) {
        filename_of_FJSSP_instance = argv[1];
        NP = convert_string_argv_to_int (argv, 2);
        F = (convert_string_argv_to_int (argv, 3) / 100.0);
        CR = (convert_string_argv_to_int (argv, 4) / 100.0);
        PLS = (convert_string_argv_to_int (argv, 5) / 100.0);
    }
    else {
        printf ("use: ./differentialEvolution.out filename_of_FJSSP_instance NP F(*100) CR(*100) PLS(*100)");
        exit (1);
    }

    //rand48 is uniform[0,1]
    srand48(time(NULL));
    omp_set_num_threads(NUM_THREADS);
    run_diferential_evolution_for_fjssp (filename_of_FJSSP_instance, NP, F, CR, PLS);
}

void run_diferential_evolution_for_fjssp (char *filename_of_FJSSP_instance, int NP, float F, float CR, double PLS) {
    int D, total_of_evaluation_in_local_search = 0;
    int **job_data, **job_id_x_operation_id;
    int *number_operations_per_job;
    int number_of_machines, number_of_jobs, number_of_operations = 0;
    
    readInstanceFJJ (filename_of_FJSSP_instance, &job_data, &number_of_machines, &number_of_jobs, &number_operations_per_job, &job_id_x_operation_id, &number_of_operations);
    D = number_of_operations;
    double final_time = (number_of_operations * (number_of_operations / 2) * 30) / NUM_THREADS;

    int total_iter, generation_of_best_fitness = 0;
    double **population = init_matrix (NP, D);
    double *individuals_fitness = init_array (NP);
    double *lower_bound = init_array_with_value (D, -1);
    double *upper_bound = init_array_with_value (D, 1);
    double *best_individual = init_array (D);
    double best_global_fitness = DBL_MAX, this_population_best_fitness;
    time_t initial_time = time (NULL), time_of_best_global_fitness = time (NULL);
    time_t total_time, t_ini = time(NULL);

    initialize_individuals_randomly (population, lower_bound, upper_bound, individuals_fitness, NP, D, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
    // printf("init population");
    // print_population (population, NP, D);
    // printf("\n");
    total_iter = 0;
    do {
        DE_mutate_recombine_evaluate_and_select (population, individuals_fitness, NP, D, F, CR, job_data, number_operations_per_job, number_of_machines, number_of_jobs);

        this_population_best_fitness = best_fitness_of_population (population, individuals_fitness, NP, best_individual, D);
        if (this_population_best_fitness < best_global_fitness) {
            best_global_fitness = this_population_best_fitness;
            generation_of_best_fitness = total_iter;
            time_of_best_global_fitness = time (NULL) - initial_time;
        }

        total_of_evaluation_in_local_search = total_of_evaluation_in_local_search + run_local_search (population, NP, D, PLS, individuals_fitness, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
        total_iter ++;
        total_time = (time(NULL) - t_ini) * 1000;
    } while ((total_time < final_time)); //milisegundos   

    // printf("final population");
    // print_population (population, NP, D);

    time_t total_running_time = time (NULL) - initial_time;
    
    cout << D << " ";
    cout << NP << " ";
    cout << F << " ";
    cout << CR << " ";
    cout << PLS << " ";
    cout << total_iter << " ";
    cout << best_global_fitness << " ";
    cout << generation_of_best_fitness << " ";
    cout << time_of_best_global_fitness << " ";
    cout << total_running_time << " ";
    cout << total_of_evaluation_in_local_search << " ";
    int *best_individual_decode = decode_solution (best_individual, D, number_operations_per_job, number_of_jobs);
    cout << "[";
    for (int i=0; i<D; i++) {
        cout << best_individual_decode[i] << ",";
    }
    cout << "]" << " \n";
    
    free_matrix (population, NP);
    free (individuals_fitness);
    individuals_fitness = NULL;
    free (best_individual);
    best_individual = NULL;
    free (best_individual_decode);
    best_individual_decode = NULL;
    free (lower_bound);
    lower_bound = NULL;
    free (upper_bound);
    upper_bound = NULL;
}

void initialize_individuals_randomly (double **population, double *lower_bound, double *upper_bound, double *individuals_fitness, int NP, int D, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    int i, j;
    for (i=0; i<NP; i++) {
        for (j=0; j<D; j++) {
            population[i][j] = lower_bound[j] + drand48() * (upper_bound[j] - lower_bound[j]);
        }
        individuals_fitness[i] = DE_evaluate (population[i], D, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
    }
}

void DE_mutate_recombine_evaluate_and_select (double **population, double *individuals_fitness, int NP, int D, float F, float CR, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    //trial populations is used as next population in select
    double **trial_population = init_matrix_with_value (NP, D, 0);
    double *trials_fitness = init_array (NP);
    int i;

    #pragma omp parallel
    {
        #pragma omp for
        for (i=0; i<NP; i++) {
            DE_mutate_and_recombine (population, i, trial_population[i], NP, D, F, CR);
            trials_fitness[i] = DE_evaluate (trial_population[i], D, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
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

void DE_mutate_and_recombine (double **population, int individual_index, double *trial_vector, int NP, int D, float F, float CR) {
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

double DE_evaluate (double *individual, int D, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    //current_fitness and evaluation_up_to_date are necessary for evaluate from standard
    double fitness, current_fitness = 0;
    int evaluation_up_to_date = 1;
    Solution *solution = new Solution;
    solution->op = init_int_array (D); 
    solution->job = decode_solution (individual, D, number_operations_per_job, number_of_jobs);
    fitness = evaluate(*solution, current_fitness , number_of_machines, number_of_jobs, D, number_operations_per_job, job_data, evaluation_up_to_date);

    free (solution->op);
    free (solution->job);
    free (solution);
    return fitness;
}

int* decode_solution (double *individual, int D, int *number_operations_per_job, int number_of_jobs) {
    int *solution = init_permutation_vector_for_individual (individual, D); 
    change_permutation_vector_to_permutation_with_repetitions (solution, D, number_operations_per_job, number_of_jobs);
    return solution;
}

int* init_permutation_vector_for_individual (double *individual, int D) {
    int *permutation_vector = init_int_array (D); 
    double *individual_for_work = init_array (D);
    int i;
    for (i=0; i<D; i++) {
        permutation_vector[i] = i + 1;
    }
    copy_individual (individual, individual_for_work, D);
    bubbleSort (individual_for_work, permutation_vector, D);
    
    free (individual_for_work);
    individual_for_work = NULL;
    return permutation_vector;
}

void change_permutation_vector_to_permutation_with_repetitions (int *permutation_vector, int D, int *number_operations_per_job, int number_of_jobs) {
    int operation_lower_bound = 0, operation_upper_bound, i, j;
    for (i=0; i<number_of_jobs; i++) {
        operation_upper_bound = number_operations_per_job[i] + operation_lower_bound;
        for (j=0; j<D; j++) {
            if(operation_lower_bound <= permutation_vector[j] && permutation_vector[j] <= operation_upper_bound) {
                permutation_vector[j] = i + 1;
            }
        }
        operation_lower_bound = number_operations_per_job[i] + operation_lower_bound;
    }
}

int run_local_search (double **population, int NP, int D, double PLS, double *individuals_fitness, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    int i, number_of_evaluations_done = 0;
    int lower_bound, upper_bound, index1, index2;
    lower_bound = 0;
    upper_bound = D - 1;
    #pragma omp parallel
    {
        #pragma omp for
        for (i=0; i<NP; i++){
            if (drand48() < PLS){
                index1 = lower_bound + drand48() * (upper_bound - lower_bound);
                index2 = lower_bound + drand48() * (upper_bound - lower_bound);
                LS_evaluate_and_select (population[i], D, &individuals_fitness[i], index1, index2, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
                number_of_evaluations_done ++;
            }
        }
    }
    return number_of_evaluations_done;
}

int run_aggressive_local_search (double **population, int NP, int D, double PLS, double *individuals_fitness, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    int i, j, number_of_evaluations_done = 0;
    int lower_bound, upper_bound, index1, index2;
    bool finish_LS_for_this_individual;
    lower_bound = 0;
    upper_bound = D - 1;
    #pragma omp parallel
    {
        #pragma omp for
        for (i=0; i<NP; i++){
            if (drand48() < PLS){
                j = 0;
                finish_LS_for_this_individual = false;
                while (j<D && finish_LS_for_this_individual == false){
                    index1 = j;
                    do {
                        index2 = lower_bound + drand48() * (upper_bound - lower_bound);
                    } while (index1 == index2);
                    finish_LS_for_this_individual = LS_evaluate_and_select (population[i], D, &individuals_fitness[i], index1, index2, job_data, number_operations_per_job, number_of_machines, number_of_jobs);

                    number_of_evaluations_done ++;
                    j++;
                }
            }
        }
    }
    return number_of_evaluations_done;
}

bool LS_evaluate_and_select (double *individual, int D, double *fitness_of_individual, int index1, int index2, int **job_data, int *number_operations_per_job, int number_of_machines, int number_of_jobs) {
    double *trial_individual = init_array (D);
    double trial_fitness;
    bool is_beter_individual_find = false;

    copy_individual (individual, trial_individual, D);
    swap_double (&trial_individual[index1], &trial_individual[index2]);
    trial_fitness = DE_evaluate (trial_individual, D, job_data, number_operations_per_job, number_of_machines, number_of_jobs);
    
    if (trial_fitness <= *fitness_of_individual) {
        copy_individual (trial_individual, individual, D);
        *fitness_of_individual = trial_fitness;
        is_beter_individual_find = true;
    }
    free (trial_individual);
    return is_beter_individual_find;
}

double best_fitness_of_population (double **population, double *individuals_fitness, int NP, double *best_individual, int D) {
    double best_fitness = DBL_MAX;
    int i;
    for (i=0; i<NP; i++) {
        if (individuals_fitness[i] < best_fitness) {
            best_fitness = individuals_fitness[i];
            copy_individual (population[i], best_individual, D);
        }
    }
    return best_fitness;
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
        if (swapped == false) 
            break; 
    } 
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

double** init_matrix_with_value (int number_rows, int number_columns, double value) {
    double **matrix = init_matrix (number_rows, number_columns);
    set_all_matrix_values_to (matrix, number_rows, number_columns, value);
    return matrix;
}

double** init_matrix (int number_rows, int number_columns) {
    double **matrix = (double **) malloc (number_rows * sizeof(double*));
    int i;
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

int* init_int_array (int size) {
    int *array = (int *) malloc (size * sizeof(int));
    if (array == NULL) {
        printf ("Found problems in memory allocation");
        exit (1);
    }
    return array;
}

int convert_string_argv_to_int (char** argv, int position) {
    char *p;
    int num;
    errno = 0;
    long conv = strtol(argv[position], &p, 10);

    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || *p != '\0' || conv > INT_MAX) {
        printf ("use: ./differentialEvolution.out filename_of_FJSSP_instance NP F(*100) CR(*100) PLS(x100)");
        exit (1);
    } else {
        num = conv;    
    }
    return num;
}
