#include "cine.h"
#include "cliente.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    // Creamos una matriz de asientos representando el cine
    Asiento **cine = crearCine();
    int numClientes = 10;
    // Variable para almacenar el patrón de asientos de cada cliente
    bool patronAsientos;
    sem_t semaforo;
    sem_init(&semaforo, 0, 1);

    // Creamos un array para almacenar los datos de los clientes y otro para almacenar los identificadores de los hilos
    Cliente clientes[numClientes];
    pthread_t hilos[numClientes];

    // Iteramos para crear cada cliente y su hilo correspondiente
    for (int i = 0; i < numClientes; i++)
    {
        // Generamos un valor aleatorio para el patrón de asientos
        int aleatorio = rand() % 2;
        patronAsientos = aleatorio == 0 ? false : true;
        // Generamos un número aleatorio de reservas para este cliente entre 1 y 4 asientos
        int numReservas = rand() % 4 + 1;
        // Creamos el cliente con la función crearCliente(), pasando el número de reservas, el patrón de asientos, el semáforo y la matriz de asientos del cine
        clientes[i] = crearCliente(numReservas, patronAsientos, &semaforo, cine);
        // Creamos un hilo para este cliente, utilizando la función reservarAsiento() como función a ejecutar por el hilo y pasando el cliente correspondiente como argumento
        pthread_create(&hilos[i], NULL, reservarAsiento, &clientes[i]);
    }

    // Esperamos a que todos los hilos terminen
    for (int i = 0; i < numClientes; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    // Destruimos el semáforo después de su uso
    sem_destroy(&semaforo);

    // Imprimimos el estado final del cine después de que todos los clientes hayan reservado sus asientos
    pintarCine(cine);
    return 0;
}