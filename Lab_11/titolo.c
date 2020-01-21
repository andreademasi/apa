#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "titolo.h"

struct TITOLO_Struct {
    Key code;
    float min, max;
    BSTquotazioni bstQuotazioni;
};

void TITOLOprint(FILE *out, Titolo t) {
    fprintf(out, "%s QUOTAZIONE MIN = %f / MAX = %f\n", t->code, t->min, t->max);
    BSTprint(t->bstQuotazioni, out);
}

int TITOLOcmp(Key t1, Key t2) {
    return strcmp((char *) t1, (char *) t2);
}

Key TITOLOgetKey(Titolo t) {
    return t->code;
}

Titolo TITOLOnew(char *cod) {
    Titolo t = malloc(sizeof *t);
    t->code = (Key) strdup(cod);
    t->min = t->max = -1.0;
    t->bstQuotazioni = BSTInit();
    return t;
}

static void updateMinmax(Titolo t) {
    float min = -1.0, max = -1.0;
    BSTgetMinMax(t->bstQuotazioni, &min, &max);
    t->min = min;
    t->max = max;
}

void TITOLOinsertTransazione(Titolo t, Date d, float val, int qta) {
    BSTInsert_leafR(t->bstQuotazioni, d, val, qta);
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

static void valRange(Titolo t, Date d1, Date d2, float *f1, float *f2) {
    BSTMinmaxRange(t->bstQuotazioni, d1, d2, f1, f2);
}

void TITOLOinRangeminmax(Titolo t, Date d1, Date d2, float *f1, float *f2) {
    int cmp = DATEcmp(d1, d2);
    if (cmp < 0)
        valRange(t, d1, d2, f1, f2);
    else if (cmp > 0)
        valRange(t, d2, d1, f1, f2);
    else
        *f1 = *f2 = QUOTATIONgetValue(BSTSearch(t->bstQuotazioni, d1));
}

Quotation TITOLOgetQuotazione(Titolo t, Date d) {
    if (t == NULL || t->bstQuotazioni == NULL)
        return QUOTAZIONEsetNull();
    return BSTSearch(t->bstQuotazioni, d);
}

void TITOLOtreeBalance(Titolo t) {
    if (t == NULL || t->bstQuotazioni == NULL)
        return;
    BSTbalance(t->bstQuotazioni);
}
