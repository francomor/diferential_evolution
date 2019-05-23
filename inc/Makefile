#include ../environment

OBJS = util.o

all: $(OBJS)

util.o: util.cc util.hh
	$(CXX) $(CPPFLAGS) util.cc -c

clean:
	rm -f *.o *~ *% 
