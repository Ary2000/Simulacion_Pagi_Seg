//#include "ProgramaInicializador.c"
//#include "ProductorProcesos.c"
//#include "Bitacora.c"
#include "ProgramaEspia.c"


void menu(){
    printf("********************\n");
    printf("1.TERMINAR EJECUCION\n");
    printf("2.PROGRAMA ESPIA    \n");
    printf("********************\n");
    int numTeclado;
    while(1){
        scanf("%d",&numTeclado);
        if(numTeclado==1){
            shmctl(bloque, IPC_RMID, NULL);
            cerrarBitacora();
            exit(EXIT_SUCCESS);
        }
        else if(numTeclado==2){
            estadoProcesos();
        }
    }
}

int main() {
    srand(time(NULL));
    inicializar();
    int numTeclado2=0;
    while(numTeclado2<1 || numTeclado2>2){
        printf("Cual tipo de algoritmo desea correr (1.Paginacion/2.Segmentacio)\n");
        scanf("%d",&numTeclado2);
        if(numTeclado2==2){
            paginacion=false;
        }
    }
    abrirBitacora();
    pthread_t threadGenerarProcesos;
    pthread_create(&threadGenerarProcesos, NULL, generarProcesos, NULL);
    menu();
    pthread_join(threadGenerarProcesos,NULL);
    return 0;
}