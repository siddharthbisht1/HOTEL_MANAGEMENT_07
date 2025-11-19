#ifndef ROOMS_H
#define ROOMS_H
typedef struct {
    int capacity;
    int *map; /* 0 free,1 occupied */
    int base;
    double *rates;
} RoomManager;
void room_manager_init(RoomManager *rm,int capacity);
int room_manager_allocate(RoomManager *rm);
void room_manager_free(RoomManager *rm,int roomNo);
double room_manager_get_rate(RoomManager *rm,int roomNo);
void room_manager_print(RoomManager *rm);
#endif
