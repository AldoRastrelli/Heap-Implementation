#include "heap.h"
#include <stdlib.h>

struct heap{
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};