LIBS=-lsfml-graphics -lsfml-window -lsfml-system
FLAGS=

all:

	@echo " * building ..."
	
	g++ $(FLAGS) src/test.cpp -c -o build/test.o
	g++ $(FLAGS) -o main build/test.o $(LIBS)

clean:
	rm main
	rm -rf build/*
