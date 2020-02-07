CC = gcc
CFLAGS = -I. -Wall

all: main clear

main: map.h hmap.h hmap.o tree.h tree.o list.o list.h main.o
	$(CC) -o main main.o tree.o hmap.o list.o

clear:
	rm -rf main.o tree.o hmap.o list.o

