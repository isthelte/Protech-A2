CC=gcc
CFLAGS=-Wall -std=c99 #-g -pg

SOURCES = read_exp.c calc.c stack.c rpn.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = read_exp.h
EXECS = calc

SOURCES2 = stack.c rpn.c test_rpn.c
OBJS2 = $(patsubst %.c,%.o,$(SOURCES2))
HEADERS2 = rpn.h
EXECS2 = test_rpn

calc: $(OBJS)
	$(CC) $(CFLAGS) -o calc $(OBJS)

$(OBJS): $(HEADERS)

testrpn: $(OBJS2)
	$(CC) $(CFLAGS) -o test_rpn $(OBJS2)

$(OBJS2): $(HEADERS2)

.PHONY: clean
clean:
	rm *.o 
	
.PHONY: cleanall
cleanall:
	rm *.o *~ $(EXECS)
