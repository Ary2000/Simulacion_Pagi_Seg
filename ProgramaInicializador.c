#ifndef PROGRAMAINICIALIZADOR_C
#define PROGRAMAINICIALIZADOR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#define IPC_RESULT_ERROR (-1)

#define UNOS ("111111111111111111111111111111")
#define DOS ("22222222222222222222222222222")

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

// Este programa revisa que haya suficiente espacio para insertar un peso del tamano
// presente en la variable cantidadNecesaria
// Los argumentos son:
//                      memoriaCompartida: Puntero a la memoria compartida
//                      tamMemoria: La cantidad de bytes de la memoria compartida
//                      tamProcesos: Tamano de todos los procesos
bool buscarEnLaMemoria(char* memoriaCompartida, int tamMemoria, int* tamProcesos, int cantidadProcesos) {
    int contadorEspaciosLibres = 0;
    int indiceElemento = 0;
    bool hayEspacio = false;
    for(int contadorMemCompartida = 0; contadorMemCompartida < tamMemoria; contadorMemCompartida++) {
        if(memoriaCompartida[contadorMemCompartida] == '0') {
            contadorEspaciosLibres++;
            if(contadorEspaciosLibres == tamProcesos[indiceElemento]) {
                strncpy(memoriaCompartida + contadorMemCompartida - (tamProcesos[indiceElemento] - 1), DOS, tamProcesos[indiceElemento]); // Copia el string en la memoria compartida
                indiceElemento++;
                if(indiceElemento == cantidadProcesos){
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
    for(int contadorMemCompartida = 0; contadorMemCompartida < tamMemoria; contadorMemCompartida++) {
        if(memoriaCompartida[contadorMemCompartida] == '2')
            memoriaCompartida[contadorMemCompartida] = '0';
    }
    return hayEspacio;
}

bool insertarEnLaMemoria(char* memoriaCompartida, int tamMemoria, int* tamProcesos, int cantidadProcesos) {
    int contadorEspaciosLibres = 0;
    int indiceElemento = 0;
    for(int contadorMemCompartida = 0; contadorMemCompartida < tamMemoria; contadorMemCompartida++) {
        if(memoriaCompartida[contadorMemCompartida] == '0') {
            contadorEspaciosLibres++;
            if(contadorEspaciosLibres == tamProcesos[indiceElemento]) {
                strncpy(memoriaCompartida + contadorMemCompartida - (tamProcesos[indiceElemento] - 1), UNOS, tamProcesos[indiceElemento]); // Copia el string en la memoria compartida
                indiceElemento++;
                if(indiceElemento == cantidadProcesos)
                    return true;

                contadorEspaciosLibres = 0;
                contadorMemCompartida = -1;
            }
        }
        else{
            contadorEspaciosLibres = 0;
        }
    }
    return false;
}

int main(){
    //int tamanoMemoria = pedirTamanoMemoria();
    int tamanoMemoria = 10;

    // Pide el bloque de memoria compartida
    //int bloque = obtener_memoria_compartida("ProgramaInicializador.c", tamanoMemoria); 
    //if(bloque == IPC_RESULT_ERROR){
    //    return IPC_RESULT_ERROR;
    //}
    // Mapea los contenidos de la memoria compartida para que esten en formato de char*
    //char *contenido_bloque_memoria = shmat(bloque, NULL, 0);
    //      Base+offset, string a insertar, tamano del string a insertar
    //strncpy(contenido_bloque_memoria + 1, "ol", 2); // Copia el string en la memoria compartida

    char contenido_bloque_memoria[] = {'0', '1', '1', '1', '0'};
    int procesos[] = {2, 1};
    bool hayEspacio = buscarEnLaMemoria(contenido_bloque_memoria, sizeof(contenido_bloque_memoria) / sizeof(char), procesos, sizeof(procesos) / sizeof(int));
    if(hayEspacio == true);{
        insertarEnLaMemoria(contenido_bloque_memoria, sizeof(contenido_bloque_memoria) / sizeof(char), procesos, sizeof(procesos) / sizeof(int));
    }

    shmdt(contenido_bloque_memoria);

    return 0;
}
#endif