default:
	@echo "Make what? (all,  clean)"


clean:
	rm -f de_for_fjssp.out *.o *% *~
#initialSol.o Sa.o  
DE: 
	g++ -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

valgrind:
	g++ -Wall -g -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

# readCfg.o readInstance.o evaluate.o MainSa.o
#	$(CXX) $(LDFLAGS) $(LOADLIBES) $(CPPFLAGS) -o $@

all:
	make clean
	make DE

runDE:
	./de_for_fjssp.out Mk01.fjs 20 90 10

runDE_valgrind:
	valgrind --leak-check=yes ./de_for_fjssp.out Mk01.fjs 10 90 10
