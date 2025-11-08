#include <math.h>
#include <cassert>
#include "VectorPuntos.h"
/**
 *   @brief Genera numeros random en punto flotante
 **/
double randf(double base)
{

   return base * rand() / (RAND_MAX - 1.);
}
/**
 *   @brief Rellena el vector de puntos con puntos definidos en un circulo
 **/
VectorPuntos::VectorPuntos(long cantidad, double radio)
{
   double angulo, r, x, y;

   this->elementos = cantidad;
   this->bloque = new Punto *[cantidad];
   for (long i = 0; i < cantidad; i++)
   {
      angulo = randf(2 * M_PI);
      r = randf(radio);
      x = r * cos(angulo);
      y = r * sin(angulo);
      this->bloque[i] = new Punto(x, y);
   }
}
/**
 *   @brief Rellena el vector de puntos con puntos colocados en el origen
 **/
VectorPuntos::VectorPuntos(long cantidad)
{

   this->elementos = cantidad;
   this->bloque = new Punto *[cantidad];
   for (long i = 0; i < cantidad; i++)
   {
      bloque[i] = new Punto(0, 0);
   }
}
VectorPuntos::~VectorPuntos()
{
   for (long elemento = 0; elemento < this->elementos; elemento++)
   {
      delete bloque[elemento];
   }
   delete[] this->bloque;
}
/**
 *  Retorna el punto en la posición indicada del vector
 *
 **/
Punto *VectorPuntos::operator[](long posicion)
{
   assert(posicion >= 0 && posicion < elementos);
   return this->bloque[posicion];
}

/**
 *
 **/
long VectorPuntos::size()
{
   return this->elementos;
}

/**
 *  De los puntos en nuestro bloque encuentra el que esta más cercano al punto indicado como parámetro
 **/
long VectorPuntos::masCercano(Punto *punto)
{
   long elemento, posicion;
   double distancia, minimo;

   minimo = HUGE_VAL;
   posicion = -1;

   for (elemento = 0; elemento < this->elementos; elemento++)
   {
      distancia = this->bloque[elemento]->dist2(punto);
      if (minimo > distancia)
      {
         minimo = distancia;
         posicion = elemento;
      }
   }

   return posicion;
}

/**
 *   Suma de las distancias Euclidianas entre el centro y los elementos de su grupo
 *   @param	centro punto central (media) de cada grupo
 *   @param	clases	vector con los datos de pertenencia a las clases de los puntos
 **/
double VectorPuntos::variabilidad(Punto *centro, long clase, long *clases)
{
   long elemento;
   double sum = 0.0;

   for (elemento = 0; elemento < this->elementos; elemento++)
   {
      if (clases[elemento] == clase)
      {
         sum += this->bloque[elemento]->dist2(centro);
      }
   }

   return sum;
}
/**
 *   La suma de todas la variabilidades de todos los grupos
 *   @param	muestras	vector con las muestras
 *   @param	clases	vector con los datos de pertenencia a las clases de los puntos
 *
 **/
double VectorPuntos::disimilaridad(VectorPuntos *muestras, long *clases)
{
   long clase;
   double sum = 0.0;
   Punto *centro;

   for (clase = 0; clase < this->elementos; clase++)
   {
      centro = this->bloque[clase];
      sum += muestras->variabilidad(centro, clase, clases);
   }

   return sum;
}

/**
 *  Guarda en un archivo la colección de puntos en un imagen, para poder observar el trabajo realizado
 *  Utiliza otro elemento "posiciones" para indicar los centros y hacer las divisiones
 *  Utiliza el formato EPS por que se trata de un archivo de texto con estructura sencilla, aunque no es
 *  recomendado para uso general por problemas de seguridad
 *  @param	centros	vector con los puntos centrales de cada conjunto
 *  @param	posiciones	vector de longitud idéntica a this para determinar a cual clase pertenece el punto
 *  @param	fileName	nombre del archivo para guardar los datos, si existe se sobre-escribe
 *
 **/
#define H 400
#define W 400
void VectorPuntos::genEpsFormat(VectorPuntos *centros, long *clases, char *fileName)
{
   long clase, cantidadCentros, pos;
   double minX, maxX, minY, maxY, scale, cx, cy, px, py;
   double *colors;
   FILE *eps;

   cantidadCentros = centros->size();
   colors = new double[3 * cantidadCentros];

   for (clase = 0; clase < cantidadCentros; clase++)
   {
      pos = 3 * clase;
      colors[pos + 0] = (3 * (clase + 1) % cantidadCentros) / (double)cantidadCentros;
      colors[pos + 1] = (7 * clase % cantidadCentros) / (double)cantidadCentros;
      colors[pos + 2] = (9 * clase % cantidadCentros) / (double)cantidadCentros;
   }

   minX = minY = HUGE_VAL;
   maxX = maxY = -HUGE_VAL;
   for (pos = 0; pos < this->elementos; pos++)
   {
      if (maxX < this->bloque[pos]->getX())
      {
         maxX = this->bloque[pos]->getX();
      }
      if (minX > this->bloque[pos]->getX())
      {
         minX = this->bloque[pos]->getX();
      }
      if (maxY < this->bloque[pos]->getY())
      {
         maxY = this->bloque[pos]->getY();
      }
      if (minY > this->bloque[pos]->getY())
      {
         minY = this->bloque[pos]->getY();
      }
   }
   scale = W / (maxX - minX);
   if (scale > H / (maxY - minY))
   {
      scale = H / (maxY - minY);
   }
   cx = (maxX + minX) / 2;
   cy = (maxY + minY) / 2;

   eps = fopen(fileName, "w+");
   fprintf(eps, "%%!PS-Adobe-3.0\n%%%%BoundingBox: -5 -5 %d %d\n", W + 10, H + 10);
   fprintf(eps, "/l {rlineto} def /m {rmoveto} def\n"
                "/c { .25 sub exch .25 sub exch .5 0 360 arc fill } def\n"
                "/s { moveto -2 0 m 2 2 l 2 -2 l -2 -2 l closepath "
                "	gsave 1 setgray fill grestore gsave 3 setlinewidth"
                " 1 setgray stroke grestore 0 setgray stroke }def\n");
   for (clase = 0; clase < cantidadCentros; clase++)
   {
      fprintf(eps, "%g %g %g setrgbcolor\n", colors[3 * clase], colors[3 * clase + 1], colors[3 * clase + 2]);
      for (pos = 0; pos < this->elementos; pos++)
      {
         if (clases[pos] != clase)
         {
            continue;
         }
         px = this->bloque[pos]->getX();
         py = this->bloque[pos]->getY();
         fprintf(eps, "%.3f %.3f c\n", (px - cx) * scale + W / 2, (py - cy) * scale + H / 2);
      }
      // Print the centroid, using a small square
      px = (*centros)[clase]->getX();
      py = (*centros)[clase]->getY();
      fprintf(eps, "\n0 setgray %g %g s\n", (px - cx) * scale + W / 2, (py - cy) * scale + H / 2);
   }
   fprintf(eps, "\n%%%%EOF");
   fclose(eps);

   delete[] colors;
}
