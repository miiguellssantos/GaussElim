CC = gcc
CFLAGS = -Wall -Wextra -Ilibs

SRCS = main.c libs/funcoes.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) -o main.exe $(CFLAGS) $(OBJS) 

libs/funcoes.o: libs/funcoes.c libs/funcoes.h
	$(CC) $(CFLAGS) -c libs/funcoes.c -o libs/funcoes.o