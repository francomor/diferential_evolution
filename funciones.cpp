#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "funciones.h"
#include "abejas.h"

using namespace std;

/*---------------------------Funcion Fitness--------------------------*/
double evaluar_fitness (Sol &lista,  int funcion)
{
	
	switch ( funcion )
	{
        /*----------Funcion Esfera-----------*/
		case 1:
		{	
			double a = 0.0; 
			int dimf;
			dimf = dimension(funcion);
			for(int i=0; i< dimf; i++){
				a+= pow(lista[i],2); 
			}
			return a;
		}
		break;
		
		/*----------Funcion Rosenbrock-----------*/
        case 2:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double a = 0.0;
			double x1;
			double x2;
			
			double diff_x1;
			
			for(int i=0; i<dimf-1; i++){
				x1=lista[i];
				x2=lista[i+1];
				diff_x1=x1-1.0;
				a=a+(100.0*((x2-x1*x1)*(x2-x1*x1)))+(diff_x1*diff_x1);
			}
			
			return a;

		}
		break; 
		
		/*----------Funcion ACKLEY-----------*/
        case 3:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double term1;
			double sum1=0.0;
			double term2;
			double sum2=0.0;
			
			double a = 0.0;
			
			for(int i=0;i<dimf;i++){
				sum1+=pow(lista[i],2.0);
			} 
	
			for(int i=0;i<dimf;i++){
				sum2+=cos(2*3.141592*lista[i]);
			}
	
			term1= (-1)*20*exp((-1)*0.2*sqrt((1/(double)dimf)*sum1));
			term2=exp((1/(double)dimf)*sum2);
			
			a = term1-term2+20+2.718281;
	
			return a;
		
		}
		break;
		
		/*----------Funcion Schwefel1.2-----------*/
        case 4:
		{
			int dimf;
			dimf = dimension(funcion);
		
			double a = 0.0, b=0.0;

			for(int i=0;i<dimf;i++) {
				for(int j=0;j<i;j++) {
					a+=lista[i];
				}
				b+=a*a;
			}

			return b;
		
		}
		break;
		
		/*----------Funcion Schaffer2-----------*/
        case 5:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double x1, x2;		
			double a = 0.0, fact1=0.0, fact2=0.0;
			
			for(int i=0;i<dimf;i++) {
				x1=lista[i];
				x2=lista[i+1];
				fact1 = (sin(x1*x1-x2*x2))*(sin(x1*x1-x2*x2)) - 0.5;
				fact2 = (1 + 0.001*(x1*x1+x2*x2))*(1 + 0.001*(x1*x1+x2*x2));
				a = 0.5 + fact1/fact2;
			}

			return a;
		
		}
		break;
		
		/*----------Funcion Booth-----------*/
        case 6:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double x1, x2;		
			double a = 0.0, term1=0.0, term2=0.0;
			

				x1=lista[0];
				x2=lista[1];
				term1 = (x1 + 2*x2 - 7);
				term2 = (2*x1 + x2 - 5);
				a = term1*term1 + term2*term2;

			return a;
		
		}
		break; 
		
		/*----------Funcion Matyas-----------*/
        case 7:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double x1, x2;		
			double a = 0.0, term1=0.0, term2=0.0;
			
			x1=lista[0];
			x2=lista[1];
			term1 = 0.26 * (x1*x1 + x2*x2);
			term2 = -0.48*x1*x2;
			a = term1 + term2;
		
			return a;
		
		}
		break; 
		
		/*----------Funcion Beale-----------*/
        case 8:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double x1, x2;		
			double a = 0.0, term1=0.0, term2=0.0, term3=0.0;
			
				x1=lista[0];
				x2=lista[1];
				term1 = (1.5 - x1 + x1*x2)*(1.5 - x1 + x1*x2);
				term2 = (2.25 - x1 + x1*(x2*x2))*(2.25 - x1 + x1*(x2*x2));
				term3 = (2.625 - x1 + x1*(x2*x2*x2))*(2.625 - x1 + x1*(x2*x2*x2));
				a = term1 + term2 + term3;
  
			return a;
		
		}
		break; 
		
		/*----------Funcion Sumpow-----------*/
        case 9:
		{
			int dimf;
			dimf = dimension(funcion);
			
			double a = 0.0;
			
			for(int i=0;i<dimf;i++) {
				a += pow((fabs(lista[i])),i+2);
			}
  
			return a;
		
		}
		break; 
		
		/*----------Funcion Branin-----------*/
        case 10:
		{
			int dimf;
			dimf = dimension(funcion);
			double pi=3.14159265358979323846;
			double x1, x2;
			double resultado = 0.0, aux = 0.0;
			int a=1, r=6, s=10;
			double t=1/(8*pi), b=5.1/(4*pi*pi), c=5/pi;
			double term1=0.0, term2=0.0;

			x1=lista[0];
			x2=lista[1];
			aux=(x2 - b*x1*x1 + c*x1 - r);
			term1 = a *aux*aux;
			term2 = s*(1-t)*cos(x1);
			resultado = term1 + term2 + s ;
 
			return resultado;	
		}
		break; 
		
        default:
			printf("Error");	
      
	  }

		

}

