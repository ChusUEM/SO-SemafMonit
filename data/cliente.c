#include "cliente.h"
#include "cine.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int idGlobal = 0;
sem_t semaforo;

// Creamos un cliente con un asiento reservado
Cliente crearCliente(int numReservas, bool patronAsientos, sem_t *semaforo, Asiento **cine)
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

            sem_wait(cliente->semaforo); // Bloquear el semáforo
            if (!cine[fila][columna].estaReservada && reservasRealizadas < cliente->numReservas)
            {
                cine[fila][columna].estaReservada = true;
                sleep(1); // Mantener el asiento reservado durante 1 segundo
                printf("El cliente %d ha reservado el asiento %d-%d\n", cliente->id, fila, columna);
                reservasRealizadas++;
            }
            sem_post(cliente->semaforo); // Desbloquear el semáforo
        }
    }
    else
    {
        for (int i = 0; i < FILAS && reservasRealizadas < cliente->numReservas; i++)
        {
            for (int j = 0; j < COLUMNAS && reservasRealizadas < cliente->numReservas; j++)
            {
                sem_wait(cliente->semaforo); // Bloquear el semáforo
                if (!cine[i][j].estaReservada)
                {
                    cine[i][j].estaReservada = true;
                    sleep(1);                    // Mantener el asiento reservado durante 1 segundo
                    sem_post(cliente->semaforo); // Desbloquear el semáforo
                    reservasRealizadas++;
                    return NULL;
                }
                sem_post(cliente->semaforo); // Desbloquear el semáforo
            }
        }
    }
    return NULL;
}