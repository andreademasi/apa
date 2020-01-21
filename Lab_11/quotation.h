#ifndef QUOTATION_H_DEFINED
#define QUOTATION_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "date.h"

typedef struct Quotation_struct {
    Date data;
    float num; // numero di titoli scambiati * valore (numeratore)
    int den; // numero di titoli scambiati (denominatore)
} Quotation;


void QUOTATIONprint(FILE *fp, Quotation q);

float QUOTATIONgetValue(Quotation q);

Date QUOTATIONgetDate(Quotation q);

int QUOTATIONcheckNull(Quotation q);

Quotation QUOTAZIONEsetNull();

#endif
