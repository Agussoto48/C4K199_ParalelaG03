#pragma once
#include "Contador.hpp"
#include<sstream>
//Funciones logicas que el main ejecuta
/**
 * Funcion para manejar y comprobar los parametros que se ingresan
 */
bool manejar_parametros(int argc, char* argv[], int& trabajadores, std::vector<int>& estrategias, std::vector<std::string>& archivos);

/**
 * Funcion para la creacion de hilos para los contadores
 */
void* inicializar_tareas(void* arg);