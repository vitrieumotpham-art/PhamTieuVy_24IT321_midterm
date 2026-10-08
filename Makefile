CC = gcc
CFLAGS = -Wall -g
TARGET = myls
OBJS = main.o myls.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c myls.h
	$(CC) $(CFLAGS) -c main.c

myls.o: myls.c myls.h
	$(CC) $(CFLAGS) -c myls.c

clean:
	rm -f $(OBJS) $(TARGET)