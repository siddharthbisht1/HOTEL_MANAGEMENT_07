#include "backup.h"
#include <stdio.h>
#include <string.h>

void backup_save(Hotel *h){
    FILE *fp = fopen("backup_checkedin.csv", "w");
    if (!fp) {
        printf("Cannot write backup.\n");
        return;
    }

    fprintf(fp, "ID,Name,Room,Bill,Status,Checkin,Checkout\n");

    for (int i = 0; i < h->checkedInCount; i++) {
        Customer *c = &h->checkedIn[i];
        fprintf(fp, "%d,%s,%d,%.2f,%d,%s,%s\n",
                c->id, c->name, c->roomNo, c->bill, c->status,
                c->checkin, c->checkout);
    }

    fclose(fp);

    // save checked-out list also
    fp = fopen("backup_checkedout.csv", "w");
    if (fp) {
        fprintf(fp, "ID,Name,Room,Bill,Status,Checkin,Checkout\n");
        for (int i = 0; i < h->checkedOutCount; i++) {
            Customer *c = &h->checkedOut[i];
            fprintf(fp, "%d,%s,%d,%.2f,%d,%s,%s\n",
                    c->id, c->name, c->roomNo, c->bill, c->status,
                    c->checkin, c->checkout);
        }
        fclose(fp);
    }

    printf("Backup saved.\n");
}

void backup_restore(Hotel *h){
    FILE *fp = fopen("backup_checkedin.csv", "r");
    if (!fp) {
        return;
    }

    char line[512];

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp)) {
        Customer c;

        c.checkin[0] = '\0';
        c.checkout[0] = '\0';

        sscanf(line, "%d,%49[^,],%d,%lf,%d,%63[^,],%63[^\n]",
               &c.id, c.name, &c.roomNo, &c.bill, &c.status,
               c.checkin, c.checkout);

        if (h->checkedInCount < HOTEL_CAPACITY)
            h->checkedIn[h->checkedInCount++] = c;
    }

    fclose(fp);
    printf("Backup restored.\n");
}
