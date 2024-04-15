#ifndef CLIENTE_MacOS_H
#define CLIENTE_MacOS_H
#include <stdbool.h>
#include <semaphore.h>
#include "cine_MacOS.h"
#include <dispatch/dispatch.h>

typedef struct
{
    int id;
    int numReservas;
    bool patronAsientos;
    dispatch_semaphore_t semaforo;
    Asiento **cine;
} Cliente;

void *reservarAsiento(void *arg);
Cliente crearCliente(int numReservas, bool patronAsientos, dispatch_semaphore_t semaforo, Asiento **cine);

#endif