#ifndef QUOTATION_COLLECTION_H_DEFINED
#define QUOTATION_COLLECTION_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "date.h"
#include "quotation.h"

#define S 2.0

typedef struct binarysearchtree *BSTquotazioni;

int BSTEmpty(BSTquotazioni bst);

Quotation BSTSearch(BSTquotazioni bst, Date d);

void BSTInsert_leafR(BSTquotazioni bst, Date d, float val, int qta);

void BSTMinmaxRange(BSTquotazioni bst, Date d1, Date d2, float *f1, float *f2);

BSTquotazioni BSTInit();

void BSTprint(BSTquotazioni bst, FILE *fp);

void BSTbalance(BSTquotazioni bst);

void BSTgetMinMax(BSTquotazioni bst, float *min, float *max);

#endif
