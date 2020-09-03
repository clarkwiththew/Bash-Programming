
myprog : line.o solve.o myprog.o
    gcc -g myprog.o line.o solve.o -o myprog
    
mainprog.o : mainprog.c line.h solve.h
    gcc -g -c mainprog.c
    
solve.o : solve.c solve.h line.h
    gcc -g -c solve.c

line.o : line.c line.h
    gcc -g -c line.c

