#ifndef _HEAP_H
#define _HEAP_H

#include "heap.h"
#include "testing.h"
#include <stddef.h>

void pruebas_heap_vacio(){
	heap_t* heap = heap_crear(NULL);

	print_test("heap_ver_max devuelve NULL para un heap vacío", heap_ver_max(heap) == NULL);
	print_test("heap_desencolar devuelve NULL para un heap vacío", heap_desencolar(heap) == NULL);
	print_test("heap_esta_vacio devuelve true para un heap vacío", heap_esta_vacio(heap));
	heap_destruir(heap,NULL);
}

static void prueba_heap_encolar()
{
    heap_t* heap = heap_crear(strcmp);

    char *dato1 = "perro";
    char *dato2 = "gato";
    char *dato3 = "vaca";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato1 es valor1", heap_ver_max(heap) == dato1);

    print_test("Prueba heap borrar dato1, es valor1", heap_desencolar(heap) == dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Inserta otros 3 valores y no los borra (se destruyen con el heap) */
    print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));	// gato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato2 es valor2", heap_ver_max(heap) == dato2);

    print_test("Prueba heap encolar dato3", heap_encolar(heap, dato1));	// perro
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver_max dato3 es valor3", heap_ver_max(heap) == dato1);

	print_test("Prueba heap ver_max dato3 es valor3", heap_ver_max(heap) == dato1);

	print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));	// vaca
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max dato3 es valor3", heap_ver_max(heap) == dato3);

    heap_destruir(heap);
}

static void prueba_heap_desencolar()
{
    heap_t* heap = heap_crear(strcmp);

    char *dato1 = "perro";
    char *dato2 = "gato";
    char *dato3 = "vaca";
	char *dato4 = "pato";

    /* Inserta 1, 2, 3 y 4 y prueba que el orden sea: vaca, perro, pato, gato */

    print_test("Prueba heap encolar dato1", heap_encolar(heap, dato1));	// perro
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver_max dato1 es valor1", heap_ver_max(heap) == dato1);

    print_test("Prueba heap encolar dato2", heap_encolar(heap, dato2));	// gato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver_max dato2 es valor2", heap_ver_max(heap) == dato1);

	print_test("Prueba heap encolar dato2", heap_encolar(heap, dato4));	// pato
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max dato2 es valor2", heap_ver_max(heap) == dato1);


	print_test("Prueba heap encolar dato3", heap_encolar(heap, dato3));	// vaca
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 3);
    print_test("Prueba heap ver_max dato3 es valor3", heap_ver_max(heap) == dato3);

	print_test("Prueba heap borrar dato1, es valor1", heap_desencolar(heap) == dato3);	// desencola vaca
	print_test("Prueba heap ver_max dato1 es valor1", heap_ver_max(heap) == dato1);		// max = perro
	print_test("Prueba heap borrar dato1, es valor1", heap_desencolar(heap) == dato1);	// desecola perro
	print_test("Prueba heap ver_max dato1 es valor1", heap_ver_max(heap) == dato4);		// max = pato
	print_test("Prueba heap borrar dato1, es valor1", heap_desencolar(heap) == dato4);	// desecola pato
	print_test("Prueba heap ver_max dato1 es valor1", heap_ver_max(heap) == dato2);		// max = gato
	print_test("Prueba heap borrar dato1, es valor1", heap_desencolar(heap) == dato2);	// desencola gato
	print_test("Prueba heap borrar dato1, es valor1", heap_esta_vacio(heap));			// está vacío

    heap_destruir(heap);
}

void pruebas_heap_alumno(){
	pruebas_heap_vacio();
	prueba_heap_encolar();
	prueba_heap_desencolar();
}

#endif