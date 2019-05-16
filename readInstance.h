/**********************************************************************************
* readInstance.h compendia las funciones para leer instancias		     *
* correspondientes a distintos problemas    					     *
* Carolina Salto - Gabriela Minetti									     *
* Mayo de 2014								     *
**********************************************************************************/

#ifndef SA_readInstance
#define SA_readInstance


#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
int readInstanceFJJ(char * filename, int *** JobData, int *M, int *J, int ** N_Ope_job, int *** op_to_JobOp, int *Op);
//	N_Ope_job   = numero operaciones por job
//	JobData     = matriz con los datos de las maquinas permitidas por operacion y los tiempos
//	op_to_JobOp = matriz con: filas = numero de operacion; 1ºcolumna = numero de job; 2ºcolumna = numero de operacion para el job
//	op 			= cantidad de operacion
//	J 			= cantidad de job
//	M 			= cantida de maquinas
#endif
