#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "titolo.h"

struct TITOLO_Struct {
    Key code;
    float min, max;
    BSTquotations quotationsBST;
};

void TITOLOprint(FILE *out, Titolo t) {
    fprintf(out, "%s QUOTAZIONE MIN = %f / MAX = %f\n", t->code, t->min, t->max);
    BSTprint(t->quotationsBST, out);
}

int TITOLOcmp(Key t1, Key t2) {
    return strcmp((char *) t1, (char *) t2);
}

Key TITOLOgetKey(Titolo t) {
    return t->code;
}

Titolo TITOLOnew(char *cod) {
    Titolo t = calloc(1, sizeof *t);
    t->code = (Key) strdup(cod);
    t->min = t->max = -1;
    t->quotationsBST = BSTInit();
    return t;
}

static void updateMinmax(Titolo t) {
    float min = -1, max = -1;
    BSTMinMax(t->quotationsBST, &min, &max);
    t->min = min;
    t->max = max;
}

void TITOLOaddTransaction(Titolo t, Date d, float valore, int qta) {
    BSTInsert_leafR(t->quotationsBST, d, valore, qta);
    updateMinmax(t);
}

float TITOLOmin(Titolo t) {
    if (t == NULL)
        return -1;
    return t->min;
}

float TITOLOmax(Titolo t) {
    if (t == NULL)
        return -1;
    return t->max;
}

void TITOLOinRangeminmax(Titolo t, Date d1, Date d2, float *f1, float *f2) {
    if (DATEcmp(d1, d2) == 0) {
        *f1 = *f2 = QUOTATIONgetValue(BSTSearch(t->quotationsBST, d1));
        return;
    }
    BSTMinmaxRange(t->quotationsBST, d1, d2, f1, f2);
}

Quotation TITOLOquotation(Titolo t, Date d) {
    if (t == NULL || t->quotationsBST == NULL)
        return QUOTATIONsetNull();
    return BSTSearch(t->quotationsBST, d);
}

void TITOLOBalance(Titolo t) {
    if (t == NULL || t->quotationsBST == NULL)
        return;
    BSTbalance(t->quotationsBST);
}
