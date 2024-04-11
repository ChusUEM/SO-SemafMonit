// Crear una estructura Cliente que tenga atributos nombre, apellido, edad, telefono y correo.

#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct
{
    int id;               // id cliente autoincremental
    int asientoReservado; // asiento reservado por el cliente
} Cliente;

#endif