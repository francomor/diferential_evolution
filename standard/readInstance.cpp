/**********************************************************************************
* readInstance.h compendia las funciones para leer instancias		     *
* correspondientes a distintos problemas    					     *
* Carolina Salto - Gabriela Minetti									     *
* Mayo de 2014								     *
**********************************************************************************/
#include "readInstance.h"
#include "stdlib.h"
//extern int LB, UB;

//op cantidad de operacion
//J cantidad de job
//M cantida de maquinas

int readInstanceFJJ(char * filename, int *** JobData, int *M, int *J, int ** N_Ope_job, int *** op_to_JobOp,int *Op)
{
	float auxN;

	ifstream file(filename);

	if(!file){ 
		cout<<"Instance File not found"<<filename<<endl;
		return 0;
	}
	file >> *J;   //Numero de Jobs
	file >> *M;   //Numero de Maquinas 
	file >> auxN; //al pedo para el promedio
	//cout<<"Jobs: "<<*J<<endl;
	//cout<<"Maquinas: "<<*M<<endl;
// carga el numero de operacione por job en el vector N_Ope_job y el resto de la linea en la matriz x
	char **x = new char*[*J];	
	*N_Ope_job = new int[*J];
	for(unsigned int i = 0; i < *J; ++i){ 
		file >> (*N_Ope_job)[i];
		*Op += (*N_Ope_job)[i];
		x[i]= new char [300];   //300
		file.getline(x[i],300);  //300
		//cout<<"(*N_Ope_job)[i] "<<(*N_Ope_job)[i]<<" *Op "<<*Op<<endl;
		}

	//lleno op_to_JobOp	
	*op_to_JobOp=new int*[*Op];
	for (int i=0; i<*Op;i++)(*op_to_JobOp)[i]=new int[2];
	//cout<<" *Op "<<*Op<<endl;
	int posx=0;
	//(*op_to_JobOp)[
	for(unsigned int i = 0; i < *J; ++i)
		for(unsigned int h = 0; h < (*N_Ope_job)[i]; ++h){	
					(*op_to_JobOp)[posx][0]=i+1;
					(*op_to_JobOp)[posx][1]=h+1;
					posx++;
		}			 
//------------------------------------------------------	
//cout<<" (*N_Ope_job)[J-1] "<<(*N_Ope_job)[*J-1]<<endl;

// creo y lleno  la  matriz JobData con 100 para setearla como no disponible
	*JobData=new int*[*Op];
	for (unsigned int i=0;i<*Op;++i){
		(*JobData)[i]=new int[*M];
		for(int j=0;j<*M;++j)(*JobData)[i][j]=100;
	}
//--------------------------
//cout<<"despues crear jobdata\n";
// parseo las lineas x y cargo la matriz JobData
	char *a; 
	int maq,tiempo,pos=0,cant_operaciones=0,nummaq;
	for (unsigned int job=0; job<*J; ++job){
		cant_operaciones=(*N_Ope_job)[job];
	//	cout<<"(*N_Ope_job)[job] "<<(*N_Ope_job)[job]<<endl;
		a=strtok(x[job]," ");
//		cout<<"job "<<a<<endl;
		for(int operacion=0; operacion<cant_operaciones; operacion++){
			nummaq=atoi(a);
			for (int maquinas=0; maquinas<nummaq; maquinas++){
//				cout<<"maquinas "<<maquinas<<" operacion "<<operacion;
				a=strtok(NULL," ");
				maq=atoi(a);
//				cout<<" maq "<<maq;
				a=strtok(NULL," ");  //el problema está en este strtok que le carga a la variable a un 7 seguidos de espacios y un 2
//				cout<<" a "<<a;
				tiempo=atoi(a);
//				cout<<" tpo "<<tiempo<<endl;
	//			cout<<" (*JobData)[pos][maq-1] "<<(*JobData)[pos][maq-1]<<endl;
				(*JobData)[pos][maq-1]=tiempo;
				
			}
			pos++;
			a=strtok(NULL," ");
		}
	}
//----------------------------------------------
//cout<<"despues parseo\n";

// //imprimo JobData-------------
// 	cout<<"Jobs: "<<*J<<endl;
// 	cout<<"Maquinas: "<<*M<<endl;
// 	cout << "Operacione: "<<*Op <<endl;
// 	cout << "J, O ";for(int i=0;i<*M;i++)cout << "\tM"<<i+1;
// 	for(int i=0;i<*Op;++i){
// 		cout <<endl<<(*op_to_JobOp)[i][0]<<", "<<(*op_to_JobOp)[i][1]<<":\t" ;
// 		for(int j=0;j<*M;++j)
// 			cout << (*JobData)[i][j]<< "\t";
// 	}
// 	cout <<endl;
// //----------------------------

	delete[] x;
	a = NULL;
	return 1;
}
