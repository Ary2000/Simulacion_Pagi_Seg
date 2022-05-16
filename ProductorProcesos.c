#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct{
    int id, cantElementos, tiempoEjecucion;
    int espacioElementos[1];
    int registroBase[1];

}proceso;

bool paginacion = true;

proceso* crearProceso(){
    int elementos;
    if(paginacion){
        elementos  = rand() % (9) + 1;
    }else{
        elementos  = rand() % (4) + 1;
    }
    proceso* dato = malloc(sizeof(dato + elementos * sizeof dato->espacioElementos 
        + elementos * sizeof dato->registroBase));
    memset(dato->espacioElementos,0,elementos * sizeof dato->espacioElementos);
    memset(dato->registroBase,-1,elementos * sizeof dato->registroBase);
    for (int i = 0; i < elementos; i++)
    {
        if(paginacion){
            dato->espacioElementos[i] = 1;
        }else{
            dato->espacioElementos[i] = rand() % (2) + 1;
        }
    }
    dato->id = 0;
    dato->cantElementos = elementos;
    dato->tiempoEjecucion = rand() % (40) + 20;
    return dato;
}

int main(){
    proceso* p = crearProceso();
    printf("Id: %i\n", p->id);
    printf("Paginas: %i\n", p->cantElementos);
    printf("Tiempo: %i\n", p->tiempoEjecucion);
    printf("Espacios: ");
    for (int i = 0; i < p->cantElementos; i++)
    {
        printf(", %i", p->espacioElementos[i]);
    }
    printf("\n");
    printf("Registro: ");
    for (int i = 0; i < p->cantElementos; i++)
    {
        printf(", %i", p->registroBase[i]);
    }
    printf("\n");
    return 0;
}