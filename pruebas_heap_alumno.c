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

void pruebas_heap_alumno(){
	pruebas_heap_vacio();
}