/**********************************************************************************
* util.cpp compendia funciones de uso general					     *
* Gabriela Minetti									     *
* Julio de 2012									     *
**********************************************************************************/

#ifndef INC_util
#define INC_util


#include <cstdlib>
#include <ctime>
#include <sys/time.h>

using namespace std;


// Returns a random number in [0,1].	
inline double rand01 ()
{
	return drand48();
}


int rand_int(int min, int max);


inline float _used_time()
{
	struct timeval tv ;
	static long tiempo = -1;
	float  u_clock;

	gettimeofday(&tv,NULL);

	if(tiempo < 0) tiempo = tv.tv_sec;

	u_clock = ((float)(tv.tv_sec - tiempo)*1000000.0) + ((float)tv.tv_usec);
	return u_clock;

}


inline float _used_time(float time)
{
	 float dif=_used_time() - time;
	 if (dif<0) dif = 0;	
	 return dif;	
}

#endif
