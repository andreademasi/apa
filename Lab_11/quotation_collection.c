#include <stdlib.h>
#include <stdio.h>

#include "quotation_collection.h"

typedef struct BSTnode *link;
struct BSTnode {
    link l, r;
    Quotation q;
    int count;
};
struct binarysearchtree {
    link root;
    int count;
};

BSTquotations BSTInit() {
    BSTquotations bst = calloc(1, sizeof *bst);
    return bst;
}

int BSTEmpty(BSTquotations bst) {
    if (bst == NULL || bst->root == 0)
        return 1;
    return 0;
}

static Quotation searchR(link h, Date d) {
    int cmp;
    if (h == NULL)
        return QUOTATIONsetNull();
    cmp = DATEcmp(d, QUOTATIONgetDate(h->q));
    if (cmp == 0)
        return h->q;
    else if (cmp < 0)
        return searchR(h->l, d);
    else
        return searchR(h->r, d);
}

Quotation BSTSearch(BSTquotations bst, Date d) {
    return searchR(bst->root, d);
}

static link NEW(Date d, float val, int amount, link left, link right) {
    link l = calloc(1, sizeof *l);
    l->q.data = d;
    l->q.num = val * amount;
    l->q.den = amount;
    l->l = left;
    l->r = right;
    l->count = 1;
    return l;
}

static void minmax(link h, float *min, float *max) {
    float q = QUOTATIONgetValue(h->q);

    if (*min < 0 || *min > q)
        *min = q; // salvo il minimo
    if (*max < 0 || *max < q)
        *max = q; // salvo il massimo
    if (h->r != NULL)
        minmax(h->r, min, max);
    if (h->l != NULL)
        minmax(h->l, min, max);
}

void BSTMinMax(BSTquotations bst, float *min, float *max) {
    if (BSTEmpty(bst))
        return;
    minmax(bst->root, min, max);
}

static link insertR(link h, Date d, float val, int amount, int *add) {
    int cmp;
    if (h == NULL) {
        *add = 1;
        return NEW(d, val, amount, NULL, NULL);
    }
    cmp = DATEcmp(d, QUOTATIONgetDate(h->q));
    if (cmp < 0)
        h->l = insertR(h->l, d, val, amount, add);
    else if (cmp > 0)
        h->r = insertR(h->r, d, val, amount, add);
    else {
        h->q.num += (h->q.num + amount * val);
        h->q.den += amount;
    }
    if (*add)
        h->count++; // se è stato aggiunto un nuovo nodo aumento il conteggio
    return h;
}

void BSTInsert_leafR(BSTquotations bst, Date d, float val, int qta) {
    int add = 0;
    bst->root = insertR(bst->root, d, val, qta, &add);
    if (add) bst->count++;
}


static void PrintR(link h, FILE *fp) {
    if (h == NULL)
        return;

    PrintR(h->l, fp); // visita in order
    QUOTATIONprint(fp, h->q);
    PrintR(h->r, fp);
}

void BSTprint(BSTquotations bst, FILE *fp) {
    if (BSTEmpty(bst))
        return;
    PrintR(bst->root, fp);
}

void static MinMaxRangeR(link root, Date d1, Date d2, float *f1, float *f2) {
    int cmpd1 = DATEcmp(d1, QUOTATIONgetDate(root->q));
    int cmpd2 = DATEcmp(d2, QUOTATIONgetDate(root->q));
    float quotation;
    if (cmpd1 < 0)
        MinMaxRangeR(root->l, d1, d2, f1, f2);
    if (cmpd2 > 0)
        MinMaxRangeR(root->r, d1, d2, f1, f2);
    if (cmpd1 <= 0 && cmpd2 >= 0) {
        quotation = QUOTATIONgetValue(root->q);
        if (*f1 < 0 || *f1 > quotation)
            *f1 = quotation;
        if (*f2 < 0 || *f2 < quotation)
            *f2 = quotation;
    }
}

void BSTMinmaxRange(BSTquotations bst, Date d1, Date d2, float *f1, float *f2) {
    if (bst == NULL || bst->root == NULL || bst->count == 0)
        return;
    MinMaxRangeR(bst->root, d1, d2, f1, f2);
}

static int BSTHeight(link h, int *max, int depth) {
    int min_l, min_r;
    if (h == NULL)
        return 0;
    if (h->l == NULL && h->r == NULL) {
        if (depth > *max) // se sono in una foglia a profondità massima (locale) aggiorno max
            *max = depth;
        return 1;
    }
    min_l = BSTHeight(h->l, max, depth + 1);
    min_r = BSTHeight(h->r, max, depth + 1);
    if (h->l == NULL)
        return min_r + 1;
    if (h->r == NULL)
        return min_l + 1;
    if (min_l < min_r) // ritorna il cammino più piccolo
        return min_l + 1;
    else
        return min_r + 1;
}

link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->count = h->count;
    h->count = 1;
    h->count += (h->l) ? h->l->count : 0;
    h->count += (h->r) ? h->r->count : 0;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->count = h->count;
    h->count = 1;
    h->count += (h->l) ? h->l->count : 0;
    h->count += (h->r) ? h->r->count : 0;
    return x;
}

static link partR(link h, int r) {
    int t = (h->l) ? h->l->count : 0;

    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r - t - 1);
        h = rotL(h);
    }
    return h;
}

static void balance(BSTquotations bst) {
    int k = (bst->count + 1) / 2 - 1; // chiave mediana inferiore
    bst->root = partR(bst->root, k);
}

void BSTbalance(BSTquotations bst) {
    int min, max = -1;
    if (BSTEmpty(bst))
        return;
    min = BSTHeight(bst->root, &max, 1);
    if (bst->root && (bst->root->l == NULL || bst->root->r == NULL))
        min = 0;
    if (min == 0 || ((float) max / (float) min) > S) {
        printf("Pre-bilanciamento min_path = %d max_path = %d\n", min, max);
        balance(bst);
        printf("Bilanciamento completato.\n");
        max = -1;
        min = BSTHeight(bst->root, &max, 1);
        printf("Post-bilanciamento min_path = %d max_path = %d\n", min, max);
    }
}
