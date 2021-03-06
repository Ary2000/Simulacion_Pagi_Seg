#ifndef PROGRAMAPROCESOS_C
#define PROGRAMAPROCESOS_C

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include "ProgramaInicializador.c"

bool paginacion = true;
int estadoHilo = 1;



void stop(void){
    estadoHilo = 0;
}

proceso* crearProceso(){
    int elementos;
    if(paginacion){
        elementos  = rand() % (9) + 1;
    }else{
        elementos  = rand() % (4) + 1;
    }
    proceso* dato = malloc(sizeof(dato));
    dato->espacioElementos = calloc(elementos,sizeof(int));
    dato->registroBase = calloc(elementos,sizeof(int));
    for (int i = 0; i < elementos; i++)
    {
        if(paginacion){
            dato->espacioElementos[i] = 1;
        }else{
            dato->espacioElementos[i] = rand() % (2) + 1;
        }
    }
    varEstado = Espera;
    dato->estado = varEstado;
    dato->id = 0;
    dato->cantElementos = elementos;
    dato->tiempoEjecucion = rand() % (40) + 20;
    return dato;
}

void *generarProcesos(void *myvar)
{
    int id = 1;
    while(1){
        proceso *p = crearProceso();
        p->id = id;
        /*printf("Id: %i\n", p->id);
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
        printf("\n\n");*/
        pthread_t threadEntrarMemoria; 
        pthread_create(&threadEntrarMemoria, NULL, buscarEnLaMemoria,p);
        //agregar(&threadEntrarMemoria);
        //free(p);
        agregar(p);
        //p = p->siguiente;
        id = id +1;
        sleep(rand() % 30 + 30);  //rand() % 30 + 30 Este sleep va de 30 a 60 segundos
    }
    pthread_exit(NULL);
}

#endif