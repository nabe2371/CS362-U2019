testme: testme.c
	gcc -o testme -g testme.c -Wall -fpic -coverage -lm -std=c99
	- ./testme 
	echo
	gcov testme.c -b -f

clean:
	rm -f *.o *.gcov *.gcda *.gcno testme
