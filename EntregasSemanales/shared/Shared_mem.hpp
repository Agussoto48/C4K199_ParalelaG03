#pragma once
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

// Crear o conectar a un segmento de memoria compartida
void* create_shared_memory(key_t key, size_t size, int* id , bool create);

// Desconectar y eliminar un segmento
void destroy_shared_memory(void* ptr, int shmid, bool remove);