# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf

CXX= g++
CXXFLAGS= -std=c++17
SFMLFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES= bin/main.o bin/licence.o bin/mainClass.o bin/mainDraw.o bin/mainUpdate.o bin/mainActions.o
TARGET= bin/sgdt


all: $(TARGET)


$(TARGET): $(OBJFILES)
	@echo FINAL BINARY:
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(OBJFILES) -o $(TARGET)
	

bin/main.o: src/main.cxx src/mainClass.hxx
	@echo MAIN CPP:
	$(CXX) $(CXXFLAGS) src/main.cxx -c -o bin/main.o

bin/licence.o: src/licence.cxx
	@echo LICENCE:
	$(CXX) $(CXXFLAGS) src/licence.cxx -c -o bin/licence.o
	
	
bin/mainClass.o: src/mainClass.cxx src/mainClass.hxx
	@echo MAIN CLASS:
	$(CXX) $(CXXFLAGS) src/mainClass.cxx -c -o bin/mainClass.o


bin/mainDraw.o: src/mainDraw.cxx src/mainClass.hxx
	@echo MAIN DRAW:
	$(CXX) $(CXXFLAGS) src/mainDraw.cxx -c -o bin/mainDraw.o
	
bin/mainUpdate.o: src/mainUpdate.cxx src/mainClass.hxx
	@echo MAIN UPDATE:
	$(CXX) $(CXXFLAGS) src/mainUpdate.cxx -c -o bin/mainUpdate.o

bin/mainActions.o: src/mainActions.cxx src/mainClass.hxx
	@echo MAIN ACTIONS:
	$(CXX) $(CXXFLAGS) src/mainActions.cxx -c -o bin/mainActions.o
	
clean:
	rm -f bin/*



.PHONY: clean all


