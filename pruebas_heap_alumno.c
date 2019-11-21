#ifndef _HEAP_H
#define _HEAP_H

#define VOLUMEN 20
#define TAM 10
#define _POSIX_C_SOURCE 200809L 
#define MAX_RAND 10
#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c -lm
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

void destruir_vector(void** vector, size_t n){
    //for (size_t i = 0; i < n; i++){
    //    free(vector[i]);
    //}
    free(vector);
}

/***************************
 * Funciones de Pruebas
 * *************************/
/*
static void pruebas_heap_vacio(){
	printf("\n**PRUEBAS HEAP VACÍO**\n");
	heap_t* heap = heap_crear(str_cmp);

	if (!heap)	return;
	print_test("heap_ver_max devuelve NULL para un heap vacío", heap_ver_max(heap) ==NULL);
	print_test("heap_desencolar devuelve NULL para un heap vacío", heap_desencolar(heap) == NULL);
	print_test("heap_esta_vacio devuelve true para un heap vacío", heap_esta_vacio(heap));
	
	heap_destruir(heap,NULL);
}

static void prueba_heap_encolar_desencolar(){
	printf("\n**PRUEBAS ENCOLAR Y DESENCOLAR**\n");
    heap_t* heap = heap_crear(str_cmp);

    char dato1[4] = "gato";
	char dato2[5] = "perro";
    char dato3[4] = "vaca";
    char dato4[6] = "iguana";

    print_test("Prueba heap no se puede encolar NULL", !heap_encolar(heap, NULL));

    //Inserta 1 dato y luego lo borra
    print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max es dato1", heap_ver_max(heap) == dato1);

    print_test("Prueba heap borrar es dato1", heap_desencolar(heap) == dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

	printf("\n");
    //Inserta otros 3 datos y no los borra (se destruyen con el heap)
    print_test("Prueba heap encolar dato1", heap_encolar(heap, &dato1));	// gato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max es dato1", heap_ver_max(heap) == dato1);

    print_test("Prueba heap encolar dato2", heap_encolar(heap, &dato2));	// perro
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver_max es dato2", heap_ver_max(heap) == dato2);

	print_test("Prueba heap encolar dato3", heap_encolar(heap, &dato3));	// vaca
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max es dato3", heap_ver_max(heap) == dato3);

    print_test("Prueba heap encolar dato3", heap_encolar(heap, &dato4));	// iguana
    print_test("Prueba heap la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba heap ver_max sigue siendo dato3", heap_ver_max(heap) == dato3);

    print_test("Prueba heap borrar es dato3", heap_desencolar(heap) == dato3);	// desencola vaca
	print_test("Prueba heap ver_max es dato2", heap_ver_max(heap) == dato2);		// max = perro
	print_test("Prueba heap borrar es dato2", heap_desencolar(heap) == dato2);	// desencola perro
	print_test("Prueba heap ver_max es dato4", heap_ver_max(heap) == dato4);		// max = iguana
	print_test("Prueba heap borrar es dato4", heap_desencolar(heap) == dato4);	// desencola iguana
	print_test("Prueba heap ver_max es dato1", heap_ver_max(heap) == dato1);		// max = gato
	print_test("Prueba heap borrar es dato1", heap_desencolar(heap) == dato1);	// desencola gato
	print_test("Prueba heap esta_vacio", heap_esta_vacio(heap));			// está vacío

    heap_destruir(heap,NULL);
}
*/
static void pruebas_heap_volumen(){
	printf("\n**PRUEBAS VOLUMEN**\n");
    heap_t* heap = heap_crear(intcmp);
    void** vector = malloc(sizeof(void*) * VOLUMEN);
    bool ok = true;

    for (int i = VOLUMEN-1; i >= 0 && ok; i--){
        //int* p = malloc(sizeof(int));
        int entero = rand() % MAX_RAND;
        if (!entero)    entero++;       // si entero = 0, suma 1 para poder dividir
        int dato = (int) pow(i/entero, entero);
        int* p = &dato;
        printf("dato = %d\n",dato);
        vector[i] = &dato;
        ok = heap_encolar(heap,p);
    }

    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == VOLUMEN);

    heap_sort(vector,VOLUMEN,intcmp);

    for (int j = 0 ; j <VOLUMEN && ok; j++){
        printf("ingresa\n");
        int* q = heap_desencolar(heap);
        printf("desencolado: %d, vector[j] = %d\n",*q,*(int*)vector[VOLUMEN-1-j]);
        //ok = (intcmp(q,&vector[j]) == 0);
    }

    print_test("Prueba heap desencolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap,NULL);
    destruir_vector(vector,VOLUMEN);
}
/*
static void pruebas_heapsort(){
    printf("\n**PRUEBAS HEAPSORT**\n");

    void** vector = malloc(sizeof(void*)*TAM);

    for (int i = 0; i < TAM; i++){
        int* p = malloc(sizeof(int*));
        *p = rand()%TAM;
        vector[i] = p;
    }

    heap_sort(vector,TAM,intcmp);
    int actual = *(int*)vector[0];
    bool ok = true;

    for (int j = 1; j < TAM; j++){
        int a = *(int*)vector[j];
        if (a < actual) ok = false;
        actual = *(int*)vector[j];
    }

    print_test("Prueba heapsort ordena un arreglo", ok);

    destruir_vector(vector,TAM); 
}

static void pruebas_heap_arreglo(){
    printf("\n**PRUEBAS HEAP ARREGLO**\n");

    void** vector = malloc(sizeof(void*)*TAM);

    for (int i = 0; i < TAM; i++){
        int* p = malloc(sizeof(int*));
        *p = rand()%TAM;
        vector[i] = p;
    }

    heap_t* heap_a = heap_crear_arr(vector,TAM,intcmp);

    print_test("Prueba heap creado con un arreglo, tiene el tamaño correcto", heap_cantidad(heap_a) == TAM);
    
    heap_t* heap_b = heap_crear(intcmp);
    
    for (int i = 0; i < TAM; i++){
        heap_encolar(heap_b,vector[i]);
    }

    bool ok = true;

    while (!(heap_esta_vacio(heap_a) || heap_esta_vacio(heap_b))){
        ok = heap_desencolar(heap_a) == heap_desencolar(heap_b);
    }

    print_test("Prueba heap creado con un arreglo, se comporta como un heap", ok);

    heap_destruir(heap_a,NULL);
    heap_destruir(heap_b,NULL);
    destruir_vector(vector,TAM);
}
*/
void pruebas_heap_alumno(){
    //srand((unsigned int)time(NULL));
	//pruebas_heap_vacio();
	//prueba_heap_encolar_desencolar();
    pruebas_heap_volumen();
    //pruebas_heapsort();
    //pruebas_heap_arreglo();
}

#endif