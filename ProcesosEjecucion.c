#include <stdio.h>
#include "ProductorProcesos.c"

typedef struct{
    int idProcess;
    proceso* process;
    struct ejecucion* siguiente;
}ejecucion;

ejecucion* inicio = NULL;
ejecucion* fin = NULL;

ejecucion* iniMuertos = NULL;
ejecucion* finMuertos = NULL;

ejecucion* iniFinalizados = NULL;
ejecucion* finFinalizados = NULL;

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
            aEliminar->siguiente = NULL;
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

void starvation(proceso* p){
    ejecucion* dato = malloc(sizeof(ejecucion));
    dato->idProcess = p->id;
    dato->process = p;
    dato->siguiente = NULL;
    if(iniMuertos == NULL){
        iniMuertos = dato;
        finMuertos = dato;
    }else{
      finMuertos->siguiente = dato;
      finMuertos = dato;
    }
}

int lenStarvation(){
    int cont = 0;
    ejecucion* i = iniMuertos;
    while(i != NULL){
        cont++;
        i = i->siguiente;
    }
    return cont;
}

void finalizo(proceso* p){
    ejecucion* dato = malloc(sizeof(ejecucion));
    dato->idProcess = p->id;
    dato->process = p;
    dato->siguiente = NULL;
    if(iniFinalizados == NULL){
        iniFinalizados = dato;
        finFinalizados = dato;
    }else{
      finFinalizados->siguiente = dato;
      finFinalizados = dato;
    }
}

int lenFinalizo(){
    int cont = 0;
    ejecucion* i = iniFinalizados;
    while(i != NULL){
        cont++;
        i = i->siguiente;
    }
    return cont;
}

void liberarMemoria(){
    ejecucion* aux;
    if(inicio != NULL){
        aux = inicio;
        while (inicio != fin)
        {
            inicio = inicio->siguiente;
            aux->siguiente = NULL;
            free(aux);
            aux = inicio;
        }
        inicio = NULL;
        fin = NULL;
        free(aux);
    }
    if(iniMuertos != NULL){
        aux = iniMuertos;
        while (iniMuertos != finMuertos)
        {
            iniMuertos = iniMuertos->siguiente;
            aux->siguiente = NULL;
            free(aux);
            aux = iniMuertos;
        }
        iniMuertos = NULL;
        finMuertos = NULL;
        free(aux);
    }
    if(iniFinalizados != NULL){
        aux = iniFinalizados;
        while (iniFinalizados != finFinalizados)
        {
            iniFinalizados = iniFinalizados->siguiente;
            aux->siguiente = NULL;
            free(aux);
            aux = iniFinalizados;
        }
        iniFinalizados = NULL;
        finFinalizados = NULL;
        free(aux);
    }
}