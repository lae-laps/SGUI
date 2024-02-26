LIBS=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=-Wall

all:

	@echo " * building "

	g++ src/test.cpp -c -o build/test.o
	g++ -o main build/test.o $(LIBS)

warn:

	@echo " * warnings on "
	
	g++ $(FLAGS) src/test.cpp -c -o build/test.o
	g++ $(FLAGS) -o main build/test.o $(LIBS)

clean:
	rm main
	rm -rf build/*
