#include "cine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Creamos una función que cree una matriz de asientos de FILAS y COLUMNAS, iniciliazadas en false
Asiento **crearCine()
{
    Asiento **cine = malloc(FILAS * sizeof(Asiento *));

    for (int i = 0; i < FILAS; i++)
    {
        cine[i] = malloc(COLUMNAS * sizeof(Asiento));
        for (int j = 0; j < COLUMNAS; j++)
        {
            cine[i][j].fila = i;
            cine[i][j].columna = j;
            cine[i][j].estaReservada = false;
        }
    }

    return cine;
}

void pintarCine(Asiento **cine) {
    printf("Estado del cine:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", cine[i][j].estaReservada ? 1 : 0);
        }
        printf("\n");
    }
}