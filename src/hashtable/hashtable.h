#ifndef _HASHTABLE_INCLUDED
#define _HASHTABLE_INCLUDED

#define _GNU_SOURCE
#include <stdio.h>   /* fprintf */ // ( Crude logging but logging nonetheless )
#include <stdlib.h>  
#include <string.h> /* strcmp */
#include <math.h>   /* Ceilf */
#include <ctype.h> 

#define LOAD_FACTOR_THRESHOLD 0.9
#define T htbl_T
typedef struct T *T;

/**
 * @brief Mallocs into existence a hashtable with an initial capacity of \p capacity
 * 
 * @param capacity 
 * @return T Null if error, struct T otherwise.
 */
T htbl_new(const unsigned int capacity);

/**
 * @brief Nullifies table entries, frees underlying pointer of \p htbl and sets to NULL 
 * 
 * @param tbl Adress of the pointer to hashtable to free
 */
void htbl_free(T *tbl);

/**
 * @brief 
 * 
 * @param tbl Table to add key -> value mapping.
 * @param key string to associate \p item with.
 * @param item Pointer to item
 * @return int 1 if item was added, 0 if item was updated.
 */
int  htbl_put(T tbl, const char *key, void *item);

/**
 * @brief 
 * 
 * @param table 
 * @param key 
 * @return void* Pointer to item with \p key. Null if does not exist
 */
void* htbl_find(T tbl, const char *key);

/**
 * @brief 
 * 
 * @param tbl Table to remove mapping from.
 * @param key String of mapping to remove from \p table
 * @return void* of value removed on success otherwise NULL.
 */
void* htbl_remove(T tbl, const char *key);

/**
 * @brief Returns the \p table's capacity
 * 
 * @param tbl 
 * @return unsigned int representing size of hashtable
 * 
 */
unsigned int htbl_capacity(const T tbl);


#undef T

#endif