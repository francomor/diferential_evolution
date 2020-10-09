# Diferential evolution algorithm to solve the FJSSP (Flexible Job Shop Scheduling Problem)
This is a DE/rand/1/bin algoritm to solve the FJSSP, documented in this paper:
[Parallelism and Hybridization in Differential Evolution to solve the Flexible Job Shop Scheduling Problem](https://journal.info.unlp.edu.ar/JCST/article/view/1353)

### Directory structure
The code of the algorithm is present on de_for_fjssp.ccp file.
In the folders you can found:

    -- base: the DE base algortihm
    -- inc: some usefull funtions.
    -- standard: standard code use around all the LISI group in UNLPam.

### Build
    make DE

### Run
    make runDE
    ./de_for_fjssp.out filename NP F(x100) CR(x100) PLS(x100)

### Build for valgrind
    make valgrind

### Run with valgrind
    make runDE_valgrind
