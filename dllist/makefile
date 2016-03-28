#CUnit header
INC=/home/wyt/cunit/include/CUnit
#Project root
INCR=../
#CUnit lib
LIB=/home/wyt/cunit/lib
#dynamic
DYNAMIC=-Wl,-rpath=$(LIB)
#static
STATIC=-static

all:DLinkedlist.c test.c
	gcc -O1 -pg -o test1 $^ -I$(INC) -I$(INCR) -L$(LIB) $(STATIC) -lcunit

