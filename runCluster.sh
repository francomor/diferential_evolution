#!/bin/bash
mkdir DE_4CPU_LS_05_09_07
for filename in *.fjs; do
	for (( counter=0; counter<30; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 50 90 70 >> "DE_4CPU_LS_05_09_07/$(basename "$filename")_data_4CPU_05_09_LS07.txt"
		sleep .3
	done
done