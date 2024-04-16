#include "cine_MacOS.h"
#include "cliente_MacOS.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dispatch/dispatch.h>
#include <sys/time.h>

double obtenerTiempo()
{
    struct timeval tiempo;
    gettimeofday(&tiempo, NULL);
    return tiempo.tv_sec + tiempo.tv_usec / 1000000.0;
}

int main()
{
    double inicio, fin;
    inicio = obtenerTiempo();

    Asiento **cine = crearCine();
    pintarCine(cine);
    int numClientes = 10;
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
    fin = obtenerTiempo(); // Guarda el tiempo de finalización


    // Imprimimos y sacamos las métricas de los resultados obtenidos
    double tiempo_total = fin - inicio;
    double clientes_media = (double)numClientes;
    printf("Tiempo total: %.6f segundos\n", tiempo_total);
    double media_tiempo = clientes_media / tiempo_total;
    printf("Media por cliente: %.6f segundos\n", media_tiempo);
    return 0;
}