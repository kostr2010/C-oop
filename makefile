CC = gcc
CFLAGS = -I. -Wall

all: main clear

main: box.h hmap.h hmap.o tree.h tree.o main.o
	$(CC) -o main main.o tree.o hmap.o

clear:
	rm -rf main.o tree.o hmap.o

