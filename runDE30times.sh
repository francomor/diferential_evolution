#!/bin/bash
for (( counter=0; counter<30; counter++ ))
do
	./de_for_fjssp.out $1 $2 $3 $4 $5 >> salida.txt
	sleep .3
done
