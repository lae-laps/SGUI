LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:

	@echo " * building ..."
	
	g++ src/main.cpp -c -o build/main.o
	g++ -o main build/main.o $(LIBS)

clean:
	rm main
	rm -rf build/*
