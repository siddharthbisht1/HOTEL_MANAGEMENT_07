CC = gcc
CFLAGS = -Wall -std=c99
OBJS = main.o hotel.o queue.o rooms.o utils.o csv.o search.o edit.o payment.o backup.o

all: hotel

hotel: $(OBJS)
	$(CC) $(CFLAGS) -o hotel $(OBJS)

clean:
	del /Q *.o hotel.exe 2>nul || rm -f *.o hotel

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
