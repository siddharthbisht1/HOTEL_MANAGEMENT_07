#include "edit.h"
#include <stdio.h>
#include <string.h>

void edit_menu(Hotel *h){
    printf("1.Edit waiting customer 2.Edit checked-in 3.Back\\n");
    int ch = input_int("Choice: ",1,3);
    if(ch==3) return;
    int id = input_int("Enter customer ID: ",1,1000000);
    int found=0;
    int idx;
    int qidx=h->vip.front; for(int i=0;i<h->vip.size;i++){ Customer *c=&h->vip.data[qidx]; if(c->id==id){ input_string("New name: ", c->name, sizeof(c->name)); input_string("New phone: ", c->phone, sizeof(c->phone)); found=1; break;} qidx=(qidx+1)%QUEUE_CAP;}
    qidx=h->regular.front; for(int i=0;i<h->regular.size && !found;i++){ Customer *c=&h->regular.data[qidx]; if(c->id==id){ input_string("New name: ", c->name, sizeof(c->name)); input_string("New phone: ", c->phone, sizeof(c->phone)); found=1; break;} qidx=(qidx+1)%QUEUE_CAP;}
    qidx=h->low.front; for(int i=0;i<h->low.size && !found;i++){ Customer *c=&h->low.data[qidx]; if(c->id==id){ input_string("New name: ", c->name, sizeof(c->name)); input_string("New phone: ", c->phone, sizeof(c->phone)); found=1; break;} qidx=(qidx+1)%QUEUE_CAP;}
    for(idx=0;idx<h->checkedInCount && !found;idx++){ if(h->checkedIn[idx].id==id){ Customer *c=&h->checkedIn[idx]; input_string("New name: ", c->name, sizeof(c->name)); input_string("New phone: ", c->phone, sizeof(c->phone)); found=1; break; } }
    if(found) printf("Edited successfully.\\n"); else printf("Customer not found.\\n");
}
