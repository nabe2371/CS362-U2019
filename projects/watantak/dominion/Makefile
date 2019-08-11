CFLAGS= -Wall -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)


unittestEC: unittestEC.c dominion.o rngs.o
	gcc -o unittestEC -g unittestEC.c dominion.o rngs.o $(CFLAGS)
	./unittestEC	

clean:
	rm -f *.o  unittestEC

