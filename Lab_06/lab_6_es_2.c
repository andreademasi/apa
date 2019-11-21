//
// Created by Andrea De Masi on 18/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Person *link;

typedef struct {
    int year;
    int month;
    int day;
} Key;

struct Person {
    char code[7];
    char name[51];
    char surname[51];
    Key birth_date;
    char address[51];
    char city[51];
    int postal_code;
    link next;
};

typedef enum {
    r_stampa, r_ins, r_ins_file, r_delete, r_delete_date, r_ricerca, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(struct Person *p, comando_e cmd);

Key KEYset(char *date);

Key KEYget(struct Person p);

struct Person *openFile(int *n);

link SortListIns(link h, struct Person val);

int KEYgreater(Key date1, Key date2);

link newNode(struct Person person, link next);

void ListIns(link registry, int file);

struct Person *ListSearch(link h, char *code);

struct Person ListExtrKeyP(link *hp, char *code);

int KEYgreaterOrEqual(Key date1, Key date2);

int main() {
    int n = 1;

    struct Person *registry = openFile(&n);

    selezionaDati(registry, leggiComando());
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"stampa", "ins", "ins_file", "cancella", "cancella_date", "ricerca", "fine"};
    int i;
    printf("Inserire comando (stampa/ins/ins_file/cancella/cancella_date/ricerca/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_stampa;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(struct Person *p, comando_e cmd) {
    int continua = 1;
    char code[6];
    struct Person *match, *temp = p, deleted;
    Key date1, date2;
    FILE *fp;

    while (continua) {
        switch (cmd) {
            case r_stampa:
                fp = fopen("list.txt", "w");
                while (temp != NULL) {
                    fprintf(fp, "%s %s %s %d/%d/%d %s %s %d\n", temp->code, temp->name, temp->surname,
                            temp->birth_date.day, temp->birth_date.month, temp->birth_date.year, temp->address,
                            temp->city, temp->postal_code);
                    temp = temp->next;
                }
                fclose(fp);
                printf("Lista stampata su 'list.txt'\n");
                cmd = leggiComando();
                break;
            case r_ins:
                ListIns(p, 0);
                cmd = leggiComando();
                break;
            case r_ins_file:
                ListIns(p, 1);
                cmd = leggiComando();
                break;
            case r_delete:
                printf("Inserire codice:");
                scanf("%s", code);
                deleted = ListExtrKeyP(&p, code);
                deleted.code[0] != '0' ? printf("\nEliminato correttamente: %s\n", deleted.code) : printf(
                        "Non trovato.\n");
                cmd = leggiComando();
                break;
            case r_delete_date:
                printf("\nInserire date nel formato <gg/mm/aaaa> <gg/mm/aaaa>:");
                scanf("%d/%d/%d %d/%d/%d", &date1.day, &date1.month, &date1.year, &date2.day, &date2.month,
                      &date2.year);
                link x = p;
                while (x != NULL && KEYgreaterOrEqual(date2, x->birth_date) &&
                       KEYgreaterOrEqual(x->birth_date, date1)) {
                    deleted = ListExtrKeyP(&p, x->code);
                    deleted.code[0] != '0' ? printf("\nEliminato correttamente: %s\n", deleted.code) : printf(
                            "Non trovato.\n");
                    x = x->next;
                }
                cmd = leggiComando();
                break;
            case r_ricerca:
                printf("Inserire codice:");
                scanf("%s", code);
                match = ListSearch(p, code);
                match != NULL ? printf("%s\n", match->surname) : printf("Non trovato.\n");
                cmd = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
                cmd = leggiComando();
                break;
        }
    }
}

void ListIns(struct Person *registry, int file) {
    struct Person temp;
    char birthdate[11], file_name[50], trash[50], code[6];
    FILE *fp;
    int found = 0;

    if (file) {
        printf("Inserire nome file:");
        scanf("%s", file_name);
        fp = fopen(file_name, "r");
        if (fp != NULL) {
            while (fscanf(fp, "%s %s %s %s %s %s %d", code, trash, trash, trash, trash, trash, (int *) trash) != EOF) {
                if (ListSearch(registry, code) != NULL) {
                    found = 1;
                    break;
                }
            }
            if (found)
                printf("PRESENTE DUPLICATO NEL FILE, LETTURA ABORTITA\n");
            else {
                rewind(fp);
                while (fscanf(fp, "%s %s %s %s %s %s %d", temp.code, temp.name, temp.surname,
                              birthdate, temp.address, temp.city, &temp.postal_code) != EOF) {
                    temp.birth_date = KEYset(birthdate);
                    registry = SortListIns(registry, temp);
                }
            }
        } else
            printf("FILE NON TROVATO.\n");

    } else {
        printf("Inserire campi nel formato:\n<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>\n");
        printf("Il campo <data_di_nascita> è nella forma gg/mm/aaaa, <cap> è un numero intero,\n"
               "mentre tutti i campi rimanenti sono stringhe senza spazi di massimo 50 caratteri. <codice> è\n"
               "nella forma AXXXX, dove X rappresenta una cifra nell'intervallo 0-9\n");
        scanf("%s %s %s %s %s %s %d", temp.code, temp.name, temp.surname,
              birthdate, temp.address, temp.city, &temp.postal_code);
        if (ListSearch(registry, temp.code) == NULL) {
            temp.birth_date = KEYset(birthdate);
            SortListIns(registry, temp);
        } else
            printf("CODICE DUPLICATO.\n");
    }
}

struct Person *ListSearch(link h, char *code) {
    link x;
    for (x = h; x != NULL; x = x->next) {
        if (strcmp(code, x->code) == 0)
            return x;
    }
    return NULL;
}

struct Person ListExtrKeyP(link *hp, char *code) {
    link *xp, t;
    struct Person i = {'0'};
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (strcmp((*xp)->code, code) == 0) {
            t = *xp;
            *xp = (*xp)->next;
            i = *t;
            free(t);
            break;
        }
    }
    return i;
}

