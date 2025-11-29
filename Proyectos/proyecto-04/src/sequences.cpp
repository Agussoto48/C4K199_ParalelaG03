#include <stdio.h>
#include <string>
#include "adn.h"
#include <mpi.h>
#include <iostream>

int main(int argumentos, char **valores)
{
	MPI_Init(&argumentos, &valores);

	ADN *adn1 = new ADN("ACCGGTCGAGTGCGCGGAAGCCGGCCGAA");
	ADN *adn2 = new ADN("GTCGTTCGGAATGGCCGTTGCTCTGTAA");
	ADN *adn3 = new ADN(100);
	ADN *adn4 = new ADN(100);
	double inicio, fin;

	inicio = MPI_Wtime();
	std::string mejor_definido = ADN::compararADN(adn1->getSequence(), adn2->getSequence());
	fin = MPI_Wtime();

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		std::cout << "\nEl resultado de las cadenas fue:\n";
		std::cout << "\nLa cadena en comun más larga fue: " << mejor_definido << std::endl;
		std::cout << "Con un tamaño de: " << mejor_definido.size() << std::endl;

		 std::cout << "Tiempo: " << (fin - inicio) << " segundos\n";
	}

	delete adn4;
	delete adn3;
	delete adn2;
	delete adn1;

	MPI_Finalize();
	return 0;
}