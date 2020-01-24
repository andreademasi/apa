#ifndef QUOTATION_COLLECTION_H_DEFINED
#define QUOTATION_COLLECTION_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "date.h"
#include "quotation.h"

#define S 2.0

typedef struct binarysearchtree *BSTquotations;

int BSTEmpty(BSTquotations bst);

Quotation BSTSearch(BSTquotations bst, Date d);

void BSTInsert_leafR(BSTquotations bst, Date d, float val, int qta);

void BSTMinmaxRange(BSTquotations bst, Date d1, Date d2, float *f1, float *f2);

BSTquotations BSTInit();

void BSTprint(BSTquotations bst, FILE *fp);

void BSTbalance(BSTquotations bst);

void BSTMinMax(BSTquotations bst, float *min, float *max);

#endif
