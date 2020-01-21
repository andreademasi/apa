#include <stdio.h>

#include "date.h"

Date DATEload(char *sd) {
    Date d;
    sscanf(sd, "%d/%d/%d", &d.aaaa, &d.mm, &d.gg);
    return d;
}

int DATEcmp(Date d1, Date d2) {
    if (d1.aaaa != d2.aaaa)
        return (d1.aaaa - d2.aaaa);
    if (d1.mm != d2.mm)
        return (d1.mm - d2.mm);
    if (d1.gg != d2.gg)
        return (d1.gg - d2.gg);
    return 0;
}

void DATEprint(Date d, FILE *fp) {
    fprintf(fp, "%d/%02d/%02d", d.aaaa, d.mm, d.gg);
}
