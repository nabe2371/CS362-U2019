CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o
	
	echo "Result for running unit tests:" > unittestresults.out
	echo >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest1.c: Test Results" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest1.c: Coverage Information (see Function 'baronRefact' below)" >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	echo >> unittestresults.out
	
	echo >> unittestresults.out
	echo "unittest2.c: Test Results" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest2.c: Coverage Information (see Function 'minionRefact' below)" >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	echo >> unittestresults.out
	
	echo >> unittestresults.out
	echo "unittest3.c: Test Results" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest3.c: Coverage Information (see Function 'ambassadorRefact' below)" >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	echo >> unittestresults.out
		
	echo >> unittestresults.out
	echo "unittest4.c: Test Results" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest4.c: Coverage Information (see Function 'tributeRefact' below)" >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	echo >> unittestresults.out
	
	echo >> unittestresults.out
	echo "unittest5.c: Test Results" >> unittestresults.out
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest5 >> unittestresults.out
	echo >> unittestresults.out
	echo "unittest5.c: Coverage Information (see Function 'mineRefact' below)" >> unittestresults.out
	echo >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	echo >> unittestresults.out

cardtestresults:	 cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o rngs.o
	echo "Result for running card tests:" > cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest1.c: Test Results" >> cardtestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest1.c: Coverage Information (see Function 'initializeGame' below)" >> cardtestresults.out
	echo >> cardtestresults.out
	gcov dominion.c -b -f >> cardtestresults.out
	echo >> cardtestresults.out
	     
	
	echo >> cardtestresults.out
	echo "cardtest2.c: Test Results" >> cardtestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest2.c: Coverage Information (see Function 'shuffle' below)" >> cardtestresults.out
	echo >> cardtestresults.out
	gcov dominion.c -b -f >> cardtestresults.out
	echo >> cardtestresults.out
	        
	echo >> cardtestresults.out
	echo "cardtest3.c: Test Results" >> cardtestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest3.c: Coverage Information (see Function 'entTurn' below)" >> cardtestresults.out
	echo >> cardtestresults.out
	gcov dominion.c -b -f >> cardtestresults.out
	echo >> cardtestresults.out
	       
	echo >> cardtestresults.out
	echo "cardtest4.c: Test Results" >> cardtestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest4.c: Coverage Information (see Function 'getWinners' below)" >> cardtestresults.out
	echo >> cardtestresults.out
	gcov dominion.c -b -f >> cardtestresults.out
	echo >> cardtestresults.out
	       
	echo >> cardtestresults.out
	echo "cardtest5.c: Test Results" >> cardtestresults.out
	gcc -o cardtest5 -g cardtest5.c dominion.o rngs.o $(CFLAGS)
	./cardtest5 >> cardtestresults.out
	echo >> cardtestresults.out
	echo "cardtest5.c: Coverage Information (see Function 'drawCard' below)" >> cardtestresults.out
	echo >> cardtestresults.out
	gcov dominion.c -b -f >> cardtestresults.out
	echo >> cardtestresults.out
	
randomtestresults:	  randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o
	echo "Result for running random tests:" > randomtestresults.out
	echo >> randomtestresults.out
	echo >> randomtestresults.out
	echo "randomtestcard1.c: Test Results" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	echo >> randomtestresults.out
	echo "randomtestcard1.c: Coverage Information (see Function 'baronRefact' below)" >> randomtestresults.out
	echo >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	echo >> randomtestresults.out
	
	echo >> randomtestresults.out
	echo "randomtestcard2.c: Test Results" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	echo >> randomtestresults.out
	echo "randomtestcard2.c: Coverage Information (see Function 'minionRefact' below)" >> randomtestresults.out
	echo >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	echo >> randomtestresults.out
	
	echo >> randomtestresults.out
	echo "randomtestcard3.c: Test Results" >> randomtestresults.out
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard3 >> randomtestresults.out
	echo >> randomtestresults.out
	echo "randomtestcard3.c: Coverage Information (see Function 'tributeRefact' below)" >> randomtestresults.out
	echo >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	echo >> randomtestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out unittest1 unittest2 unittest3 unittest4 unittest5 cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 randomtestcard1 randomtestcard2 randomtestcard3


