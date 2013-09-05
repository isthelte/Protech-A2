CC=gcc
CFLAGS=-Wall -std=c99 #-g -pg

SOURCES = read_exp.c calc.c stack.c rpn.c operators.c in.c variables_mapping.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = read_exp.h
EXECS = calc

SOURCES2 = stack.c rpn.c test_rpn.c
OBJS2 = $(patsubst %.c,%.o,$(SOURCES2))
HEADERS2 = rpn.h
EXECS2 = test_rpn

calc: $(OBJS)
	$(CC) $(CFLAGS) -o calc $(OBJS) -lm

$(OBJS): $(HEADERS)

intest: $(EXECS)
	./calc -e --in < sampleExp_In.txt

rpntest: $(EXECS)
	./calc -e --rpn < sampleExp_RPN.txt

.PHONY: clean
clean:
	rm *.o 
	
.PHONY: cleanall
cleanall:
	rm *.o *~ $(EXECS)
