#ifndef PROGRAMAINICIALIZADOR_C
#define PROGRAMAINICIALIZADOR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#include "VariablesGlobales.c"

#define IPC_RESULT_ERROR (-1)

#define CEROS ("\000\000\000\000\000\000\000\000\000\000")
#define UNOS ("111111111111111111111111111111")
#define DOS ("22222222222222222222222222222")

int tamanoMemoria = 0;
char* memoriaCompartida;
pthread_mutex_t lockMemoria;

// Buscar referencia 
int isNumber(char s[]) {
    for(int i = 0; s[i] != '\0'; i++){ 
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}

static int obtener_memoria_compartida(char *nombre_archivo, int tamano){
    key_t llave;

    llave = ftok(nombre_archivo, 0);
    if(llave == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    return shmget(llave, tamano, 0644 | IPC_CREAT);
}

int pedirTamanoMemoria() {
    char inputMemoria[20]; 
        while(true){
            printf("Insertar el tamano de la memoria compartida: ");
            fgets(inputMemoria, sizeof inputMemoria, stdin);
            char* posicionNulo1;

            if((posicionNulo1 = strchr(inputMemoria, '\n')) != NULL) {
                *posicionNulo1 = '\0';
            }

            if(isNumber(inputMemoria) == 0) {
                printf("Input no es valido, por favor solo insertar numeros\n");
            }
            else 
                return atoi(inputMemoria);
        }
}

bool eliminarEnLaMemoria(char* memoriaCompartida, int tamMemoria, int* registrosBase, int* tamProcesos, int cantidadProcesos) {
    pthread_mutex_lock(&lockMemoria);
    for(int i = 0; i < cantidadProcesos; i++) {
        strncpy(memoriaCompartida + registrosBase[i], CEROS, tamProcesos[i]);
    }
    pthread_mutex_unlock(&lockMemoria);
    return true;
}

// Este programa revisa que haya suficiente espacio para insertar un peso del tamano
// presente en la variable cantidadNecesaria
// Los argumentos son:
//                      memoriaCompartida: Puntero a la memoria compartida
//                      tamMemoria: La cantidad de bytes de la memoria compartida
//                      tamProcesos: Tamano de todos los procesos
void *buscarEnLaMemoria(void *args) {
    pthread_mutex_lock(&lockMemoria);
    proceso *procesoEnBusqueda = args;
    int contadorEspaciosLibres = 0;
    int indiceElemento = 0;
    bool hayEspacio = false;
    for(int contadorMemCompartida = 0; contadorMemCompartida < tamanoMemoria; contadorMemCompartida++) {
        if(memoriaCompartida[contadorMemCompartida] == 0) {
            contadorEspaciosLibres++;
            if(contadorEspaciosLibres == procesoEnBusqueda->espacioElementos[indiceElemento]) {
                strncpy(memoriaCompartida + contadorMemCompartida - (procesoEnBusqueda->espacioElementos[indiceElemento] - 1), DOS, procesoEnBusqueda->espacioElementos[indiceElemento]); // Copia el string en la memoria compartida
                procesoEnBusqueda->registroBase[indiceElemento] = contadorMemCompartida - (procesoEnBusqueda->espacioElementos[indiceElemento] - 1);
                indiceElemento++;
                if(indiceElemento == procesoEnBusqueda->cantElementos){
                    hayEspacio = true;
                    break;
                }

                contadorEspaciosLibres = 0;
                contadorMemCompartida = -1;
            }
        }
        else{
            contadorEspaciosLibres = 0;
        }
    }
    
    char charRemplazo = 0;
    if(hayEspacio == true)
    // El proceso fue asignado
        charRemplazo = '1';
    else
        procesoEnBusqueda->registroBase[0] = -1;

    for(int contadorMemCompartida = 0; contadorMemCompartida < tamanoMemoria; contadorMemCompartida++) {
        if(memoriaCompartida[contadorMemCompartida] == '2')
            memoriaCompartida[contadorMemCompartida] = charRemplazo;
    }
    pthread_mutex_unlock(&lockMemoria);
    sleep(procesoEnBusqueda->tiempoEjecucion);
    //eliminarEnLaMemoria();
}

int inicializar(){
    tamanoMemoria = pedirTamanoMemoria();
    pthread_mutex_init(&lockMemoria, NULL);

    // Pide el bloque de memoria compartida
    int bloque = obtener_memoria_compartida("ProgramaInicializador.c", tamanoMemoria); 
    //shmctl(bloque, IPC_RMID, NULL);
    if(bloque == IPC_RESULT_ERROR){
        return IPC_RESULT_ERROR;
    }
    // Mapea los contenidos de la memoria compartida para que esten en formato de char*
    memoriaCompartida = shmat(bloque, NULL, 0);
    //      Base+offset, string a insertar, tamano del string a insertar
    //strncpy(contenido_bloque_memoria + 1, "ol", 2); // Copia el string en la memoria compartida
    //shmdt(contenido_bloque_memoria);

    return 0;
}
#endif