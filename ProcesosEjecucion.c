#include <stdio.h>
#include "ProductorProcesos.c"

typedef struct{
    int idProcess;
    proceso* process;
    struct ejecucion* siguiente;
}ejecucion;

ejecucion* inicio = NULL;
ejecucion* fin = NULL;

void insertar(proceso* p){
    ejecucion* dato = malloc(sizeof(ejecucion));
    dato->idProcess = p->id;
    dato->process = p;
    dato->siguiente = NULL;
    if(inicio == NULL){
        inicio = dato;
        fin = dato;
    }else{
      fin->siguiente = dato;
      fin = dato;
    }
}

void eliminar(proceso* p){
    if(inicio == NULL){
        return;
    }
    if(inicio->idProcess == p->id){
        ejecucion* aux = primero;
        if(inicio==fin){
            inicio = NULL;
            fin = NULL;
        }else{
            primero = primero->siguiente;
        }
        free(aux);
        return;
    }
    ejecucion* aEliminar = inicio->siguiente;
    ejecucion* aux = primero;
    while(aEliminar != NULL){
        if(aEliminar->idProcess == p->id){
            aux->siguiente = aEliminar->siguiente;
            free(aEliminar);
            return;
        }
        aEliminar = aEliminar->siguiente;
        aux = aux->siguiente;
    }
}

int cantProcesos(){
   int cont = 0;
   ejecucion* i = inicio;
   while(i != NULL){
      cont++;
      i = i->siguiente;
   }
   return cont;
}

proceso* getProceso(int pos){
    if(inicio == NULL){
        return NULL;
    }
    if(pos < 0){
        return NULL;
    }if(pos == 0){
        return inicio->process;
    }
    int cont = 0;
    ejecucion* aux = inicio;
    while (cont != pos && aux != NULL)
    {
        pos++;
        aux = aux->siguiente;
    }
    if(aux == NULL){
        return NULL;
    }
    return aux->process;
}