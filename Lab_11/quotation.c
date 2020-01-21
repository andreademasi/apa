#include <stdio.h>

#include "quotation.h"

int QUOTATIONcheckNull(Quotation q) {
    return (q.den == 0);
}

Quotation QUOTAZIONEsetNull() {
    Quotation q = {{-1, -1, -1}, 0.0, 0};
    return q;
}

static float average(Quotation q) {
    if (q.den != 0)
        return q.num / (float) q.den;
    return (float) -1.0;
}

void QUOTATIONprint(FILE *fp, Quotation q) {
    DATEprint(q.data, fp);
    printf(" %f\n", QUOTATIONgetValue(q));
}

Date QUOTATIONgetDate(Quotation q) {
    Date d = {-1, -1, -1};
    if (QUOTATIONcheckNull(q))
        return d;
    return q.data;
}

float QUOTATIONgetValue(Quotation q) {
    return average(q);
}

