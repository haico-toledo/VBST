%module arvores
%{
#include "arvore.h"
%}

/* Inclua as declarações da sua árvore */
#include "arvore.h"

/*swig -python arvores.i
gcc -c -fPIC arvore.c arvores_wrap.c -I/usr/include/python3.x
gcc -shared arvore.o arvores_wrap.o -o _arvores.so*/