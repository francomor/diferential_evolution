# Algoritmo de evolucion diferencial
DE/rand/1/bin para problema de minimizacion

# Compilar
gcc differentialEvolution.c -o differentialEvolution.out

# Ejecutar
./differentialEvolution.out D NP max_generations F(x100) CR(x100)

# Compilar para valgrind
gcc -Wall -g differentialEvolution.c -o differentialEvolution.out

# Ejecutar para valgrind
valgrind --leak-check=yes ./differentialEvolution.out D NP max_generations F(x100) CR(x100)

# Git
git add .
git commit -m "Nombre del commit"
git push origin master