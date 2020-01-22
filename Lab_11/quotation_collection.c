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

BSTquotazioni BSTInit() {
    BSTquotazioni bst = malloc(sizeof *bst);
    return bst;
}

int BSTEmpty(BSTquotazioni bst) {
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

Quotation BSTSearch(BSTquotazioni bst, Date d) {
    return searchR(bst->root, d);
}

static link NEW(Date d, float val, int amount, link left, link right) {
    link l = malloc(sizeof *l);
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
        *min = q;
    if (*max < 0 || *max < q)
        *max = q;
    if (h->r)
        minmax(h->r, min, max);
    if (h->l)
        minmax(h->l, min, max);
}

void BSTgetMinMax(BSTquotazioni bst, float *min, float *max) {
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

void BSTInsert_leafR(BSTquotazioni bst, Date d, float val, int qta) {
    int add = 0;
    bst->root = insertR(bst->root, d, val, qta, &add);
    if (add) bst->count++;
}


static void treePrintR(link h, FILE *fp) {
    if (h == NULL)
        return;

    treePrintR(h->l, fp); // IN ORDER
    QUOTATIONprint(fp, h->q);
    treePrintR(h->r, fp);
}

void BSTprint(BSTquotazioni bst, FILE *fp) {
    if (BSTEmpty(bst))
        return;
    treePrintR(bst->root, fp);
}

void static treeMinmaxRange(link r, Date d1, Date d2, float *f1, float *f2) {
    int cmp1 = DATEcmp(d1, QUOTATIONgetDate(r->q));
    int cmp2 = DATEcmp(d2, QUOTATIONgetDate(r->q));
    float qv;
    if (cmp1 < 0)
        treeMinmaxRange(r->l, d1, d2, f1, f2);
    if (cmp2 > 0)
        treeMinmaxRange(r->r, d1, d2, f1, f2);
    if (cmp1 <= 0 && cmp2 >= 0) {
        qv = QUOTATIONgetValue(r->q);
        if (*f1 < 0 || *f1 > qv)
            *f1 = qv;
        if (*f2 < 0 || *f2 < qv)
            *f2 = qv;
    }
}

void BSTMinmaxRange(BSTquotazioni bst, Date d1, Date d2, float *f1, float *f2) {
    if (bst == NULL || bst->root == NULL || bst->count == 0)
        return;
    treeMinmaxRange(bst->root, d1, d2, f1, f2);
}

static int treeMinmaxHeight(link h, int *max, int depth) {
    int min_l, min_r;
    if (h == NULL)
        return 0;
    if (h->l == NULL && h->r == NULL) {
        if (depth > *max)
            *max = depth;
        return 1;
    }
    min_l = treeMinmaxHeight(h->l, max, depth + 1);
    min_r = treeMinmaxHeight(h->r, max, depth + 1);
    if (h->l == NULL)
        return min_r + 1;
    if (h->r == NULL)
        return min_l + 1;
    return (min_l < min_r) ? min_l + 1 : min_r + 1;
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

static link treePartition(link h, int k) {
    int t = (h->l) ? h->l->count : 0;

    if (t > k) {
        h->l = treePartition(h->l, k);
        h = rotR(h);
    }
    if (t < k) {
        h->r = treePartition(h->r, k - t - 1);
        h = rotL(h);
    }
    return h;
}

static void treeBalance(BSTquotazioni bst) {
    int k = (bst->count + 1) / 2 - 1;
    bst->root = treePartition(bst->root, k);
}

void BSTbalance(BSTquotazioni bst) {
    int min = -1, max = -1;
    if (BSTEmpty(bst))
        return;
    min = treeMinmaxHeight(bst->root, &max, 1);
    if (bst->root && (bst->root->l == NULL || bst->root->r == NULL))
        min = 0;
    if (min == 0 || ((float) max / (float) min) > S) {
        printf("Pre-bilanciamento min_path = %d max_path = %d\n", min, max);
        treeBalance(bst);
        min = max = -1;
        min = treeMinmaxHeight(bst->root, &max, 1);
        printf("Post-bilanciamento min_path = %d max_path = %d\n", min, max);
    }
}
