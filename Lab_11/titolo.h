#ifndef TITOLO_H_DEFINED
#define TITOLO_H_DEFINED

#define LEN 100

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "quotation_collection.h"

typedef char *Key;
typedef struct TITOLO_Struct *Titolo;

void TITOLOprint(FILE *out, Titolo t);

int TITOLOcmp(Key t1, Key t2);

Key TITOLOgetKey(Titolo t);

Titolo TITOLOnew(char *cod);

void TITOLOaddTransaction(Titolo t, Date d, float valore, int qta);

float TITOLOmin(Titolo t);

float TITOLOmax(Titolo t);

void TITOLOinRangeminmax(Titolo t, Date d1, Date d2, float *f1, float *f2);

Quotation TITOLOquotation(Titolo t, Date d);

void TITOLOBalance(Titolo t);

#endif
