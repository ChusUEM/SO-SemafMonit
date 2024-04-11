#include <stdbool.h>

#define FILAS 10
#define COLUMNAS 15

typedef struct
{
    int fila;
    int columna;
    bool estaReservada;
} Asiento;

Asiento **crearCine();