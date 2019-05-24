# Algoritmo de evolucion diferencial
DE/rand/1/bin para problema FJSSP

# Compilar
make DE

# Ejecutar
make runDE
./de_for_fjssp.out filename NP max_generations F(x100) CR(x100)

# Compilar para valgrind
make valgrind

# Ejecutar para valgrind
make runDE_valgrind

# Git
git add .
git commit -m "Nombre del commit"
git push origin master

# SSH
ssh franco@190.105.160.50 -p 2222
