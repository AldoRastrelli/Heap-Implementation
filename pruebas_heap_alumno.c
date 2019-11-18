#define VOLUMEN 1000
#define TAM 10
#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int stringcmp(const void* a, const void* b){
    return strcmp(a,b);
}

int _intcmp(int a, int b){
    if (a > b) return 1;
    else if (a < b) return -1;
    return 0;  
}

int intcmp(const void* a, const void* b){
    return _intcmp(*(int*)a,*(int*)b);
}

void destruir_vector(void** vector, size_t n){
    for (size_t i = 0; i < n; i++){
        free(vector[i]);
    }
}

static void pruebas_heap_vacio(){
	heap_t* heap = heap_crear(NULL);

	print_test("Prueba heap vacío está vacío", heap_esta_vacio(heap));
	print_test("Prueba heap vacío ver_max devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba heap vacío desencolar devuelve NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap vacío la cantidad de elementos es 0", heap_cantidad(heap) == 0);
	heap_destruir(heap,NULL);
}

static void prueba_heap_insertar(){
    heap_t* heap = heap_crear(stringcmp);

    char* dato1 = "aaa";
    char* dato2 = "ggg";
    char* dato3 = "zzz";

    print_test("Prueba heap no se puede encolar NULL", !heap_encolar(heap, NULL));

    /* Inserta 1 dato y luego lo borra */
    print_test("Prueba heap insertar dato1", heap_encolar(heap, dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap el maximo es dato1", heap_ver_max(heap) == dato1);
    print_test("Prueba heap desencolar, es dato1", heap_desencolar(heap) == dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Inserta otros 2 datos y no los borra (se destruyen con el heap) */
    print_test("Prueba heap insertar dato2", heap_encolar(heap, dato2));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap el maximo es dato2", heap_ver_max(heap) == dato2);

    print_test("Prueba heap insertar dato3", heap_encolar(heap, dato3));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 1);
    print_test("Prueba heap el maximo es dato3", heap_ver_max(heap) == dato3);

    heap_destruir(heap,NULL);
}

static void pruebas_heap_volumen(){
    heap_t* heap = heap_crear(intcmp);
    int* vector[VOLUMEN];
    bool ok = true;

    for (int i = VOLUMEN; i >= 0 && ok; i--){
        int* p = malloc(sizeof(int*));
        *p = i/2;
        vector[i] = p;
        ok = heap_encolar(heap,p);
    }
    
    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == VOLUMEN);

    for (int j = VOLUMEN; j >= 0 && ok; j--){
        int* q = heap_desencolar(heap);
        ok = (q == vector[j]);
        free(q);
    }

    print_test("Prueba heap desencolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap,NULL);
}

static void pruebas_heapsort(){
    void* vector[TAM];

    for (int i = 0; i < TAM; i++){
        int* p = malloc(sizeof(int*));
        *p = rand();
        vector[i] = p;
    }

    heap_sort(vector,TAM,intcmp);
    int actual = *(int*)vector[0];
    bool ok = true;

    for (int j = 1; j < TAM; j++){
        if (*(int*)vector[j] < actual) ok = false;
        actual = *(int*)vector[j];
    }

    print_test("Prueba heapsort ordena un arreglo", ok);

    destruir_vector(vector,TAM);    
}

void pruebas_heap_alumno(){
    srand((unsigned int)time(NULL));
	pruebas_heap_vacio();
    prueba_heap_insertar();
    pruebas_heap_volumen();
    pruebas_heapsort();
}
