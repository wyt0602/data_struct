#CUnit header
INC=/home/wyt/cunit/include/CUnit
#Project root
INCR=../../
#CUnit lib
LIB=/home/wyt/cunit/lib
#dynamic
DYNAMIC=-Wl,-rpath=$(LIB)
#static
STATIC=-static

all:../Queue.c test.c
	gcc  -o test $^ -I$(INC) -I$(INCR) -L$(LIB) $(STATIC) -lcunit

clean:
	rm test Test* log.txt
