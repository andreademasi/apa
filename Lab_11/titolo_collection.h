#ifndef TITOLI_COLLECTION_H_DEFINED
#define TITOLI_COLLECTION_H_DEFINED
#define LEN 100

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "titolo.h"

typedef struct titoli_collection_struct *titoli_collection;

int Empty_TitoliCollection(titoli_collection titoli);

Titolo Search_TitoliCollection(titoli_collection titoli, char *cod);

void Insert_TitoliCollection(titoli_collection titoli, Titolo t);

titoli_collection Init_TitoliCollection();

#endif
