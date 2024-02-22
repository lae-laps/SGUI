LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:

	@echo " * building ..."
	
	g++ src/test.cpp -c -o build/test.o
	g++ -o main build/test.o $(LIBS)

clean:
	rm main
	rm -rf build/*