/*----------------------Funcion de Inicializacion---------------------------*/
void inicializacion (Sol &lista, int funcion)
{
	int dimf;
	switch ( funcion )
	{
		/*----------Funcion Esfera-----------*/
		case 1:  
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-100,100);
			}
		}	
		break;
        
		/*----------Funcion Rosenbrock-----------*/
		case 2:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-30,30);
			}
		}
		break; 
		
		/*----------Funcion ACKLEY-----------*/
		case 3:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-32.768,32.768);
			}
		}
		break; 
		
		/*----------Funcion Schwefel1.2-----------*/
		case 4:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-100,100);
			}
		}
		break; 
		
		/*----------Funcion Schaffer2-----------*/
		case 5:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-100,100);
			}
		}
		break; 
		
		/*----------Funcion Booth-----------*/
		case 6:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-10,10);
			}
		}
		break; 
		
		/*----------Funcion Matyas-----------*/
		case 7:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-10,10);
			}
		}
		break;

		/*----------Funcion Beale-----------*/
		case 8:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-4.5,4.5);
				}
		}
		break; 
		
		/*----------Funcion Sumpow-----------*/
		case 9:
		{	
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++){
				lista[i] = Random_Real(-1,1);
			}
		}
		break; 
		
		/*----------Funcion Branin-----------*/
		case 10:
		{
			lista[0] = Random_Real(-5,10);
			lista[1] = Random_Real(0,15);
		}
		break; 
		
        default:
			printf("Error");
		break;
    }		

}

/*----------------------------Funcion dimension---------------------------*/
int dimension (int funcion){
	switch ( funcion )
	{
        /*----------Funcion Esfera-----------*/
		case 1:  
         	return 30;
		break;
        
		/*----------Funcion Rosenbrock-----------*/
		case 2:
			return 30;
		break; 
		
		/*----------Funcion ACKLEY-----------*/
		case 3:
			return 30;
		break; 
		
		/*----------Funcion Schwefel1.2-----------*/
		case 4:
			return 30;
		break; 
		
		/*----------Funcion Schaffer2-----------*/
		case 5:
			return 30;
		break; 
		
		/*----------Funcion Booth-----------*/
		case 6:
			return 2;
		break; 
		
		/*----------Funcion Matyas-----------*/
		case 7:
			return 2;
		break; 
		
		/*----------Funcion Beale-----------*/
		case 8:
			return 2;
		break; 
		/*----------Funcion Sumpow-----------*/
		case 9:
			return 20;
		break; 
		
		/*----------Funcion Branin-----------*/
		case 10:
			return 2;
		break; 
		
        default:
			printf("Error");
		break;
      }		
	
}

