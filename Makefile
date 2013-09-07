CC=gcc
CFLAGS=-Wall -std=c99 #-g -pg

SOURCES = read_exp.c calc.c stack.c rpn.c operators.c in.c variables_mapping.c in_exp_rebuilder.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = read_exp.h
EXECS = calc

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
	rm *.o 
	rm calc