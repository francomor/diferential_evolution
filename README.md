# Differential evolution algorithm with Local Search to solve the FJSSP (Flexible Job Shop Scheduling Problem)
This implements and hybrid DE NPE/rand/1/bin optimization algorithm with local search to solve the FJSSP, documented in this paper:
[Parallelism and Hybridization in Differential Evolution to solve the Flexible Job Shop Scheduling Problem](https://journal.info.unlp.edu.ar/JCST/article/view/1353)

### Directory structure
The code of the algorithm is present in the de_for_fjssp.ccp file.
In the folders you can found:

    -- base: the base DE algorithm
    -- inc: some useful functions.
    -- standard: standard code use around all the LISI group in UNLPam.

### Build
    make DE

### Run
    make runDE
    ./de_for_fjssp.out filename NP F(x100) CR(x100) PLS(x100)
Example using NP=50, F=0.5, Cr=0.9 and Pls = 0.7

	./de_for_fjssp.out "instances_Brandirmarte/Mk03.fjs" 50 50 90 70

### Build for valgrind
    make valgrind

### Run with valgrind
    make runDE_valgrind
