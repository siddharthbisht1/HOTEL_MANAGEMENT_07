#include "csv.h"
#include <stdio.h>
#include <string.h>
void csv_init(CSVLogger *c,const char *filename){
    strncpy(c->filename,filename,sizeof(c->filename)-1);
    c->fp = fopen(c->filename,"a");
    if(!c->fp) c->fp = fopen(c->filename,"w");
    if(c->fp){
        fseek(c->fp,0,SEEK_END);
        long sz=ftell(c->fp);
        if(sz==0) fprintf(c->fp,"ID,Name,Address,Phone,Days,Priority,Room,Bill,Status,Checkin,Checkout\n");
        fflush(c->fp);
    }
}
void csv_close(CSVLogger *c){ if(c->fp) fclose(c->fp); c->fp=NULL; }
void csv_append(CSVLogger *c,Customer cust){
    if(!c->fp) c->fp=fopen(c->filename,"a");
    if(!c->fp) return;
    fprintf(c->fp,"%d,%s,%s,%s,%d,%d,%d,%.2f,%d,%s,%s\n",
        cust.id,cust.name,cust.address,cust.phone,cust.days,cust.priority,cust.roomNo,cust.bill,cust.status,cust.checkin,cust.checkout);
    fflush(c->fp);
}
void csv_export_all(CSVLogger *c,Customer *arr,int n){
    FILE *fp=fopen(c->filename,"w");
    if(!fp) return;
    fprintf(fp,"ID,Name,Address,Phone,Days,Priority,Room,Bill,Status,Checkin,Checkout\n");
    for(int i=0;i<n;i++){
        Customer *cust=&arr[i];
        fprintf(fp,"%d,%s,%s,%s,%d,%d,%d,%.2f,%d,%s,%s\n",
            cust->id,cust->name,cust->address,cust->phone,cust->days,cust->priority,cust->roomNo,cust->bill,cust->status,cust->checkin,cust->checkout);
    }
    fclose(fp);
}
