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

all:Stack.c test.c
	gcc  -o test1 $^ -I$(INC) -I$(INCR) -L$(LIB) $(STATIC) -lcunit

