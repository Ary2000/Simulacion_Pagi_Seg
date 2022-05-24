#ifndef PROGRAMAESPIA_C
#define PROGRAMAESPIA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "ProductorProcesos.c"



int * memoriaCompartidaCopia = NULL;
void estadoMemoria();

void estadoProcesos(){
    printf("-------------------------------- PROGRAMA ESPIA --------------------------------\n");
    printf("Memoria: ");
    for (int i = 0; i < tamanoMemoria; ++i)
    {
        if(memoriaCompartida[i]!='1'){
            printf("%c",'0');
        }
        else{
            printf("%c",memoriaCompartida[i]);
        }
    }
    printf("\n");
    printf("Procesos acomodados en memoria: ");
    estadoMemoria();
    printf("\n*** PID EN MEMORIA ***");
    mostrarListaXEstado(EnMemoria);
    printf("*** PID BUSCANDO ENTRAR A MEMORIA ***");
    mostrarListaXEstado(Buscando);
    printf("*** PID BLOQUEADOS ESPERANDO ***");
    mostrarListaXEstado(Espera);
    mostrarListaXEstado(Saliendo);
    printf("*** PID MUERTO POR NO HABER ESPACIO ***");
    mostrarListaXEstado(Muerto);
    printf("*** PID PROCESOS QUE TERMINARON ***");
    mostrarListaXEstado(Ejecutado);
}
void estadoMemoria(){
    enum estados varE = EnMemoria;
    //memoria de tamaño n que acepta por direccion un maximo de 4 chars
    memoriaCompartidaCopia = calloc(tamanoMemoria,sizeof(int));
    for (int i = 0; i < tamanoMemoria; i++)
    {
        memoriaCompartidaCopia[i] = 0;
    }
    nodo* aux2 = primero;
    if(paginacion){
        while(aux2!=NULL){
            proceso* p2 = aux2->p;
            if(p2->estado==varE){
                for (int i = 0; i < p2->cantElementos; i++)
                {
                    int indice = p2->registroBase[i];
                    memoriaCompartidaCopia[indice] = p2->id;
                }

            }
            aux2 = aux2->siguiente;
        }
    }
    else{
        while(aux2!=NULL){
            proceso* p2 = aux2->p;
            if(p2->estado==varE){
                for (int i = 0; i < p2->cantElementos; i++)
                {
                    int indice = p2->registroBase[i];
                    int max = p2->espacioElementos[i];
                    for (int j = 0; j < max; ++j)
                    {
                        memoriaCompartidaCopia[indice] = p2->id;
                        indice = indice+1;
                    }
                }
            }
            aux2 = aux2->siguiente;
        }

    }
    for (int i = 0; i < tamanoMemoria; i++)
    {
        printf("%d,",memoriaCompartidaCopia[i]);
    }
}

#endif