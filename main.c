#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
#include "search.h"
#include "edit.h"
#include "payment.h"
#include "backup.h"

int main(void) {
    Hotel hotel;
    hotel_init(&hotel, HOTEL_CAPACITY);

    if(!hotel_admin_login()){
        printf("Authentication failed. Exiting.\\n");
        return 0;
    }

    int choice;
    while (1) {
        hotel_print_menu(&hotel);
        choice = input_int("Enter your choice: ", 1, 15);
        switch (choice) {
            case 1: hotel_add_customer_interactive(&hotel); break;
            case 2: hotel_serve_next(&hotel); break;
            case 3: hotel_checkout_interactive(&hotel); break;
            case 4: hotel_show_waiting(&hotel); break;
            case 5: hotel_show_checked_in(&hotel); break;
            case 6: hotel_show_checked_out(&hotel); break;
            case 7: search_menu(&hotel); break;
            case 8: edit_menu(&hotel); break;
            case 9: hotel_cancel_waiting(&hotel); break;
            case 10: hotel_room_status(&hotel); break;
            case 11: payment_generate_receipt(&hotel); break;
            case 12: hotel_export_csv(&hotel); break;
            case 13: backup_save(&hotel); break;
            case 14: backup_restore(&hotel); break;
            case 15: hotel_destroy(&hotel); printf("Goodbye!\\n"); return 0;
            default: printf("Invalid option\\n");
        }
    }
    return 0;
}
