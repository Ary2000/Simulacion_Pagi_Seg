#ifndef PROGRAMAESPIA_C
#define PROGRAMAESPIA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "ProcesosEjecucion.c"

void estadoMemoria(){
    int procesos[1];
    memset(procesos,0,1);//array, dato a inicializar, elementos a cambiar del arreglo
    int count = cantProcesos();
    for (int i = 0; i < count; i++)
    {
        proceso* p = getProceso(i);
        for (int j = 0; i < p->cantElementos; j++)
        {
            procesos[j] = p->id;
        }
        
    }
    for (int i = 0; i < 1; i++)
    {
        printf("[ %i ]\n", procesos[i]);
    }
    
}

void estadoProcesos(){

}

int main(){
    bool seleccion = true;
    while(seleccion){
        printf("Seleccionar cual tipo de estado quiere revisar\n1. Estado memoria\n2. Estado procesos\n3. Finalizar\n");
        char character = getchar();
        while ((getchar()) != '\n');
        switch (character)
        {
        case '1':
            estadoMemoria();
            seleccion = false;
            break;

        case '2':
            estadoProcesos();
            seleccion = false;
            break;

        case '3':
            seleccion = false;
            break;

        default:
            printf("\n\n\n\n\n\n\nPor favor insertar uno de los numeros presentes\n");
            break;
        }
    }
    /*srand(time(NULL));
    pthread_t threadConexionCliente,threadTerminar;
    pthread_create(&threadConexionCliente, NULL, hiloConexionCliente, NULL); 
    pthread_create(&threadTerminar, NULL, hiloTerminar, NULL);
    //Crear menu de seleccion
    bool seleccion = true;
    while(seleccion) {
        printf("Seleccionar cual tipo de cliente se quiere correr\n1. Cliente manual\n2. Cliente Automatico\n");
        char character = getchar();
        while ((getchar()) != '\n');
        switch (character)
        {
        case '1':
            clienteManual();
            seleccion = false;
            break;

        case '2':
            clienteAutomatico();
            seleccion = false;
            break;

        default:
            printf("\n\n\n\n\n\n\nPor favor insertar uno de los numeros presentes\n");
            break;
        }
    }
    pthread_join(threadConexionCliente,NULL); //Termina la ejecucion del hilo de cliente
    pthread_join(threadTerminar,NULL);*/
    return 0;
}

#endif