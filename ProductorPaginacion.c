#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
   int cantElementos, tiempoEjecucion;

}paginacion;

paginacion* crearPaginacion(){
    paginacion* dato = malloc(sizeof(paginacion));
    dato->cantElementos = rand() % (10) + 1;
    dato->tiempoEjecucion = rand() % (20) + 1;
    return dato;
}

int main(){
    return 0;
}