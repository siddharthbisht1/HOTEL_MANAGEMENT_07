#include "payment.h"
#include <stdio.h>
#include <string.h>

void payment_generate_receipt(Hotel *h){
    if(h->checkedOutCount==0){ printf("No checked-out records to create receipts from.\\n"); return; }
    printf("Generating invoice CSV 'invoices.csv' for last checkout...\\n");
    FILE *fp=fopen("invoices.csv","w");
    if(!fp){ printf("Cannot create invoice file.\\n"); return; }
    fprintf(fp,"ID,Name,Room,Bill,GST,Discount,Final\n");
    Customer *c = &h->checkedOut[h->checkedOutCount-1];
    double gst = c->bill * 0.18;
    double discount = 0.0;
    if(c->priority==1) discount = c->bill * 0.1;
    double final = c->bill + gst - discount;
    fprintf(fp,"%d,%s,%d,%.2f,%.2f,%.2f,%.2f\n", c->id,c->name,c->roomNo,c->bill,gst,discount,final);
    fclose(fp);
    printf("Invoice written. Final amount: %.2f\\n", final);
}
