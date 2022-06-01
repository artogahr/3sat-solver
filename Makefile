CC=g++

3sat-solver: src/main.cpp
	$(CC) -pthread -o 3sat-solver src/main.cpp
	./3sat-solver
