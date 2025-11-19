#include "search.h"
#include <stdio.h>
#include <string.h>

static void print_customer(Customer *c){
    if(c->id==-1) { printf("None\n"); return; }
    printf("ID:%d Name:%s Room:%d Days:%d Priority:%d Status:%d\\n", c->id,c->name,c->roomNo,c->days,c->priority,c->status);
}

void search_menu(Hotel *h){
    printf("1.Search by ID 2.Search by Name 3.Search by Room 4.Back\\n");
    int ch = input_int("Choice: ",1,4);
    if(ch==4) return;
    if(ch==1){
        int id = input_int("Enter ID: ",1,1000000);
        int found=0;
        int idx=h->vip.front; for(int i=0;i<h->vip.size;i++){ Customer *c=&h->vip.data[idx]; if(c->id==id){ print_customer(c); found=1; break;} idx=(idx+1)%QUEUE_CAP;}
        idx=h->regular.front; for(int i=0;i<h->regular.size;i++){ Customer *c=&h->regular.data[idx]; if(c->id==id){ print_customer(c); found=1; break;} idx=(idx+1)%QUEUE_CAP;}
        idx=h->low.front; for(int i=0;i<h->low.size;i++){ Customer *c=&h->low.data[idx]; if(c->id==id){ print_customer(c); found=1; break;} idx=(idx+1)%QUEUE_CAP;}
        for(int i=0;i<h->checkedInCount;i++){ if(h->checkedIn[i].id==id){ print_customer(&h->checkedIn[i]); found=1; break; } }
        for(int i=0;i<h->checkedOutCount;i++){ if(h->checkedOut[i].id==id){ print_customer(&h->checkedOut[i]); found=1; break; } }
        if(!found) printf("Not found\\n");
    } else if(ch==2){
        char name[50]; input_string("Enter name (substring): ", name, sizeof(name));
        int found=0;
        int idx=h->vip.front; for(int i=0;i<h->vip.size;i++){ Customer *c=&h->vip.data[idx]; if(strstr(c->name,name)){ print_customer(c); found=1; } idx=(idx+1)%QUEUE_CAP;}
        idx=h->regular.front; for(int i=0;i<h->regular.size;i++){ Customer *c=&h->regular.data[idx]; if(strstr(c->name,name)){ print_customer(c); found=1; } idx=(idx+1)%QUEUE_CAP;}
        idx=h->low.front; for(int i=0;i<h->low.size;i++){ Customer *c=&h->low.data[idx]; if(strstr(c->name,name)){ print_customer(c); found=1; } idx=(idx+1)%QUEUE_CAP;}
        for(int i=0;i<h->checkedInCount;i++){ if(strstr(h->checkedIn[i].name,name)){ print_customer(&h->checkedIn[i]); found=1; } }
        for(int i=0;i<h->checkedOutCount;i++){ if(strstr(h->checkedOut[i].name,name)){ print_customer(&h->checkedOut[i]); found=1; } }
        if(!found) printf("Not found\\n");
    } else if(ch==3){
        int room = input_int("Enter Room No: ",0,10000);
        int found=0;
        for(int i=0;i<h->checkedInCount;i++){ if(h->checkedIn[i].roomNo==room){ print_customer(&h->checkedIn[i]); found=1; break; } }
        if(!found) printf("Not found\\n");
    }
}
