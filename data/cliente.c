#include "cliente.h"
#include "cine.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Variable global para asignar un ID único a cada cliente
int idGlobal = 0;
sem_t semaforo;

// Función para crear un cliente con un asiento reservado
Cliente crearCliente(int numReservas, bool patronAsientos, sem_t *semaforo, Asiento **cine)
{
    // Creamos un nuevo cliente y le asignamos los valores recibidos
    Cliente nuevoCliente;
    nuevoCliente.id = idGlobal++;
    nuevoCliente.numReservas = numReservas;
    nuevoCliente.patronAsientos = patronAsientos;
    nuevoCliente.semaforo = semaforo;
    nuevoCliente.cine = cine;
    return nuevoCliente;
}

// Función que simula la reserva de asientos por parte del cliente
void *reservarAsiento(void *arg)
{
    // Recogemos los valores del puntero en un nuevo objeto
    Cliente *cliente = (Cliente *)arg;
    Asiento **cine = cliente->cine; // Obtenemos la matriz de asientos del cine del cliente

    // Contador de reservas realizadas por el cliente
    int reservasRealizadas = 0;

    // Selector que indica la forma de seleccionar el asiento
    if (cliente->patronAsientos)
    {
        // Iteramos para realizar las reservas de acuerdo al número de reservas que el cliente tiene que hacer
        for (int k = 0; k < cliente->numReservas; k++)
        {
            // Seleccionamos una fila y columna aleatoria dentro del cine
            int fila = rand() % FILAS;
            int columna = rand() % COLUMNAS;
            // Bloqueamos el semáforo antes de acceder a los datos compartidos
            sem_wait(cliente->semaforo);
            // Verificamos si el asiento seleccionado está disponible y si aún no hemos alcanzado el número máximo de reservas
            if (!cine[fila][columna].estaReservada && reservasRealizadas < cliente->numReservas)
            {
                // Realizamos la reserva del asiento
                cine[fila][columna].estaReservada = true;
                // Mantenemos el asiento reservado durante 1 segundo
                sleep(1);
                printf("El cliente %d ha reservado el asiento %d-%d\n", cliente->id, fila, columna);
                // Incrementamos el contador de reservas realizadas
                reservasRealizadas++;
            }
            // Desbloqueamos el semáforo después de acceder a los datos compartidos
            sem_post(cliente->semaforo);
        }
    }
    else
    {
        // Iteramos sobre todas las filas y columnas del cine hasta que el cliente haya realizado todas sus reservas
        for (int i = 0; i < FILAS && reservasRealizadas < cliente->numReservas; i++)
        {
            for (int j = 0; j < COLUMNAS && reservasRealizadas < cliente->numReservas; j++)
            {
                // Bloqueamos el semáforo antes de acceder a los datos compartidos
                sem_wait(cliente->semaforo);
                // Verificamos si el asiento seleccionado está disponible
                if (!cine[i][j].estaReservada)
                {
                    // Realizamos la reserva del asiento
                    cine[i][j].estaReservada = true;
                    // Mantenemos el asiento reservado durante 1 segundo
                    sleep(1);
                    printf("El cliente %d ha reservado el asiento %d-%d\n", cliente->id, i, j);
                    // Desbloqueamos el semáforo después de acceder a los datos compartidos
                    sem_post(cliente->semaforo);
                    // Incrementamos el contador de reservas realizadas
                    reservasRealizadas++;
                    return NULL;
                }
                // Desbloqueamos el semáforo después de acceder a los datos compartidos
                sem_post(cliente->semaforo);
            }
        }
    }
    return NULL;
}