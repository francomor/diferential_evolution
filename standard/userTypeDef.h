/*********************************************************************************
* userTypeDef.h compendia definiciones de tipos y variables globales	     *
* 									     *
* 								     *
**********************************************************************************/

#ifndef SA_userTypeDef
#define SA_userTypeDef

struct Solution{
	int *op;
	int *job;
};

struct individual{  //al individuo en ICA se lo denomina country
 Solution sol;
 double fitness;
 //int id, idImp;   //si id=-1 entonces el pa�s fue eliminado. Si id=idImp significa que el country id es imperialista, si idImp=-2 todav�a no tiene imperio asignado
 int act;//Fitness = 0-actualizado 1-noActualizado
}; 
//int N;	//tama�o de una soluci�n

struct EvaluationRequeriment{
	int *operacion;
	int *job;
	int *maquina;
};

#endif


