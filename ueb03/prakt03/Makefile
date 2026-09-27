PROG   = MainProgram

GCC    = g++
CFLAGS = -O0 -Wall -g
DFLAGS =


SRC = Schedule.cc \
      Task.cc \
      MainProgram.cc

OBJ = $(SRC:.cc=.o)

PROG = MainProgram

all: $(SRC) $(PROG)
	@./$(PROG)

$(PROG): $(OBJ)
	$(GCC) ${OBJ} ${CFLAGS} -o $@

%.o: %.cc
	$(GCC) ${INCLUDE} ${CFLAGS} ${DFLAGS} -c -o $@ $<

clean:
	rm -f *.o ${PROG} core




