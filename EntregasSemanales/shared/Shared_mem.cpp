#include "Shared_mem.hpp"

void* create_shared_memory(key_t key, size_t size, int* id , bool create) {
    int flags = 0600;
    if (create)
        flags |= IPC_CREAT;

    *id = shmget(key, size, flags);
    if (*id == -1) {
        perror("Error en shmget");
        exit(EXIT_FAILURE);
    }

    void* ptr = shmat(*id, NULL, 0);
    if (ptr == (void*) -1) {
        perror("Error en shmat");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void destroy_shared_memory(void* ptr, int shmid, bool remove) {
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
        
    
}
