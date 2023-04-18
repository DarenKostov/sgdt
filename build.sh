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


echo "CLI:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/cli/mainCLIClass.cpp -c -o bin/mainCLIClass.o


echo "GUI:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/gui/mainGUIClass.cpp -c -o bin/mainGUIClass.o
echo "BOX:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/structures/box.cpp -c -o bin/box.o
echo "BOX:"
g++ -lsfml-graphics -lsfml-window -lsfml-system src/structures/box.cpp -c -o bin/box.o

echo "FINAL BINARY:"
g++ -lsfml-graphics -lsfml-window -lsfml-system bin/*.o -o bin/out.out -g
echo "DONE"