struct Person *openFile(int *n) {
    int i = 0;
    struct Person *registry, temp;
    char birthdate[11];
    FILE *fp = fopen("/home/andrea/apa/Lab_06/es2.txt", "r");

    registry = NULL;

    while (fscanf(fp, "%s %s %s %s %s %s %d", temp.code, temp.name, temp.surname,
                  birthdate, temp.address, temp.city, &temp.postal_code) != EOF) {
        temp.birth_date = KEYset(birthdate);
        registry = SortListIns(registry, temp);
        i++;
    }
    *n = i;

    fclose(fp);
    return registry;
}

Key KEYget(struct Person p) {
    return p.birth_date;
}

Key KEYset(char *date) {
    int day, month, year;
    Key key;

    sscanf(date, "%d/%d/%d", &day, &month, &year);
    key.day = day;
    key.month = month;
    key.year = year;
    return key;
}

link SortListIns(link h, struct Person val) {
    link x, p;
    Key k = KEYget(val);
    if (h == NULL || KEYgreater(KEYget(*h), k))
        return newNode(val, h);
    for (x = h->next, p = h;
         x != NULL && KEYgreater(k, KEYget(*x));
         p = x, x = x->next);
    p->next = newNode(val, x);
    return h;
}

link newNode(struct Person person, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    strcpy(x->code, person.code);
    strcpy(x->name, person.name);
    strcpy(x->surname, person.surname);
    x->birth_date = person.birth_date;
    strcpy(x->address, person.address);
    strcpy(x->city, person.city);
    x->postal_code = person.postal_code;
    x->next = next;
    return x;
}

int KEYgreater(Key date1, Key date2) {

    if (date2.year < date1.year)
        return 1;
    else if (date2.month < date1.month && date1.year == date2.year)
        return 1;
    else if (date2.day < date1.day && date1.year == date2.year && date1.month == date2.month)
        return 1;

    return 0;
}

int KEYgreaterOrEqual(Key date1, Key date2) {

    if (date2.year <= date1.year)
        return 1;
    else if (date2.month <= date1.month && date1.year == date2.year)
        return 1;
    else if (date2.day <= date1.day && date1.year == date2.year && date1.month == date2.month)
        return 1;

    return 0;
}


