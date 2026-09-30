%module tree
%{
#include "tree.h"
%}

/* Inclua as declarações da sua árvore */
#include "tree.h"

/*swig -python tree.i
gcc -c -fPIC tree.c arvores_wrap.c -I/usr/include/python3.x
gcc -shared tree.o arvores_wrap.o -o _arvores.so*/