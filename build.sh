#!/bin/bash



g++ -lsfml-graphics -lsfml-window -lsfml-system src/main.cpp -c -o bin/main.o
g++ -lsfml-graphics -lsfml-window -lsfml-system src/licence.cpp -c -o bin/licence.o
g++ -lsfml-graphics -lsfml-window -lsfml-system src/mainClass.cpp -c -o bin/mainClass.o
g++ -lsfml-graphics -lsfml-window -lsfml-system src/structures/node.cpp -c -o bin/node.o
g++ -lsfml-graphics -lsfml-window -lsfml-system bin/*.o -o bin/out.out

