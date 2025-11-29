#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

#include "adn.h"

enum Letras
{
   LETRA_G = 0,
   LETRA_T = 1,
   LETRA_C = 2,
   LETRA_A = 3
};

/**
 * Constructor por defecto
 * Crea una secuencia random de 100 carácteres compuestas por las letras "G",'T','C' y 'A'
 *
 **/
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
ADN::ADN(const char *string)
{
   this->sequence = std::string("");
   for (size_t posicion = 0; posicion < strlen(string); posicion++)
   {
      switch (string[posicion])
      {
      case 'A':
      case 'C':
      case 'G':
      case 'T':
         this->sequence.push_back(string[posicion]);
         break;
      default:
         this->sequence.push_back('A');
         break;
      }
   }
}

/**
 * Destructor de la clase
 **/
ADN::~ADN()
{
}

/**
 * Return a String with sequence
 **/
std::string ADN::toString()
{
   return this->sequence;
}

/**
 *
 **/
void ADN::printSeqs()
{
   printSeqs(this->sequence, -1, this->sequence.size());
}

/**
 *
 **/
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

void explorar(const std::string &S1, const std::string &S2, size_t inicio_1, size_t inicio_2, std::string actual, std::string &mejor)
{
   if (inicio_1 >= S1.size() || inicio_2 >= S2.size())
   {
      if (actual.size() > mejor.size())
         mejor = actual;
      return;
   }

   //Busca las letras comunes en ambos strings
   std::set<char> comunes;
   for (size_t a = inicio_1; a < S1.size(); a++)
      for (size_t b = inicio_2; b < S2.size(); b++)
         if (S1[a] == S2[b])
            comunes.insert(S1[a]);

   if (comunes.empty())
   {
      if (actual.size() > mejor.size())
         mejor = actual;
      return;
   }

   for (char c : comunes)
   {
      size_t match_en_1 = inicio_1;
      while (match_en_1 < S1.size() && S1[match_en_1] != c)
         match_en_1++;
      if (match_en_1 == S1.size())
         continue;

      size_t match_en_2 = inicio_2;
      while (match_en_2 < S2.size() && S2[match_en_2] != c)
         match_en_2++;
      if (match_en_2 == S2.size())
         continue;

      explorar(S1, S2, match_en_1 + 1, match_en_2 + 1, actual + c, mejor);
   }
}
std::string ADN::compararADN(const std::string &string_1, const std::string &string_2)
{
   std::string mejor = "";
   std::string actual = "";
   size_t inicio_1 = 0, inicio_2 = 0;
   explorar(string_1, string_2, inicio_1, inicio_2, actual, mejor);
   return mejor;
}