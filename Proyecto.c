#include "ProgramaInicializador.c"
#include "ProductorProcesos.c"

int main() {
    inicializar();
    pthread_t threadGenerarProcesos;
    pthread_create(&threadGenerarProcesos, NULL, generarProcesos, NULL);
    menu();
    pthread_join(threadGenerarProcesos,NULL);
    return 0;
}