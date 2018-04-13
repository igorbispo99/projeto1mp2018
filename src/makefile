IDIR =../include 
CC=g++
CXXFLAGS=-I$(IDIR) -g -std=c++17 -ftest-coverage -fprofile-arcs

ODIR=obj

_OBJ = arvore.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

obj/arvore.o: arvore.cpp ../include/arvore.hpp
				$(CC) -c -o $@ $< $(CXXFLAGS)

testa_arvore: $(OBJ)
			$(CC) -o ../$@ testa_arvore.cpp $< $(CXXFLAGS)

jogo_20_perguntas: $(OBJ)
			$(CC) -o ../$@ jogo_20_perguntas.cpp $< $(CXXFLAGS)

.PHONY: clean

clean:
			rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
