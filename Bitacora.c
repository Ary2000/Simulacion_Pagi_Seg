#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaProcesos.c"

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

    case Saliendo:
        strcpy(string, "solicitando semaforo para salir");
        break;
    
    case Muerto:
        strcpy(string, "muerto");
        break;
    default:
        strcpy(string, "esperando semaforo para entrar");
        break;
    }
}

//https://stackoverflow.com/questions/30234363/how-can-i-convert-an-int-array-into-a-string-array
void getPosiciones(char* string, proceso *p, enum estados estado){
    int tamanio = p->cantElementos * 5;
    char posiciones[tamanio];
    int indice = 0;
    switch (estado)
    {
    case EnMemoria:
        for (int i = 0; i < p->cantElementos-1; i++)
        {
            indice += snprintf(&posiciones[indice], tamanio-indice, "%d", p->registroBase[i]);
            indice += snprintf(&posiciones[indice], tamanio-indice, "%s", ",");
        }
        indice += snprintf(&posiciones[indice], tamanio-indice, "%d", p->registroBase[p->cantElementos-1]);
        sprintf(string, "Direcciones en memoria: [%s], ",posiciones);
        break;
    
    default:
        break;
    }
    /*int tamanio = p->cantElementos * 5;
    char posiciones[tamanio];
    int indice = 0;
    for (int i = 0; i < p->cantElementos-1; i++)
    {
        indice += snprintf(&posiciones[indice], tamanio-indice, "%d", p->registroBase[i]);
        indice += snprintf(&posiciones[indice], tamanio-indice, "%s", ",");
    }
    indice += snprintf(&posiciones[indice], tamanio-indice, "%d", p->registroBase[p->cantElementos-1]);
    sprintf(string, "Direcciones en memoria: [%s], ",posiciones);*/
}

void escribirBitacora(proceso *p){
    //PID, estado, espacio en memoria(si esta en memoria)/eliminado, hora
    time_t horaActual = time(NULL);
    char entrada[150];
    char estado[50];
    char pocisionesMem[40];
    memset(pocisionesMem, 0, sizeof(pocisionesMem));
    getEstado(estado, p->estado);
    /*if(p->estado == EnMemoria){
        getPosiciones(pocisionesMem, p);
    }*/
    getPosiciones(pocisionesMem, p, p->estado);
    sprintf(entrada, "PID: %i, Estado: %s, %s Hora: %s\n",p->id, estado, pocisionesMem, ctime(&horaActual));
    fprintf(archivo, entrada);
    //printf(entrada);
}

/*int main(){
    /*int i = 10;
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
    cerrarBitacora();*/
    /*int numeros[] = {2,4,6,18,49};
    int tamanio = 5*4;
    char posiciones[tamanio];
    int indice = 0;
    for (int i = 0; i < 5-1; i++)
    {
        indice += snprintf(&posiciones[indice], tamanio-indice, "%d", numeros[i]);
        indice += snprintf(&posiciones[indice], tamanio-indice, "%s", ",");
    }
    indice += snprintf(&posiciones[indice], tamanio-indice, "%d", numeros[5-1]);
    printf(posiciones);
    printf("\n");
    //////////////////////////
    abrirBitacora();
    proceso* p = malloc(sizeof(p));
    int elementos = 3;
    enum estados e = EnMemoria;
    p->id=4;
    p->estado = e;
    p->cantElementos = elementos;
    p->espacioElementos = calloc(elementos,sizeof(int));
    p->registroBase = calloc(elementos,sizeof(int));
    for (int i = 0; i < elementos; i++)
    {
        p->espacioElementos[i] = 1;
    }
    escribirBitacora(p);
    e = Saliendo;
    p->estado = e;
    escribirBitacora(p);
    cerrarBitacora();
    return 0;
}*/