#include <stdio.h>
#include <string>
#include "adn.h"
#include<iostream>


//Definicion de funciones
void printSubsequences(std::string str, int start, int end, std::string curStr = "");

int main(int argumentos, char **valores)
{
	ADN *adn1 = new ADN("AAAAA");
	ADN *adn2 = new ADN("AAAA");
	ADN *adn3 = new ADN(1024);
	std::string test = "ACCGGT";

	printf("Random sequence: %s\n", adn3->toString().c_str());

	std::string hola =  ADN::compararADN("ACCGGTCGAGTGCGCGGAAGCCGGCCGAA", "GTCGTTCGGAATGGCCGTTGCTCTGTAA");
	std::cout << "\n" << hola << std::endl;
	delete adn3;
	delete adn2;
	delete adn1;
}

//Declaracion de funciones
void printSubsequences(std::string str, int start, int end, std::string curStr)
{
	// base case
	if (start == end)
	{
		return;
	}
	// print current string permutation
	printf("%s\n", curStr.c_str());
	for (int i = start + 1; i < end; i++)
	{
		curStr += str[i];
		printSubsequences(str, i, end, curStr);
		curStr = curStr.erase(curStr.size() - 1);
	}
}