#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct{
   int cantElementos, tiempoEjecucion;
   int segmentos[1];

}segmentacion;

segmentacion* crearSegmentacion(){
    int elementos  = rand() % (5) + 1;
    segmentacion* dato = malloc(sizeof(dato + elementos * sizeof dato->segmentos));
    memset(dato->segmentos,0,elementos * sizeof dato->segmentos);
    //dato->segmentos = int[elementos];
    for (int i = 0; i < elementos; i++)
    {
        dato->segmentos[i] = rand() % (3) + 1;
    }
    dato->cantElementos = elementos;
    dato->tiempoEjecucion = rand() % (20) + 1;
    return dato;
}

int main(){
    return 0;
}