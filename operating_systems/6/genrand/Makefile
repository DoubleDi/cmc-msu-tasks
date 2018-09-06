CC = gcc
CFLAGS = -std=gnu11 -Wall -Werror -O2
LDFLAGS = -c
OBJECTS = main.o rand.o
TARGET = genrand
all : $(TARGET)
$(TARGET) : $(OBJECTS)
	$(CC) $^ -o $@
main.o : main.c rand.h
	$(CC) $(CFLAGS) $(LDFLAGS) main.c
rand.o : rand.c rand.h
	$(CC) $(CFLAGS) $(LDFLAGS) rand.c
clean :
	rm -f $(TARGET) *.o 
