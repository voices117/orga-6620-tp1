IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =.

LIBS=-lm

_DEPS = matrix.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o matrix.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


matrix.o: matrix.S
	nasm -f elf -g -F stabs matrix.S

matrix: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 