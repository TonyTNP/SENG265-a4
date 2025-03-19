#include <stdlib.h>
#include <stdio.h>
#include "emalloc.h"

/**
 * Function:  emalloc
 * --------------------
 * @brief Represents a wrapper to malloc to use it in a safer way.
 */
void *emalloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "malloc of %zu bytes failed\n", n);
        exit(1);
    }

    return p;
}
