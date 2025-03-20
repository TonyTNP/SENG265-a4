/**
 * @file emalloc.c
 * @brief A safe wrapper for memory allocation functions.
 * 
 * This module provides a safer alternative to `malloc()` by ensuring 
 * that memory allocation failures are properly handled.
 * 
 * @author Ashton Majachani
 * @date March 20, 2025
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include "emalloc.h"
 
 /**
  * @brief Allocates memory safely, terminating if allocation fails.
  * 
  * This function is a wrapper for `malloc()`, ensuring that if memory 
  * allocation fails, the program exits gracefully.
  * 
  * @param n Size in bytes to allocate.
  * @return void* Pointer to allocated memory.
  */
 void *emalloc(size_t n) {
     void *p = malloc(n);
     if (p == NULL) {
         fprintf(stderr, "Error: malloc of %zu bytes failed\n", n);
         exit(1);
     }
     return p;
 }
 