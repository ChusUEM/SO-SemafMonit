#include "cine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Función para crear una matriz de asientos
Asiento **crearCine()
{
    // Reservamos memoria para la cantidad de filas del cine
    Asiento **cine = malloc(FILAS * sizeof(Asiento *));

    // Iteramos sobre cada fila
    for (int i = 0; i < FILAS; i++)
    {
        // Reservamos memoria para las columnas en cada fila
        cine[i] = malloc(COLUMNAS * sizeof(Asiento));

        // Iteramos sobre cada asiento en la fila
        for (int j = 0; j < COLUMNAS; j++)
        {
            // Inicializamos el asiento con su fila, columna y marcado como no reservado
            cine[i][j].fila = i;
            cine[i][j].columna = j;
            cine[i][j].estaReservada = false;
        }
    }

    return cine;
}

// Función para imprimir el estado del cine
void pintarCine(Asiento **cine)
{
    printf("Estado del cine:\n");

    // Iteramos sobre cada fila del cine
    for (int i = 0; i < FILAS; i++)
    {
        // Iteramos sobre cada asiento en la fila
        for (int j = 0; j < COLUMNAS; j++)
        {
            // Imprimimos 1 si el asiento está reservado y 0 si se encuentra disponible
            printf("%d ", cine[i][j].estaReservada ? 1 : 0);
        }
        printf("\n");
    }
}