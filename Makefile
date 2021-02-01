default:
	@echo "Make what? (all,  clean, DE, valgrind). Or run? (runDE, runDE_valgrind)"


clean:
	rm -f de_for_fjssp.out *.o *% *~

DE: 
	g++ -std=c++11 -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

valgrind:
	g++ -std=c++11 -Wall -g -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

all:
	make clean
	make DE

runDE:
	./de_for_fjssp.out "instances_Brandirmarte/Mk01.fjs" 50 50 90 0

runDE_valgrind:
	valgrind --leak-check=yes ./de_for_fjssp.out "instances_Brandirmarte/Mk01.fjs" 50 90 10 0
