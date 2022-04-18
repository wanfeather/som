OBJS = som.o vector.o main.o
EXE = main
CC = gcc
CFLAGS = -O3
LIB = -lm



main:$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $(EXE)

main.o som.o:som.h
$(OBJS):vector.h



.PHONY:clean
clean :
	rm -f $(EXE)
	rm -f $(OBJS)
