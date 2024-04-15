#include "cine_MacOS.h"
#include "cliente_MacOS.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dispatch/dispatch.h>
#include <time.h>

int main()
{
    Asiento **cine = crearCine();
    clock_t inicio = clock(); // Inicializar el reloj
    pintarCine(cine);
    int numClientes = 30;
    bool patronAsientos;
    dispatch_semaphore_t semaforo = dispatch_semaphore_create(1); // Inicializar el semáforo
    Cliente clientes[numClientes];
    pthread_t hilos[numClientes];

    for (int i = 0; i < numClientes; i++)
    {
        int aleatorio = rand() % 2;
        patronAsientos = aleatorio == 0 ? false : true;
        int numReservas = rand() % 4 + 1;
        clientes[i] = crearCliente(numReservas, patronAsientos, semaforo, cine);
        pthread_create(&hilos[i], NULL, reservarAsiento, &clientes[i]);
    }

    for (int i = 0; i < numClientes; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    dispatch_semaphore_signal(semaforo); // Incrementar el semáforo

    pintarCine(cine);
    clock_t fin = clock(); // Finalizar el reloj
    // Calcular el tiempo total que tardó la sección de código
    double tiempo_total = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    // Imprimir el tiempo total
    printf("Tiempo total: %f segundos\n", tiempo_total);
    return 0;
}