/**********************************************************************************
* initialSol.cpp compendia las funciones de evaluación de soluciones		     *
* para distintos problemas    							     *
* Gabriela Minetti									     *
* Diciembre de 2012									     *
**********************************************************************************/
#ifndef SA_evaluate
#define SA_evaluate


#include <iostream>
#include "userTypeDef.h"
#include <math.h>
#include "initialSol.h"

using namespace std;
//LAS FUNCIONES DE MINIMIZACIÓN DEVUELVEN 1/COSTO
//LAS FUNCIONES DE MAXIMIZACIÓN DEVUELVEN EL COSTO 
//double evaluate(int *Sjobs, int *Soperaciones, double &costo, int M, int J,int Op, int * N_Ope_job, int ** JobData);  
double evaluate(Solution& sol, double &costo, int M, int J,int Op, int * N_Ope_job, int ** JobData, int &act);  
#endif
