#!/bin/bash
for filename in Instancias/Barnes/*.fjs; do
	for (( counter=0; counter<5; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 90 10 70 >> "Resultados/Barnes/$(basename "$filename")_data_DE4Nucleos_LS_CR01.txt"
		sleep .3
	done
done

for filename in Instancias/Hurink/edata/*.fjs; do
	for (( counter=0; counter<5; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 90 10 70 >> "Resultados/Hurink/edata/$(basename "$filename")_data_DE4Nucleos_LS_CR01.txt"
		sleep .3
	done
done

for filename in Instancias/Hurink/rdata/*.fjs; do
	for (( counter=0; counter<5; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 90 10 70 >> "Resultados/Hurink/rdata/$(basename "$filename")_data_DE4Nucleos_LS_CR01.txt"
		sleep .3
	done
done

for filename in Instancias/Hurink/sdata/*.fjs; do
	for (( counter=0; counter<5; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 90 10 70 >> "Resultados/Hurink/sdata/$(basename "$filename")_data_DE4Nucleos_LS_CR01.txt"
		sleep .3
	done
done

for filename in Instancias/Hurink/vdata/*.fjs; do
	for (( counter=0; counter<5; counter++ ))
	do
		./de_for_fjssp.out "$filename" 50 90 10 70 >> "Resultados/Hurink/vdata/$(basename "$filename")_data_DE4Nucleos_LS_CR01.txt"
		sleep .3
	done
done

