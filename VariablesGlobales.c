#include<stdio.h>

enum estados{Espera, Ejecutado, Buscando, EnMemoria, Muerto};

typedef struct{
    int id, cantElementos, tiempoEjecucion;
    int *espacioElementos;
    int *registroBase;
    enum estados estado;

}proceso;