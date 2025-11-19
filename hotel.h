#ifndef HOTEL_H
#define HOTEL_H
#include "customer.h"
#include "queue.h"
#include "rooms.h"
#include "csv.h"
#include "utils.h"
#include "colors.h"
#define HOTEL_CAPACITY 12
#define MAX_CUSTOMERS 1000
typedef struct {
    Queue vip, regular, low;
    Customer checkedIn[HOTEL_CAPACITY];
    int checkedInCount;
    Customer checkedOut[MAX_CUSTOMERS];
    int checkedOutCount;
    RoomManager rooms;
    CSVLogger csv;
} Hotel;
void hotel_init(Hotel *h,int cap);
void hotel_destroy(Hotel *h);
void hotel_print_menu(Hotel *h);
int hotel_admin_login();
void hotel_add_customer_interactive(Hotel *h);
void hotel_serve_next(Hotel *h);
void hotel_checkout_interactive(Hotel *h);
void hotel_cancel_waiting(Hotel *h);
void hotel_show_waiting(Hotel *h);
void hotel_show_checked_in(Hotel *h);
void hotel_show_checked_out(Hotel *h);
void hotel_room_status(Hotel *h);
void hotel_export_csv(Hotel *h);
#endif
