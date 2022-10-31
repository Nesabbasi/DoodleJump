CC=g++ --std=c++11

CCFLAGS +=-l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

doodleJump.out: main.o program.o gameObjects.o maincharacter.o rsdl.o
	$(CC) main.o program.o gameObjects.o maincharacter.o rsdl.o $(CCFLAGS) -o doodleJump.out

main.o: main.cpp program.cpp
	$(CC) -c main.cpp -o main.o

program.o: program.hpp program.cpp rsdl.hpp maincharacter.hpp gameObjects.hpp
	$(CC) -c program.cpp -o program.o

maincharacter.o: maincharacter.hpp maincharacter.cpp rsdl.hpp gameObjects.hpp
	$(CC) -c maincharacter.cpp -o maincharacter.o

gameObjects.o: gameObjects.hpp gameObjects.cpp program.hpp rsdl.hpp
	$(CC) -c gameObjects.cpp -o gameObjects.o

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

clean :
	rm *.o doodleJump.out

