#ifndef _HEAP_H
#define _HEAP_H

#define VOLUMEN 20
#define TAM 10

#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/*
gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
*/

/**************************
 * Funciones Auxiliares
 * ***********************/

/* Wrapper de strcmp que recibe dos const void*/
int str_cmp(const void* a, const void* b){
	const char* str_a = a;
	const char* str_b = b;

	return strcmp(str_a, str_b);
}

int intcmp(const void* a, const void* b){
    if (*(int*)a > *(int*)b) return 1;
    else if (*(int*)a < *(int*)b) return -1;
    return 0;
}

void destruir_vector(int** vector, size_t n){
    for (size_t i = 0; i < n; i++){
        free(vector[i]);
    }
}

/***************************
 * Funciones de Pruebas
 * *************************/

static void pruebas_heap_vacio(){
	printf("\n**PRUEBAS HEAP VACÍO**\n");
	heap_t* heap = heap_crear(str_cmp);

	if (!heap)	return;
	print_test("heap_ver_max devuelve NULL para un heap vacío", heap_ver_max(heap) ==NULL);
	print_test("heap_desencolar devuelve NULL para un heap vacío", heap_desencolar(heap) == NULL);
	print_test("heap_esta_vacio devuelve true para un heap vacío", heap_esta_vacio(heap));
	
	heap_destruir(heap,NULL);
}

static void prueba_heap_encolar(){
	printf("\n**PRUEBAS ENCOLAR Y DESENCOLAR**\n");
    heap_t* heap = heap_crear(str_cmp);

    char dato1[5] = "gato";
	char dato2[5] = "perro";
    //char dato3[5] = "vaca";

    print_test("Prueba heap no se puede encolar NULL", !heap_encolar(heap, NULL));

    //Inserta 1 dato y luego lo borra
    print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == dato1);

    print_test("Prueba heap borrar dato1, es dato1", heap_desencolar(heap) == dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

	printf("\n");
    //Inserta otros 3 datos y no los borra (se destruyen con el heap)
    print_test("Prueba heap encolar dato2", heap_encolar(heap, &dato1));	// gato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato2 es dato2", heap_ver_max(heap) == &dato1);

    print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato2));	// perro
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    //print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == &dato1);
//
	//print_test("Prueba heap ver_max dato3 es dato3", heap_ver_max(heap) == &dato1);
//
	//print_test("Prueba heap encolar dato3", heap_encolar(heap, &dato3));	// vaca
    //print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    //print_test("Prueba heap ver_max dato3 es dato3", heap_ver_max(heap) == &dato3);

    heap_destruir(heap,NULL);
}
/*
static void prueba_heap_desencolar(){
	
    heap_t* heap = heap_crear(str_cmp);

    void *dato1 = "perro";
    void *dato2 = "gato";
    void *dato3 = "vaca";
	void *dato4 = "pato";

    // Inserta 1, 2, 3 y 4 y prueba que el orden sea: vaca, perro, pato, gato

    print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato1));	// perro
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == &dato1);

    print_test("Prueba heap encolar dato2", heap_encolar(heap, &dato2));	// gato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver_max dato2 es dato2", heap_ver_max(heap) == &dato1);

	print_test("Prueba heap encolar dato2", heap_encolar(heap, &dato4));	// pato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max dato2 es dato2", heap_ver_max(heap) == &dato1);


	print_test("Prueba heap encolar dato3", heap_encolar(heap, &dato3));	// vaca
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max dato3 es dato3", heap_ver_max(heap) == &dato3);

	print_test("Prueba heap borrar dato1, es dato1", heap_desencolar(heap) == dato3);	// desencola vaca
	print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == &dato1);		// max = perro
	print_test("Prueba heap borrar dato1, es dato1", heap_desencolar(heap) == dato1);	// desecola perro
	print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == &dato4);		// max = pato
	print_test("Prueba heap borrar dato1, es dato1", heap_desencolar(heap) == dato4);	// desecola pato
	print_test("Prueba heap ver_max dato1 es dato1", heap_ver_max(heap) == &dato2);		// max = gato
	print_test("Prueba heap borrar dato1, es dato1", heap_desencolar(heap) == dato2);	// desencola gato
	print_test("Prueba heap borrar dato1, es dato1", heap_esta_vacio(heap));			// está vacío

    heap_destruir(heap, NULL);
} */

static void pruebas_heap_volumen(){
    heap_t* heap = heap_crear(intcmp);
    int* vector[VOLUMEN];
    bool ok = true;

    for (int i = VOLUMEN-1; i >= 0 && ok; i--){
        int* p = malloc(sizeof(int*));
        *p = i/2;
        vector[i] = p;
        ok = heap_encolar(heap,p);
    }

    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == VOLUMEN);

    for (int j = VOLUMEN-1; j >= 0 && ok; j--){
        int* q = heap_desencolar(heap);
        ok = (intcmp(q,vector[j]) == 0);
    }

    print_test("Prueba heap desencolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    destruir_vector(vector,VOLUMEN);
    heap_destruir(heap,NULL);
}

void pruebas_heap_alumno(){
	pruebas_heap_vacio();
	prueba_heap_encolar();
	//prueba_heap_desencolar();
    pruebas_heap_volumen();

}

#endif