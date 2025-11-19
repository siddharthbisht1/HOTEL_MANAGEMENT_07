#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int id;
    char name[50];
    char address[100];
    char phone[20];
    int days;
    int priority; /* 1 VIP,2 Regular,3 Low */
    int roomNo; /* -1 if not assigned */
    double bill;
    int status; /* 0 waiting,1 checked-in,2 checked-out */
    char checkin[64];
    char checkout[64];
} Customer;

#endif
