#include "cine.h"
#include "cliente.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// Queremos utilizar la funcion de cine.c en main.c que se llama crearCine para crear una variable cine
int main()
{
    // Creamos una variable cine que es una matriz de asientos
    Asiento **cine = crearCine();
    pintarCine(cine);
    int numClientes = 20;
    bool patronAsientos;
    sem_t semaforo;
    sem_init(&semaforo, 0, 1); // Inicializar el semáforo

    // Crea un numero aleatorio de clientes con crearCliente(), que tengan random el patronAsientos y un numero de numReservas entre 1 y 4
    Cliente clientes[numClientes];
    pthread_t hilos[numClientes];

    for (int i = 0; i < numClientes; i++)
    {
        int aleatorio = rand() % 2;
        patronAsientos = aleatorio == 0 ? false : true;
        int numReservas = rand() % 4 + 1;
        clientes[i] = crearCliente(numReservas, patronAsientos, &semaforo, cine);
        pthread_create(&hilos[i], NULL, reservarAsiento, &clientes[i]);
    }

    for (int i = 0; i < numClientes; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&semaforo); // Destruir el semáforo

    pintarCine(cine);
    return 0;
}
