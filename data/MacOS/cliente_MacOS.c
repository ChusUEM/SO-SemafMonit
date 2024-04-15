#include "cliente_MacOS.h"
#include "cine_MacOS.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>

int idGlobal = 0;
sem_t semaforo;

// Creamos un cliente con un asiento reservado
Cliente crearCliente(int numReservas, bool patronAsientos, dispatch_semaphore_t semaforo, Asiento **cine)
{
    Cliente nuevoCliente;
    nuevoCliente.id = idGlobal++;
    nuevoCliente.numReservas = numReservas;
    nuevoCliente.patronAsientos = patronAsientos;
    nuevoCliente.semaforo = semaforo;
    nuevoCliente.cine = cine;
    return nuevoCliente;
}

// Pasarle al cliente un cine determinado en cine.h
void *reservarAsiento(void *arg)
{
    Cliente *cliente = (Cliente *)arg;
    Asiento **cine = cliente->cine;
    // Usa el cine del cliente
    int reservasRealizadas = 0;
    if (cliente->patronAsientos)
    {
        for (int k = 0; k < cliente->numReservas; k++)
        {
            int fila = rand() % FILAS;
            int columna = rand() % COLUMNAS;

            dispatch_semaphore_wait(cliente->semaforo, DISPATCH_TIME_FOREVER); // Bloquear el semáforo
            if (!cine[fila][columna].estaReservada && reservasRealizadas < cliente->numReservas)
            {
                cine[fila][columna].estaReservada = true;
                sleep(1); // Mantener el asiento reservado durante 1 segundo
                printf("El cliente %d ha reservado el asiento %d-%d\n", cliente->id, fila, columna);
                reservasRealizadas++;
            }
            dispatch_semaphore_signal(cliente->semaforo); // Desbloquear el semáforo
        }
    }
    else
    {
        for (int i = 0; i < FILAS && reservasRealizadas < cliente->numReservas; i++)
        {
            for (int j = 0; j < COLUMNAS && reservasRealizadas < cliente->numReservas; j++)
            {
                dispatch_semaphore_wait(cliente->semaforo, DISPATCH_TIME_FOREVER); // Bloquear el semáforo
                if (!cine[i][j].estaReservada)
                {
                    cine[i][j].estaReservada = true;
                    sleep(1);                                     // Mantener el asiento reservado durante 1 segundo
                    dispatch_semaphore_signal(cliente->semaforo); // Desbloquear el semáforo
                    reservasRealizadas++;
                    return NULL;
                }
                dispatch_semaphore_signal(cliente->semaforo); // Desbloquear el semáforo
            }
        }
    }
    return NULL;
}