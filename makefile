CC = gcc
CFLAGS = -Wall
TARGET = teste_arvore
SRCS = main.c arvore.c
OBJS = main.o arvore.o
HEADERS = arvore.h

all: $(TARGET)

# CORREÇÃO: Usar $(OBJS) em vez de $(SRCS) para linkar os objetos já compilados
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# ADIÇÃO: Regra para compilar cada .c em .o se houver mudanças neles ou no header
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
    
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

