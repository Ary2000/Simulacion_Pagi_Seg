#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
   int cantElementos, tiempoEjecucion;
   int info[];

}proceso;

bool paginacion = true;

proceso crearProceso(){
    proceso dato = malloc(sizeof(proceso));
    int elementos;
    if(paginacion){
        elementos = rand() % (10) + 1;
        int espacios[] = {1};
        dato->cantElementos = elementos;
        dato->info = espacios
    }else{
        elementos = rand() % (5) + 1;
        int espacios[elementos];
        for (int i = 0; i < elementos; i++)
        {
            espacios[i] = rand() % (3) + 1;
        }
        dato->cantElementos = elementos;
        dato->info = espacios
    }
    dato->tiempoEjecucion = rand() % (20) + 1;
    return dato;
}