CC:=gcc
RM:=rm -rf

#all: rAlgo countBH case1 test

all: case2
#clean:
#	$(RM) case1 case2 case3
	
case1: ./randomized/rAlgo.c ./randomized/case1.c
	$(CC) ./randomized/rAlgo.c ./randomized/case1.c -o ./randomized/case1
	
	
test: ./randomized/rAlgo.c ./randomized/test.c
	$(CC) ./randomized/rAlgo.c ./randomized/test.c -o ./randomized/test
	
case2: ./randomized/rAlgo.c ./randomized/case2.c
	$(CC) ./randomized/rAlgo.c ./randomized/case2.c -o ./randomized/case2
	
#case3: ./randomized/rAlgo.c ./randomized/case3.c
#	$(CC) ./randomized/rAlgo.c ./randomized/case3.c -o ./binary/case3
	
rAlgo: ./deterministic/rAlgo.c
	$(CC) ./deterministic/rAlgo.c -o ./deterministic/rAlgo
	
countBH: ./deterministic/countBH.c
	$(CC) ./deterministic/countBH.c -o ./deterministic/countBH
	