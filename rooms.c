#include "rooms.h"
#include <stdlib.h>
#include <stdio.h>
void room_manager_init(RoomManager *rm,int capacity){
    rm->capacity=capacity;
    rm->base=100;
    rm->map=(int*)calloc(capacity,sizeof(int));
    rm->rates=(double*)malloc(sizeof(double)*capacity);
    for(int i=0;i<capacity;i++){
        if(i<2) rm->rates[i]=2500;
        else if(i<5) rm->rates[i]=1800;
        else rm->rates[i]=1200;
    }
}
int room_manager_allocate(RoomManager *rm){
    for(int i=0;i<rm->capacity;i++){
        if(rm->map[i]==0){ rm->map[i]=1; return rm->base+i; }
    }
    return -1;
}
void room_manager_free(RoomManager *rm,int roomNo){
    int idx=roomNo - rm->base;
    if(idx>=0 && idx<rm->capacity) rm->map[idx]=0;
}
double room_manager_get_rate(RoomManager *rm,int roomNo){
    int idx=roomNo - rm->base;
    if(idx>=0 && idx<rm->capacity) return rm->rates[idx];
    return 1200;
}
void room_manager_print(RoomManager *rm){
    printf("Room\tType\tStatus\tRate\n");
    for(int i=0;i<rm->capacity;i++){
        int rn=rm->base+i;
        const char *type = (i<2)?"Deluxe":(i<5)?"Semi":"Standard";
        printf("%d\t%s\t%s\t%.0f\n", rn, type, rm->map[i]?"Occupied":"Free", rm->rates[i]);
    }
}
