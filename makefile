CC=g++
CXXFLAGS = -g -std=c++17 -ftest-coverage -fprofile-arcs
DEPS = arvore.h
OBJ = arvore.o

%.o: %.cpp $(DEPS)
			$(CC) -c -o $@ $< $(CXXFLAGS)

testa_arvore: $(OBJ)
			$(CC) -o $@ testa_arvore.cpp $< $(CXXFLAGS)

.PHONY: clean

clean:
			rm -f *.o