#ifndef CLIENTE_H
#define CLIENTE_H
#include <stdbool.h>
#include <semaphore.h>
#include "cine.h"

typedef struct
{
    int id;
    int numReservas;
    bool patronAsientos;
    sem_t *semaforo;
    Asiento **cine;
} Cliente;

void *reservarAsiento(void *arg);
Cliente crearCliente(int numReservas, bool patronAsientos, sem_t *semaforo, Asiento **cine);

#endif