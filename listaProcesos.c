#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <pthread.h>


enum estados{Espera, Ejecutado, Buscando, EnMemoria, Saliendo, Muerto};

typedef struct{
    int id, cantElementos, tiempoEjecucion;
    enum estados estado;
    int *espacioElementos;
    int *registroBase;
    pthread_t hilo;
    struct proceso* siguiente;

}proceso;

typedef struct{
   struct proceso* p;
   struct nodo* siguiente;
}nodo;

nodo* primero = NULL;
nodo* ultimo = NULL;

void agregar(proceso* p){
   nodo* dato = malloc(sizeof(nodo)); //Inicializa el nodo
   dato->siguiente = NULL;
   dato->p = p;

   if(primero == NULL){
      primero = dato;
      ultimo = dato;
   }
   else{
      ultimo->siguiente = dato;
      ultimo = dato;
   }
}

int largoLista(){
   int cont = 0;
   nodo* i = primero;
   while(i != NULL){
      cont++;
      i = i->siguiente;
   }
   return cont;
}

nodo* getPrimero(){
   return primero;
}

nodo* getUltimo(){
   return ultimo;
}


nodo* getElemento(int pos){
   /*if(pos == 0){
      return getPrimero;
   }*/
   nodo* aux = primero;
   int cont = 0;
   while (aux != NULL)
   {
      if(cont == pos){
         return aux;
      }else{
         aux = aux->siguiente;
      }
      cont = cont + 1;
   }
   return NULL;
}
/*void eliminar(int pos){
   if(primero == NULL){
      return;
   }
   nodo* aux = primero;
   if(pos==0){
      if(primero->siguiente == NULL){
         ultimo = NULL;
         primero = NULL;
      }else{
         primero = primero->siguiente;
         aux->siguiente = NULL;
      }
      aux->finish = salida;
      //free(aux);
   }
   else{
      nodo* prev = NULL;
      for (int i = 0; i < largoLista(); ++i)
      {
         if(i==pos){
            if(pos == largoLista()-1){
               prev->siguiente = NULL;
               ultimo = prev;
            }
            else{
               prev->siguiente = aux->siguiente;
            }
            aux->siguiente = NULL;
            aux->finish = salida;
            //free(aux);
            break;
         }
         prev = aux;
         aux = aux->siguiente;
      }

   }
}*/
