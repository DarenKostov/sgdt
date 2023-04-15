#!/bin/bash

# WIP

echo "MAIN:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/main.cpp -c -o bin/main.o
echo "LICENCE:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/licence.cpp -c -o bin/licence.o
echo "NODE:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/structures/node.cpp -c -o bin/node.o
echo "MAIN CLASS:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/mainClass.cpp -c -o bin/mainClass.o
echo "FINAL BINARY:"
g++ -lsfml-graphics -lsfml-window -lsfml-system bin/*.o -o bin/out.out
echo "DONE"
