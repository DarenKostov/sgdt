
# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf

CXX= g++
CXXFLAGS= -std=c++17
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES= bin/main.o bin/licence.o bin/mainClass.o bin/mainCLIClass.o bin/mainCLIClass.o bin/node.o bin/mainGUIClass.o bin/box.o
TARGET= bin/sgdt

all: $(TARGET)


$(TARGET) : $(OBJFILES)
	@echo FINAL BINARY:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) bin/*.o -o $(TARGET)



bin/main.o: src/main.cpp
	@echo MAIN:
	$(CXX) $(CXXFLAGS) src/main.cpp -c -o bin/main.o

bin/licence.o: src/licence.cpp
	@echo LICENCE:
	$(CXX) $(CXXFLAGS) src/licence.cpp -c -o bin/licence.o
	


bin/mainClass.o: src/mainClass.cpp
	@echo MAIN CLASS:
	$(CXX) $(CXXFLAGS) src/mainClass.cpp -c -o bin/mainClass.o



bin/mainCLIClass.o: src/cli/mainCLIClass.cpp
	@echo "CLI:"
	$(CXX) $(CXXFLAGS) src/cli/mainCLIClass.cpp -c -o bin/mainCLIClass.o

bin/node.o: src/structures/node.cpp
	@echo NODE:
	$(CXX) $(CXXFLAGS) src/structures/node.cpp -c -o bin/node.o



bin/mainGUIClass.o: src/gui/mainGUIClass.cpp
	@echo GUI:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/gui/mainGUIClass.cpp -c -o bin/mainGUIClass.o
	
bin/box.o: src/structures/box.cpp
	@echo BOX:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/structures/box.cpp -c -o bin/box.o

clean:
	rm -f bin/*





