#include <cstdio>
#include "Punto.h"

/**
 *   @brief Constructor básico, deja las coordenadas en cero
 **/
Punto::Punto()
    : x(0), y(0), z(0)
{
}
/**
 *   @brief Constructor, inicializa el punto con los parámetros indicados
 **/
Punto::Punto(double x, double y, double z)
    : x(x), y(y), z(z)
{
}
/**
 *  @brief Devuelve el valor de la coordenada x
 **/
double Punto::getX()
{

   return this->x;
}
/**
 *  @brief Retorna el valor de la coordenada y
 **/
double Punto::getY()
{

   return this->y;
}
/**
 *  @brief Cambia el valor de las coordenadas
 **/
void Punto::modificar(double vx, double vy, double vz)
{
   this->x = vx;
   this->y = vy;
   this->z = vz;
}
/**
 *   @brief Calcula el cuadrado de la distancia entre dos puntos (Euclidiana)
 *   Por el momento utiliza solo dos coordenadas "x" y "y"
 *
 **/
double Punto::dist2(Punto *otro)
{
   double dx = this->x - otro->x;
   double dy = this->y - otro->y;
   double resultado;

   resultado = dx * dx + dy * dy;

   return resultado;
}
/**
 *  @brief Suma desplazamientos a un punto
 **/
void Punto::sume(Punto *sumando)
{
   this->x += sumando->x;
   this->y += sumando->y;
   this->z += sumando->z;
}
/**
 *  @brief Divide las coordenas de un punto por el mismo valor
 **/
void Punto::divida(double div)
{

   this->x /= div;
   this->y /= div;
   this->z /= div;
}
/**
 *  @brief Despliega la información de un punto
 **/
std::string Punto::ver()
{
   std::string disp;

   disp = "[ " + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + " ]";

   return disp;
}
