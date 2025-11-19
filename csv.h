#ifndef CSV_H
#define CSV_H
#include <stdio.h>
#include "customer.h"
typedef struct {
    char filename[256];
    FILE *fp;
} CSVLogger;
void csv_init(CSVLogger *c,const char *filename);
void csv_close(CSVLogger *c);
void csv_append(CSVLogger *c,Customer cust);
void csv_export_all(CSVLogger *c,Customer *arr,int n);
#endif
