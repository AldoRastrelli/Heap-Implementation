#include "heap.h"
#include <stdlib.h>

struct heap{
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/***************************
* Primitivas del heap
****************************/

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
    if (destruir_elemento){
        for (int i = 0; i < heap->cant; i++){
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}