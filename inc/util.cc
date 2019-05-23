/**********************************************************************************
* util.cpp compendia funciones de uso general					     *
* Gabriela Minetti									     *
* Julio de 2012									     *
**********************************************************************************/
#include "util.hh"

int rand_int(int min, int max)
{
	double r = (double)rand()/double(RAND_MAX);
	
	r = r*(max-min) + min;

	return (int) r;
}



