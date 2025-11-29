#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <mpi.h>

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

   // Busca las letras comunes en ambos strings
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
std::string ADN::compararADN(const std::string &A, const std::string &B)
{
   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   std::string mejorGlobal = "";
   std::string mejorLocal = "";

   //Un hilo
   if (size == 1)
   {
      std::string mejor;
      explorar(A, B, 0, 0, "", mejor);
      return mejor;
   }
   //Varios hilos
   //El primero define los puntos de partida
   if (rank == 0)
   {
      std::set<char> comunes;
      for (char c1 : A)
         for (char c2 : B)
            if (c1 == c2)
               comunes.insert(c1);

      std::vector<char> ramas(comunes.begin(), comunes.end());

      int worker = 1;
      for (char c : ramas)
      {
         if (worker >= size)
            break;
         MPI_Send(&c, 1, MPI_CHAR, worker, 0, MPI_COMM_WORLD);
         worker++;
      }

      char fin = '#';
      for (; worker < size; worker++)
         MPI_Send(&fin, 1, MPI_CHAR, worker, 0, MPI_COMM_WORLD);

      for (int p = 1; p < size; p++)
      {
         int len = 0;
         MPI_Recv(&len, 1, MPI_INT, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

         if (len == 0)
            continue;

         std::vector<char> buf(len);
         MPI_Recv(buf.data(), len, MPI_CHAR, p, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

         std::string recibido(buf.begin(), buf.end());
         if (recibido.size() > mejorGlobal.size())
            mejorGlobal = recibido;
      }

      return mejorGlobal;
   }
   //Ya los demas empiezan a partir de ese punto a buscar el string
   else
   {
      char letra;
      MPI_Recv(&letra, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      if (letra == '#')
      {
         int zero = 0;
         MPI_Send(&zero, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
         return "";
      }
      size_t pos1 = 0, pos2 = 0;

      while (pos1 < A.size() && A[pos1] != letra)
         pos1++;
      while (pos2 < B.size() && B[pos2] != letra)
         pos2++;

      if (pos1 == A.size() || pos2 == B.size())
      {
         int zero = 0;
         MPI_Send(&zero, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
         return "";
      }

      // Explorar la rama correspondiente
      explorar(A, B, pos1 + 1, pos2 + 1, std::string(1, letra), mejorLocal);

      // Enviar resultado al master
      int len = mejorLocal.size();
      MPI_Send(&len, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

      if (len > 0)
         MPI_Send(mejorLocal.c_str(), len, MPI_CHAR, 0, 2, MPI_COMM_WORLD);

      return mejorLocal;
   }
}