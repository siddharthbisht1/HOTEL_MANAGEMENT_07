#include "hotel.h"
#include "search.h"
#include "edit.h"
#include "payment.h"
#include "backup.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void hotel_init(Hotel *h,int cap){
    queue_init(&h->vip);
    queue_init(&h->regular);
    queue_init(&h->low);

    h->checkedInCount = 0;
    h->checkedOutCount = 0;

    room_manager_init(&h->rooms, cap);
    csv_init(&h->csv, "hotel_records.csv");
}

void hotel_destroy(Hotel *h){
    csv_close(&h->csv);
}

int hotel_admin_login() {
    char user[64], pass[64];

    input_string("Username: ", user, sizeof(user));
    input_string("Password: ", pass, sizeof(pass));

    if(strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0)
        return 1;

    return 0;
}

void hotel_print_menu(Hotel *h){
    printf("\n" CYAN "===== HOTEL MANAGEMENT SYSTEM =====" RESET "\n");
    printf("Capacity: %d | Occupied: %d\n", h->rooms.capacity, h->checkedInCount);
    printf("1. Add Customer (Waiting)\n");
    printf("2. Serve Next (Check-in)\n");
    printf("3. Checkout Customer\n");
    printf("4. Show Waiting List\n");
    printf("5. Show Checked-in Customers\n");
    printf("6. Show Checked-out Customers\n");
    printf("7. Search\n");
    printf("8. Edit\n");
    printf("9. Cancel Waiting Customer\n");
    printf("10. Room Status\n");
    printf("11. Payment / Receipt (last checkout)\n");
    printf("12. Export CSV\n");
    printf("13. Save Backup\n");
    printf("14. Restore Backup\n");
    printf("15. Exit\n");
}

static void current_datetime(char *buf,int n){
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, n, "%Y-%m-%d %H:%M:%S", tm_info);
}

void hotel_add_customer_interactive(Hotel *h){
    Customer c;
    c.id = input_int("Enter Customer ID: ", 1, 1000000);

    input_string("Enter Name: ", c.name, sizeof(c.name));
    input_string("Enter Address: ", c.address, sizeof(c.address));
    input_string("Enter Phone: ", c.phone, sizeof(c.phone));

    c.days = input_int("Enter Number of Days: ", 1, 365);
    c.priority = input_int("Priority (1=VIP,2=Regular,3=Low): ", 1, 3);

    c.roomNo = -1;
    c.bill = 0.0;
    c.status = 0;

    c.checkin[0] = '\0';
    c.checkout[0] = '\0';

    if(c.priority == 1)
        queue_enqueue(&h->vip, c);
    else if(c.priority == 2)
        queue_enqueue(&h->regular, c);
    else
        queue_enqueue(&h->low, c);

    printf(GREEN "Added to waiting list.\n" RESET);
}

void hotel_serve_next(Hotel *h){
    if(h->checkedInCount >= h->rooms.capacity){
        printf(RED "Hotel full.\n" RESET);
        return;
    }

    Customer c;
    int found = 0;

    if(!queue_is_empty(&h->vip))       { c = queue_dequeue(&h->vip); found = 1; }
    else if(!queue_is_empty(&h->regular)) { c = queue_dequeue(&h->regular); found = 1; }
    else if(!queue_is_empty(&h->low))     { c = queue_dequeue(&h->low); found = 1; }

    if(!found){
        printf(YELLOW "No waiting customers.\n" RESET);
        return;
    }

    int room = room_manager_allocate(&h->rooms);
    if(room == -1){
        printf(RED "No rooms available.\n" RESET);
        return;
    }

    c.roomNo = room;
    c.status = 1;
    c.bill = (double)c.days * room_manager_get_rate(&h->rooms, room);

    current_datetime(c.checkin, sizeof(c.checkin));

    h->checkedIn[h->checkedInCount++] = c;

    printf(GREEN "Checked-in: %s Room:%d Bill:%.2f\n" RESET, c.name, c.roomNo, c.bill);
}

void hotel_checkout_interactive(Hotel *h){
    if(h->checkedInCount == 0){
        printf("No checked-in customers.\n");
        return;
    }

    int room = input_int("Enter room number to checkout: ", 0, 99999);

    int idx = -1;
    for(int i = 0; i < h->checkedInCount; i++){
        if(h->checkedIn[i].roomNo == room){
            idx = i;
            break;
        }
    }

    if(idx == -1){
        printf("Room not found.\n");
        return;
    }

    Customer c = h->checkedIn[idx];
    c.status = 2;
    current_datetime(c.checkout, sizeof(c.checkout));

    h->checkedOut[h->checkedOutCount++] = c;
    csv_append(&h->csv, c);

    room_manager_free(&h->rooms, c.roomNo);

    for(int j = idx; j < h->checkedInCount - 1; j++)
        h->checkedIn[j] = h->checkedIn[j + 1];

    h->checkedInCount--;

    printf(GREEN "Checked-out %s Bill:%.2f\n" RESET, c.name, c.bill);
}

void hotel_cancel_waiting(Hotel *h){
    int id = input_int("Enter waiting customer ID to cancel: ", 1, 1000000);

    queue_remove_by_id(&h->vip, id);
    queue_remove_by_id(&h->regular, id);
    queue_remove_by_id(&h->low, id);

    printf("If present, customer removed from waiting queues.\n");
}

void hotel_show_waiting(Hotel *h){
    printf("\n-- VIP --\n"); queue_print(&h->vip);
    printf("\n-- Regular --\n"); queue_print(&h->regular);
    printf("\n-- Low --\n"); queue_print(&h->low);
}

void hotel_show_checked_in(Hotel *h){
    if(h->checkedInCount == 0){
        printf("No checked-in customers.\n");
        return;
    }

    printf("Room\tName\tDays\tPriority\tBill\n");

    for(int i = 0; i < h->checkedInCount; i++){
        Customer *c = &h->checkedIn[i];
        printf("%d\t%s\t%d\t%d\t%.2f\n",
               c->roomNo, c->name, c->days, c->priority, c->bill);
    }
}

void hotel_show_checked_out(Hotel *h){
    if(h->checkedOutCount == 0){
        printf("No checked-out customers.\n");
        return;
    }

    for(int i = 0; i < h->checkedOutCount; i++){
        Customer *c = &h->checkedOut[i];
        printf("Name:%s Room:%d Bill:%.2f Checkin:%s Checkout:%s\n",
               c->name, c->roomNo, c->bill, c->checkin, c->checkout);
    }
}

void hotel_room_status(Hotel *h){
    room_manager_print(&h->rooms);
}

void hotel_export_csv(Hotel *h){
    csv_export_all(&h->csv, h->checkedOut, h->checkedOutCount);
    printf("Exported hotel_records.csv\n");
}
