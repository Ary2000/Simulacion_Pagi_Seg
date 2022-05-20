#ifndef PROGRAMAPROCESOS_C
#define PROGRAMAPROCESOS_C

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ColaReady.c"
#include <semaphore.h>
#include <pthread.h>

#include "ProgramaInicializador.c"


pthread_mutex_t mutex;



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
    //proceso* dato = malloc(sizeof(dato + elementos * sizeof dato->espacioElementos 
    //    + elementos * sizeof dato->registroBase));
    //memset(dato->espacioElementos,0,elementos * sizeof dato->espacioElementos);
    //memset(dato->registroBase,-1,elementos * sizeof dato->registroBase);
    proceso* dato = malloc(sizeof(dato));
    dato->espacioElementos = calloc(elementos,sizeof(int));
    dato->registroBase = calloc(elementos,sizeof(int));
    // for (int i = 0; i < elementos; ++i)
    // {
    //     dato->espacioElementos[i]=0;
    //     dato->registroBase[i]=-1;

    // }
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
    //dato->estado = Espera;
    return dato;
}


void *buscarEspacioMemoria(void *arg){
    proceso *p;
    p = (proceso *) arg;
    pthread_mutex_lock(&mutex);
    printf("%d\n", p->id);
    pthread_mutex_unlock(&mutex);
    free(p);
    pthread_exit(NULL);
    //semaforo();
    //muevo proceso al bloque de memoria
    //memoria()
    //  memmove(contenido_bloque_memoria, proceso, strlen(data2)+1);
    //  sleep(proceso->tiempo)
    //printf("%s\n","mueve el proceso");
}
void *generarProcesos(void *myvar)
{
    int id = 0;
    while(1){
        proceso* p = crearProceso();
        p->id = id;
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
        printf("\n\n");
        pthread_t threadEntrarMemoria; 
        pthread_create(&threadEntrarMemoria, NULL, buscarEnLaMemoria, p);
        //pthread_join(threadEntrarMemoria, NULL);
        //agregar(threadEntrarMemoria);
        //free(p);
        id = id +1;
        sleep(1);  //Este sleep va de 30 a 60 segundos
    }
    for (int i = 0; i < largoLista(); ++i)
    {
        pthread_join(getElemento(i)->proceso,NULL);
    }
    pthread_exit(NULL);
}

void *menu(){
    printf("1.TERMINAR EJECUCION\n");
    int numTeclado;
    while(1){
        scanf("%d",&numTeclado);
        if(numTeclado==1){
            exit(EXIT_SUCCESS);
        }
    }
    pthread_exit(NULL);
}

/*bool buscarEspacio = true;

void semaforo(){
    //pthread_mutex_t mutex
    //funcion hilo -> pthread_mutex_lock , sentencia, pthread_mutex_unlock
    //pthread_mutex_init(&mutex,NULL); 
    if(buscarEspacio==false){
        wait();
    }
    else{
        buscarEspacio = false;
        printf("%s\n", "Buscando espacio...");
        buscarEspacio = true;
    }

}*/



// int main(){
//     pthread_mutex_init(&mutex,NULL);
//     pthread_t threadGenerarProcesos, threadMenu;
//     pthread_create(&threadGenerarProcesos, NULL, generarProcesos, NULL);
//     pthread_create(&threadMenu, NULL, menu, NULL);
//     pthread_join(threadGenerarProcesos,NULL);
//     pthread_join(threadMenu, NULL);
//     return 0;
// }


// int main(){
//     //int tamanoMemoria = pedirTamanoMemoria();
//     tamanoMemoria = 5;

//     // Pide el bloque de memoria compartida
//     //int bloque = obtener_memoria_compartida("ProgramaInicializador.c", tamanoMemoria); 
//     //if(bloque == IPC_RESULT_ERROR){
//     //    return IPC_RESULT_ERROR;
//     //}
//     // Mapea los contenidos de la memoria compartida para que esten en formato de char*
//     //char *contenido_bloque_memoria = shmat(bloque, NULL, 0);

//     pthread_t threadGenerarProcesos;
//     pthread_create(&threadGenerarProcesos, NULL, generarProcesos, NULL);
//     pthread_join(threadGenerarProcesos,NULL);

//     char contenido_bloque_memoria[] = {'0', '0', '0', '0', '0'};
//     int procesos[] = {2, 1};
//     int registrosBase[] = {0, 0};
//     bool hayEspacio = buscarEnLaMemoria(contenido_bloque_memoria, sizeof(contenido_bloque_memoria) / sizeof(char), procesos, sizeof(procesos) / sizeof(int), registrosBase);
//     eliminarEnLaMemoria(contenido_bloque_memoria, tamanoMemoria, registrosBase, procesos, sizeof(registrosBase)/sizeof(int));
    
//     shmdt(contenido_bloque_memoria);

//     return 0;
// }

#endif