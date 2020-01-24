#ifndef DATE_H_DEFINED
#define DATE_H_DEFINED
#define DATELEN 11

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct data_ {
    int aaaa, mm, gg;
} Date;

Date DATEload(char *s);

int DATEcmp(Date d1, Date d2);

void DATEprint(Date d, FILE *fp);

#endif
