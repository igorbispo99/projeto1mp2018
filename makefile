CC=g++
CXXFLAGS = -O2 -std=c++17 -ftest-coverage -fprofile-arcs
DEPS = arvore.h
OBJ = arvore.o

%o: %c $(DEPS)
			$(CC) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CC) -o $@ testa_arvore.cpp $< $(CXXFLAGS)