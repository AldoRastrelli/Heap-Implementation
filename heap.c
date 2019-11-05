#include "heap.h"
#include <stdlib.h>
#define CAPACIDAD_INICIAL 20
#define CTE_INCREMENTO 2

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

void upheap(void** vector, size_t pos_elem, cmp_func_t cmp){
    if ((pos_elem) == 0) return;
    int pos_padre = (pos_elem-1)/2;
    if (cmp(vector[pos_elem],vector[pos_padre]) > 0){
        swap(vector,pos_padre,pos_elem);
        upheap(vector,pos_padre,cmp);
    }
}

bool heap_encolar(heap_t *heap, void *elem){
    if (!elem) return false;
    if (heap->cant == heap->tam){
        if (!heap_redimensionar(heap,aumentar_capacidad)) return false;
    }
    void** datos = heap->datos;
    datos[heap->cant] = elem;
    upheap(datos,heap->cant,heap->cmp);
    heap->cant++;
    return true;
}

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}