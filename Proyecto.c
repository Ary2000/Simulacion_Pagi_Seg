#include "ProgramaInicializador.c"
#include "ProductorProcesos.c"
#include "Bitacora.c"

int main() {
    inicializar();
    //abrirBitacora();
    pthread_t threadGenerarProcesos;
    pthread_create(&threadGenerarProcesos, NULL, generarProcesos, NULL);
    menu();
    pthread_join(threadGenerarProcesos,NULL);
    return 0;
}