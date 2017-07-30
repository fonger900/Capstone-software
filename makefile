CC = gcc
IDIR= include
SDIR = src
ODIR = obj
LDIR = lib
CFLAGS = -Wsign-compare  -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes
LFLAGS = -lpython2.7 -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
PYLIBS = -L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib
_SRC = main.cpp
SRC = $(patsubst %,$(SDIR)/%, $(_SRC))

_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

# $@ matches the target; $< matches the first dependent

main: $(OBJ) 
	$(CC) -o $@ $^ $(PYLIBS) $(LFLAGS) 

$(ODIR)/%.o: $(SRC) 
	$(CC) -c -o $@ $^ $(CFLAGS)	

.PHONY: clean

clean:
	rm $(ODIR)/*.o main
