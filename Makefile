
# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf

CXX= g++
CXXFLAGS= -std=c++17
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES= bin/main.o bin/licence.o bin/mainClass.o bin/mainCLIClass.o bin/node.o bin/link.o  bin/terminal.o
GUIOBJFILES= bin/mainGUIClass.o bin/box.o bin/connector.o
TARGET= bin/sgdt


all: $(TARGET)


	


$(TARGET): $(OBJFILES) $(GUIOBJFILES)
	@echo FINAL BINARY:
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(OBJFILES) $(GUIOBJFILES) -o $(TARGET)
	
nogui: $(OBJFILES) bin/mainGUIClassRemoved.o
	@echo FINAL BINARY:
	$(CXX) $(CXXFLAGS) $(OBJFILES) bin/mainGUIClassRemoved.o -o $(TARGET)



bin/main.o: src/main.cpp
	@echo MAIN:
	$(CXX) $(CXXFLAGS) src/main.cpp -c -o bin/main.o

bin/licence.o: src/licence.cpp
	@echo LICENCE:
	$(CXX) $(CXXFLAGS) src/licence.cpp -c -o bin/licence.o
	


bin/mainClass.o: src/mainClass.cpp src/mainClass.h bin/node.o bin/link.o
	@echo MAIN CLASS:
	$(CXX) $(CXXFLAGS) src/mainClass.cpp -c -o bin/mainClass.o

bin/terminal.o: src/terminal.cpp
	@echo MAIN CLASS:
	$(CXX) $(CXXFLAGS) src/terminal.cpp -c -o bin/terminal.o



# CLI
bin/mainCLIClass.o: src/cli/mainCLIClass.cpp src/cli/mainCLIClass.h
	@echo "CLI:"
	$(CXX) $(CXXFLAGS) src/cli/mainCLIClass.cpp -c -o bin/mainCLIClass.o

bin/node.o: src/structures/node.cpp src/structures/node.h
	@echo NODE:
	$(CXX) $(CXXFLAGS) src/structures/node.cpp -c -o bin/node.o
	
bin/link.o: src/structures/link.cpp src/structures/link.h
	@echo LINK:
	$(CXX) $(CXXFLAGS) src/structures/link.cpp -c -o bin/link.o



# # GUI
bin/mainGUIClass.o: src/gui/mainGUIClass.cpp src/gui/mainGUIClass.h bin/box.o bin/connector.o src/mainClass.h
	@echo GUI:
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) src/gui/mainGUIClass.cpp -c -o bin/mainGUIClass.o
	
bin/mainGUIClassRemoved.o: src/gui/mainGUIClassRemoved.cpp src/gui/mainGUIClassRemoved.h
	@echo REMOVE GUI:
	$(CXX) $(CXXFLAGS) src/gui/mainGUIClassRemoved.cpp -c -o bin/mainGUIClassRemoved.o
	
bin/box.o: src/structures/box.cpp src/structures/box.h src/structures/node.h src/structures/guiElement.h
	@echo BOX:
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) src/structures/box.cpp -c -o bin/box.o
	
bin/connector.o: src/structures/connector.cpp src/structures/connector.h src/structures/link.h src/structures/guiElement.h
	@echo CONNECTOR:
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) src/structures/connector.cpp -c -o bin/connector.o


clean:
	rm -f bin/*



.PHONY: clean nogui all


