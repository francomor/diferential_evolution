#!/bin/bash
for (( counter=0; counter<30; counter++ ))
do
	./differentialEvolution.out $1 $2 $3 $4 $5 >> de_out.txt
	sleep .3
done