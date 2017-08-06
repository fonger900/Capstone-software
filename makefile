CC = gcc

IDIR=~/project/git_prj/Capstone-software/include
CFLAGS =-I/usr/include -I/$(IDIR) -Wsign-compare -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes

SDIR =src
ODIR =obj
LDIR =lib

LIBS =-lconfig -L/home/phong/anaconda2/lib

LFLAGS =-lpython2.7 -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
#PYLIBS =-L/usr/lib/x86_64-linux-gnu 

#_DEPS =capstone.h
#DEPS =$(patsubst %, $(IDIR)/%, $(_DEPS))

_SRC =main.cpp capstone.cpp
SRC =$(patsubst %, $(SDIR)/%, $(_SRC))

_OBJ =$(_SRC:.cpp=.o)
OBJ =$(patsubst %, $(ODIR)/%, $(_OBJ))

MAIN = gendosrule

# $@ matches the target; $< matches the first dependent
all: $(MAIN)
	@echo file \'$(MAIN)\' has been compiled

$(MAIN): $(OBJ) 
	$(CC) -o $@ $^ $(LIBS) $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)	

.PHONY: clean

clean:
	rm $(ODIR)/*.o $(MAIN)
