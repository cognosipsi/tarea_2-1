#ifndef __defined_hashmap_h
#define __defined_hashmap_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;

Pair * createPair( char * key,  void * value);

long hash( char * key, long capacity);

int is_equal(void* key1, void* key2);

void enlarge(HashMap * map);

void insertMap(HashMap * map, char * key, void * value);

void enlarge(HashMap * map);

HashMap * createMap(long capacity);

void eraseMap(HashMap * map,  char * key);

void * searchMap(HashMap * map,  char * key);

void * firstMap(HashMap * map);

void * nextMap(HashMap * map);

#endif /* __defined_hashmap_h */
