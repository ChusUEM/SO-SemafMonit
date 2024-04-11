#include "cine.h"
// #include "cliente.h"
#include <stdio.h>

// Queremos utilizar la funcion de cine.c en main.c que se llama crearCine para crear una variable cine
int main()
{
    // Creamos una variable cine que es una matriz de asientos
    Asiento **cine = crearCine();

    // Imprimimos la matriz de asientos
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            printf("%d ", cine[i][j].estaReservada);
        }
        printf("\n");
    }

    return 0;
}
