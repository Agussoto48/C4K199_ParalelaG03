#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <omp.h>
#include "adn.h"

enum Letras
{
    LETRA_G = 0,
    LETRA_T = 1,
    LETRA_C = 2,
    LETRA_A = 3
};

ADN::ADN(int length)
{
    int posicion;
    char base = 'A';

    this->sequence = std::string("");
    for (posicion = 0; posicion < length; posicion++)
    {
        switch (rng(0, 4))
        {
        case LETRA_G:
            base = 'G';
            break;
        case LETRA_T:
            base = 'T';
            break;
        case LETRA_C:
            base = 'C';
            break;
        case LETRA_A:
            base = 'A';
            break;
        }
        this->sequence.push_back(base);
    }
}

/**
 * Constructor con parametros
 * @param	char	un string con los compenentes del ADN
 *
 **/
ADN::ADN(std::string palabra)
{
    this->sequence = std::string("");
    for (size_t posicion = 0; posicion < palabra.size(); posicion++)
    {
        this->sequence.push_back(palabra[posicion]);    
    }
}

ADN::~ADN()
{
}

std::string ADN::toString()
{
    return this->sequence;
}

void ADN::printSeqs()
{
    printSeqs(this->sequence, -1, this->sequence.size());
}

void ADN::printSeqs(std::string str, int start, int end, std::string curStr)
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
        printSeqs(str, i, end, curStr);
        curStr = curStr.erase(curStr.size() - 1);
    }
}
int ADN::rng(int min, int max)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}

int encontrar_palindromo(const std::string &s, int left, int right)
{
    int L = left, R = right;
    while (L >= 0 && R < (int)s.size() && std::tolower(s[L]) == std::tolower(s[R]))
    {
        L--;
        R++;
    }
    return R - L - 1;
}
std::string ADN::Palindromo()
{
    std::string text = this->getSequence();

    int n = text.size();
    int len_maximo = 0;
    int posicion_inicial = 0;

    #pragma omp parallel
    {
        int maximo_local = 0;
        int inicio_local = 0;

        #pragma omp for nowait
        for (int i = 0; i < n; i++)
        {

            // Palíndromos impares, por ejemplo, oso
            int len1 = encontrar_palindromo(text, i, i);

            // Palíndromos pares, por ejemplo, lool
            int len2 = encontrar_palindromo(text, i, i + 1);

            int len = std::max(len1, len2);

            
            int posible_inicio_local = i - (len - 1) / 2;

            if (len > maximo_local)
            {
                maximo_local = len;
                inicio_local = posible_inicio_local;
            }
        }
        //Zona critica, comprobar con el maximo general
        #pragma omp critical
        {
            if (maximo_local > len_maximo)
            {
                len_maximo = maximo_local;
                posicion_inicial = inicio_local;
            }
        }
    }

    std::string palindromo_mas_largo = text.substr(posicion_inicial, len_maximo);

    return palindromo_mas_largo;
}
