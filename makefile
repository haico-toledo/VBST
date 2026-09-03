CC = gcc
CFLAGS = -Wall
TARGET = teste_arvore
SRCS = main.c arvore.c auxiliary.c
OBJS = main.o arvore.o auxiliary.o
HEADERS = arvore.h auxiliary.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
    
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

