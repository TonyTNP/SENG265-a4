/**
 * @file emalloc.h
 * @brief Header file for safe memory allocation functions.
 * 
 * This file declares a safer version of `malloc()` for use in dynamic 
 * memory allocation.
 * 
 * @author Ashton Majachani
 * @date March 20, 2025
 */

 #ifndef _EMALLOC_H_
 #define _EMALLOC_H_
 
 #include <stdlib.h>
 
 /**
  * @brief Allocates memory safely.
  * 
  * @param n Number of bytes to allocate.
  * @return void* Pointer to allocated memory.
  */
 void *emalloc(size_t n);
 
 #endif
 