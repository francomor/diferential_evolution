/*********************************************************************************
* evalueate.cpp compendia las funciones de evaluación de soluciones		     *
* para distintos problemas    							     *
* Gabriela Minetti - Carolina Salto									     *
* Mayo de 2014									     *
**********************************************************************************/
#include <stdlib.h>
#include "evaluate.h"

//LAS FUNCIONES DE MINIMIZACIÓN DEVUELVEN 1/COSTO
//LAS FUNCIONES DE MAXIMIZACIÓN DEVUELVEN EL COSTO
extern long int total_eval;
double evaluate(Solution& sol, double &costo, int M, int J,int Op, int * N_Ope_job, int **JobData, int &act)  
{ 
	int tiempojob[J];for(int t=0;t<J;++t)tiempojob[t]=0;
	int tiempomaq[M];for(int t=0;t<M;t++)tiempomaq[t]=0;
		
	if(act==0) return costo;

	int tiempo, m=0;
	int *Sm =new int[Op];  //HABILITAR PARA LA OTRA FORMA DE EVALUACION
	act=0;
	
	int *ctajob=new int[J]; for(int i=0;i<J;i++)ctajob[i]=1; //lleva la cuenta de la operacion para cada job 
	for(int i=0;i<Op;i++) //armo vector operaciones
		sol.op[i]=ctajob[sol.job[i]-1]++;
	//cout<<"despues de ctajob en evaluate\n sol.job \n";	
/*	for(int i=0;i<Op;i++) //armo vector operaciones
		cout<<sol.job[i]<<" ";
	cout<<"\nsol.op\n";
	for(int i=0;i<Op;i++) //armo vector operaciones
		cout<<sol.op[i]<<" ";
	cout<<endl;
	*/
	//AGREGADO POR CAROLINA 06/05 codigo Reordena2
	int parcial,total,aux2,auxm;
	
	int *maq = new int[M];for (int i=0;i<M;i++)maq[i]=0; //lleva la cuenta del tiempo en cada maquina
	int *tpojob=new int[J];for(int t=0;t<J;++t)tpojob[t]=0;
	
	//cout<<"despues de crear memor con maq y job en evaluate\n";
	//cout<<"Op: "<<Op<<" M: "<<M<<" J: "<<J<<endl;
	
	for(int i=0;i<Op;i++){
		total=1000;  
		for(m=0;m<M;m++){
	//		cout<<"--------i: "<<i<<"   m: "<<m<<endl;
			int fila=Job_Op_a_Op( sol.job[i]-1, sol.op[i]-1, N_Ope_job );
			aux2=  JobData [ fila ]  [m];
	//		cout<<"--------aux2: "<<aux2<<endl;
			if(aux2<100 ){
				if ( tpojob[sol.job[i]-1] > maq[m])
					parcial = aux2 + tpojob[sol.job[i]-1];			
				else
					parcial = aux2 + maq[m];
	//			cout<<"-------parcial: "<<parcial<<endl;
				if(parcial<total){
					total=parcial;
					auxm=m;					
				}
			}
		}
		
	//	cout<<"--------total "<<total<<" auxm "<<auxm<<endl;
		maq[auxm]=total; //le quite el +=
		Sm[i]=auxm+1;
		tpojob[sol.job[i]-1]=total;//le quite el +=
	//	cout<<"--------maq[auxm]: "<<maq[auxm]<<" tpojob: "<<tpojob[sol.job[i]-1]<<endl;
	}	
	//cout<<"********************maq[auxm]: "<<maq[auxm]<<endl;
	m=0;
	for(int t=0;t<J;t++)
		if(tpojob[t]>= m) m=tpojob[t];	
	//	cout<<"evalua de reordena2 "<<m<<endl;
	//cout<<"despues de reordena2 en evaluate\n";	
/*COMENTADO POR CAROLINA 06/05	
	***********************************FALTA REORDENA2 PARA SM
*/	
//	cout <<endl<<"--EVALUATE---"<<endl;
	for(int t=0;t<Op;t++){
//		cout << endl <<i<<": "<< Sj[i]<<", "<<So[i]<<" m->"<<Sm[i]<<" tiempo->"<<  JobData [ Job_Op_a_Op( Sj[i]-1, So[i]-1, N_Ope_job ) ]  [Sm[i]-1]   <<endl;
		int fila=Job_Op_a_Op( sol.job[t]-1, sol.op[t]-1, N_Ope_job );
		tiempo=JobData [ fila ]  [Sm[t]-1];

		if ( tiempojob[sol.job[t]-1] > tiempomaq[Sm[t]-1])
			tiempo+=tiempojob[sol.job[t]-1];			
		else
			tiempo+=tiempomaq[Sm[t]-1];
		tiempojob[sol.job[t]-1]=tiempo;
		tiempomaq[Sm[t]-1]=tiempo;
	}
	for(int t=0;t<J;t++)
		if(tiempojob[t]>= m) m=tiempojob[t];
	
	delete[] Sm ;

	//FIX USO DE MEMORIA FRANCO MORERO
	delete[] maq;
	delete[] ctajob;
	delete[] tpojob;

	//cout<<"evalua original "<<m<<endl;
	total_eval++;
	return m;
}

