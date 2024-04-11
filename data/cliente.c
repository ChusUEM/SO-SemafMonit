#include "cliente.h"

int idGlobal = 0;

Cliente crearCliente(int asientoReservado)
{
    Cliente nuevoCliente;
    nuevoCliente.id = idGlobal++;
    nuevoCliente.asientoReservado = asientoReservado;
    return nuevoCliente;
}