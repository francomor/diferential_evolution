default:
	@echo "Make what? (all,  clean)"


clean:
	rm -f de_for_fjssp.out *.o *% *~
	
DE: 
	g++ -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

valgrind:
	g++ -Wall -g -I /inc -I /standard -lm -o de_for_fjssp.out standard/readInstance.cpp standard/evaluate.cpp inc/util.cc standard/initialSol.cpp de_for_fjssp.cpp -fopenmp

all:
	make clean
	make DE

runDE:
	./de_for_fjssp.out mt10cc.fjs 50 90 10 70

runDE_valgrind:
	valgrind --leak-check=yes ./de_for_fjssp.out Mk01.fjs 50 90 10 50
