/**********************************************************************************
* initialSol.cpp compendia las distintas formas de crear una solución inicial     *
* Gabriela Minetti									     *
* Julio de 2012									     *
**********************************************************************************/
#ifndef SA_initialSol
#define SA_initialSol


#include <iostream>
#include <queue>
#include <stdlib.h>
#include "../inc/util.hh"
#include "userTypeDef.h"
#include "evaluate.h"

using namespace std;
int Job_Op_a_Op(int J, int O ,int *N_Ope_job);
//void initializeRandom(Solution &sj, Solution &so,Solution &sm, int J, int M, int * N_Ope_job, int Op, int **JobData); 		// genera aleatoriamente una permutación
void initializeKacem(Solution& sol, int J, int M, int *N_Ope_job, int Op, int **JobData, int&act); 		
void initializeKacem1(Solution& sol, int J, int M, int *N_Ope_job, int Op, int **JobData, int&act); 		//version sin cola--Gaby 10/5/2016
//void initializeMenor(Solution &sj, Solution &so, Solution &sm, int J, int M, int *N_Ope_job, int Op, int **JobData); 	
//void Reordena(Solution &sj, Solution &so, Solution &sm, int M, int J, int Op, int *N_Ope_job, int **JobData) 		; 			
#endif