/*-----------------------------Funcion controlar limite-------------------------*/
void controlar_limite (Sol &lista, int funcion){
	
	switch ( funcion )
	{
        /*----------Funcion Esfera-----------*/
		case 1:  
        { 		int dimf;
				dimf = dimension(funcion);
				
				for(int i=0; i< dimf; i++)
				{
					if(lista[i]<-100.0)
					{
						lista[i] = -100.0;	
					}else{
						if(lista[i]>100.0){
							lista[i] = 100.0;
						}
					}
				}
		}
		break;
        
		/*----------Funcion Rosenbrock-----------*/
		case 2:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-30.0)
				{
					lista[i] = -30.0;	
				}else{
					if(lista[i]>30.0){
						lista[i] = 30.0;
					}
				}
			}
		}
		break; 
		
		/*----------Funcion ACKLEY-----------*/
		case 3:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-32.768)
				{
					lista[i] = -32.768;	
				}else{
					if(lista[i]>32.768){
						lista[i] = 32.768;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Schwefel1.2-----------*/
		case 4:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-100.0)
				{
					lista[i] = -100.0;	
				}else{
					if(lista[i]>100.0){
						lista[i] = 100.0;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Schaffer2-----------*/
		case 5:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-100.0)
				{
					lista[i] = -100.0;	
				}else{
					if(lista[i]>100.0){
						lista[i] = 100.0;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Booth-----------*/
		case 6:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-10.0)
				{
					lista[i] = -10.0;	
				}else{
					if(lista[i]>10.0){
						lista[i] = 10.0;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Matyas-----------*/
		case 7:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-10.0)
				{
					lista[i] = -10.0;	
				}else{
					if(lista[i]>10.0){
						lista[i] = 10.0;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Beale-----------*/
		case 8:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-4.5)
				{
					lista[i] = -4.5;	
				}else{
					if(lista[i]>4.5){
						lista[i] = 4.5;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Sumpow-----------*/
		case 9:
		{
			int dimf;
			dimf = dimension(funcion);
			
			for(int i=0; i< dimf; i++)
			{
				if(lista[i]<-1.0)
				{
					lista[i] = -1.0;	
				}else{
					if(lista[i]>1.0){
						lista[i] = 1.0;
					}
				}
			}
		}
		break;
		
		/*----------Funcion Branin-----------*/
		case 10:
		{
			int dimf;
			dimf = dimension(funcion);
			
			if(lista[0]<-5.0)
			{
				lista[0] = -5.0;	
			}else{
				if(lista[0]>10.0){
					lista[0] = 10.0;
				}
			}
		
			if(lista[1]<0.0)
			{
				lista[1] = 0.0;	
			}else{
				if(lista[1]>15.0){
					lista[1] = 15.0;
				}
			}

		}
		break;
		
        default:
			printf("Error");
		break;
    }		
	
}

/*------------------------Funcion de maximizacion o minimazacion--------------------------*/
// min = 0 o max = 1 //
int max_min (int funcion)
{
	switch ( funcion )
	{
		case 1:  
         	return 0;
		break;
        case 2:
			return 0;
		break;
		case 3:
			return 0;
		break;
		case 4:
			return 0;	
        break;
		case 5:
			return 0;	
        break;
		case 6:
			return 0;	
        break;
		case 7:
			return 0;	
        break;
		case 8:
			return 0;	
        break;
		case 9:
			return 0;	
        break;
		case 10:
			return 0;	
        break;
		
		default:
			printf("Error");
		break;
    }	

}

/*--------------------------Funcion para calcular el tiempo---------------------------*/
double tiempo(time_t inicial){
    time_t final;
    time(&final);
    return difftime(final, inicial);

}

/*----------------------------Funcion random entero------------------------------------*/
int Random_Entero(int min, int max)
{
	double r = (double)rand()/double(RAND_MAX);
	
	r = r*(max-min) + min;

	return (int) r;

}

/*-------------------------------Funcion random real------------------------------------*/
double Random_Real(double min, double max)
{
	double r = (double)rand()/double(RAND_MAX);
	
	r = r*(max-min) + min;

	return r;

}

