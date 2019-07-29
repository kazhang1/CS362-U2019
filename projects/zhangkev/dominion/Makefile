CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> randomtestresult.out
	gcov dominion.c >> randomtestresult.out
	cat dominion.c.gcov >> randomtestresult.out

randomtestresults.out: randomtest1.c randomtest2.c randomtest3.c dominion.o
	echo "randomtest1.c:" >> randomtestresults.out
	gcc -o randomtest1 dominion.c rngs.c randomtest1.c $(CFLAGS)
	randomtest1 >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out 
	
	echo "randomtest2.c:" >> randomtestresults.out
	gcc -o randomtest2 dominion.c rngs.c randomtest2.c $(CFLAGS)
	randomtest2 >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out 
	
	echo "randomtest3.c:" >> randomtestresults.out
	gcc -o randomtest3 dominion.c rngs.c randomtest3.c $(CFLAGS)
	randomtest3 >> randomtestresults.out
	gcov dominion.c -b >> randomtestresults.out 
	
randomtest1: randomtest1.c dominion.o
	gcc -o randomtest1 dominion.c rngs.c randomtest1.c $(CFLAGS)

randomtest2: randomtest2.c dominion.o
	gcc -o randomtest2 dominion.c rngs.c randomtest2.c $(CFLAGS)
	
randomtest3: randomtest3.c dominion.o
	gcc -o randomtest3 dominion.c rngs.c randomtest3.c $(CFLAGS)
	
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
