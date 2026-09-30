CC = gcc
CFLAGS = -Wall -fPIC
TARGET = teste_arvore
SRCS = main.c tree.c auxiliary.c
OBJS = main.o tree.o auxiliary.o
HEADERS = tree.h auxiliary.h

# Variáveis para o SWIG
INTERFACE = tree.i
WRAP_C = arvores_wrap.c
WRAP_OBJ = arvores_wrap.o
SHARED_LIB = _arvores.so
PYTHON_MODULE = arvores.py

# Flags do Python obtidas automaticamente pelo python3-config
PY_CFLAGS := $(shell python3-config --cflags)
PY_LDFLAGS := $(shell python3-config --ldflags)

all: $(TARGET)

# Compilação padrão C
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar com o SWIG
swig: tree.o
	swig -python $(INTERFACE)
	$(CC) $(CFLAGS) $(PY_CFLAGS) -c $(WRAP_C) -o $(WRAP_OBJ)
	$(CC) -shared tree.o $(WRAP_OBJ) -o $(SHARED_LIB) $(PY_LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS) $(WRAP_C) $(WRAP_OBJ) $(SHARED_LIB) $(PYTHON_MODULE)

.PHONY: all clean swig