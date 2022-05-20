#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ProductorProcesos.c"

FILE *archivo;
char fileName[] = "Bitacora.txt";

void abrirBitacora(){
    remove(fileName);
    archivo = fopen(fileName,"w");
}

void cerrarBitacora(){
    fclose(archivo);
}

void getEstado(char* string, enum estados estado){
    switch (estado)
    {
    case Ejecutado:
        strcpy(string, "ejecucion finalizada");
        break;

    case Buscando:
        strcpy(string, "buscando espacio");
        break;

    case EnMemoria:
        strcpy(string, "en ejecucion");
        break;

    /*case Saliendo:
        strcpy(string, "solicitando semaforo para salir");
        break;*/
    
    case Muerto:
        strcpy(string, "muerto");
        break;
    default:
        strcpy(string, "esperando semaforo para entrar");
        break;
    }
}

void getPosiciones(char* string, proceso *p){

}

void escribirBitacora(proceso *p){
    //PID, estado, espacio en memoria(si esta en memoria)/eliminado, hora
    time_t horaActual = time(NULL);
    char entrada[90];
    char estado[40];
    char pocisionesMem[30];
    getEstado(estado, p->estado);
    if(p->estado == EnMemoria){
        getPosiciones(pocisionesMem, p);
    }
    sprintf(entrada, "PID: %i, Estado: %s, Hora: %s\n",p->id, estado, ctime(&horaActual));
    printf(entrada);
}

/*int main(){
    int i = 10;
    time_t horaActual = time(NULL);
    char e[] = "buscando memoria";
    char PID[10];
    char estado[30];
    char hora[50];
    char entrada[90];
    strcpy(PID, "PID: ");
    char* itoa(i, entrada, DECIMAL);
    //strcpy(entrada, "\n");
    sprintf(PID, "PID: %i, ", 10);
    sprintf(estado, "Estado: buscando memoria, ");
    sprintf(hora,"Hora: %s\n",ctime(&horaActual));
    sprintf(entrada, "PID: %i, Estado: %s, Hora: %s\n",i, e, ctime(&horaActual));
    printf(entrada); 
    abrirBitacora();
    cerrarBitacora();
    return 0;
}*/