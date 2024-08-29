all: functions.o main.o
	gcc functions.o main.o -Wall -o autocaflood

functions.o:
	gcc -c functions.c

main.o:
	gcc -c main.c

clean:
	rm *.o autocaflood
