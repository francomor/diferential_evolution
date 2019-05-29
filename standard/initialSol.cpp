/**********************************************************************************
* initialSol.cpp compendia las distintas formas de crear una solución inicial     *
* Gabriela Minetti									     *
* Julio de 2012									     *
**********************************************************************************/

#include "initialSol.h"
int Job_Op_a_Op(int J, int O ,int *N_Ope_job);

/*void initializeRandom(Solution &sj, Solution &so, Solution &sm, int J, int M, int *N_Ope_job, int Op, int **JobData) 		
{
int aux,aux2;
//creo una cola por Job y cargo las operaciones
	queue<int> c[J]; 
	for(int i=0;i<J;i++)
		for(int h=0;h< N_Ope_job[i];h++)
			c[i].push(h+1);

//cargo sj, sm y so  de forma aleatoria
	for(int i=0;i<Op;i++){
		do{
			aux=rand_int(0, J);			
		}while(c[aux].empty());
		sj[i]=aux+1;
		so[i]=c[aux].front();
		c[aux].pop();
		do{                    // esto para chequear maquina invalida, sino sacar
			aux=rand_int(0, M); // el do while y dejar esta linea sola
			aux2=  JobData [ Job_Op_a_Op( sj[i]-1, so[i]-1, N_Ope_job ) ]  [aux];
			}while(aux2>=100);
		sm[i]=aux+1;
	}	
	
}	
*/


//***********************************************************************
//  KACEM: lleva la cuenta del tiempo de operacion de cada maquina 
//         y selecciona el menor
//***********************************************************************
void initializeKacem(Solution& sol, int J, int M, int *N_Ope_job, int Op, int **JobData, int&act) 		
{
	int aux;
//creo una cola por Job y cargo las operaciones
//cout<<"inicio kacem J="<<J<<endl;	
	queue<int> c[J]; 
	for(int i=0;i<J;i++)  
		for(int h=0;h< N_Ope_job[i];h++){
			c[i].push(h+1);  
			
		}
//	cout<<"entre for de kacem\n";			
//cargo sj, sm y so  de forma aleatoria
	for(int i=0;i<Op;i++){
		do{
			aux=rand_int(0, J-1);			
		}while(c[aux].empty());
		sol.job[i]=aux+1;
		c[aux].pop();
	}
	act=1;
//	cout<<"fin kacem\n";	
	return;
}

void initializeKacem1(Solution& sol, int J, int M, int *N_Ope_job, int Op, int **JobData, int&act) 		//version sin cola--Gaby 10/5/2016
{
	int aux;
//creo una cola por Job y cargo las operaciones
//cout<<"inicio kacem J="<<J<<endl;	
	int *c = new int[J]; 
	for(int i=0;i<J;i++){
		c[i]=N_Ope_job[i];
		//cout<<"c["<<i<<"]= "<<c[i]<<endl;
		
	}

//cargo sj, sm y so  de forma aleatoria
	for(int i=0;i<Op;i++){
		do{
			aux=rand_int(0, J-1);			
		}while(c[aux]==0);
		sol.job[i]=aux+1;
		c[aux]--;
	}
	act=1;

	delete[] c;	
	return;
}

//***********************************************************************
//  MENOR: selecciona la maquina con el menor tiempo de 
//         proceso para la operacion
//***********************************************************************
/*void initializeMenor(Solution &sj, Solution &so, Solution &sm, int J, int M, int *N_Ope_job, int Op, int **JobData) 		
{
int aux,aux2,auxm;
//creo una cola por Job y cargo las operaciones
	queue<int> c[J]; 
	for(int i=0;i<J;i++)
		for(int h=0;h< N_Ope_job[i];h++)
			c[i].push(h+1);

//cargo sj, sm y so  de forma aleatoria
	for(int i=0;i<Op;i++){
		do{
			aux=rand_int(0, J);			
		}while(c[aux].empty());
		sj[i]=aux+1;
		so[i]=c[aux].front();
		c[aux].pop();
		aux=100;
		for(int m=0;m<M;m++){
			aux2=  JobData [ Job_Op_a_Op( sj[i]-1, so[i]-1, N_Ope_job ) ]  [m];
			if(aux>aux2){
				aux=aux2;
				auxm=m;
				}
		}
		sm[i]=auxm+1;
	}	
	

	return;
}
*/
//devuelve la posicion de operacion para un job y su operacion
int Job_Op_a_Op(int J, int O ,int *N_Ope_job){
	int o=0;
	for(int i=0;i<J;i++)
		o+=N_Ope_job[i];
	return o+O;
}



