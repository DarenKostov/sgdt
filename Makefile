
# https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf

CXX= g++
CXXFLAGS= -std=c++17
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES= bin/main.o bin/licence.o bin/mainClass.o bin/mainCLIClass.o bin/mainGUIClass.o
TARGET= bin/sgdt

nocli:
	$(eval LDFLAGS=)
	$(eval OBJFILES=bin/main.o bin/licence.o bin/mainClass.o bin/mainCLIClass.o bin/mainGUIClassRemoved.o)
	@echo NO CLI
	@echo $(OBJFILES)

all: $(TARGET)


$(TARGET) : $(OBJFILES)
	@echo FINAL BINARY:
	@echo $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJFILES) -o $(TARGET)



bin/main.o: src/main.cpp
	@echo MAIN:
	$(CXX) $(CXXFLAGS) src/main.cpp -c -o bin/main.o

bin/licence.o: src/licence.cpp
	@echo LICENCE:
	$(CXX) $(CXXFLAGS) src/licence.cpp -c -o bin/licence.o
	


bin/mainClass.o: src/mainClass.cpp src/mainClass.h
	@echo MAIN CLASS:
	$(CXX) $(CXXFLAGS) src/mainClass.cpp -c -o bin/mainClass.o


# CLI
bin/mainCLIClass.o: src/cli/mainCLIClass.cpp src/cli/mainCLIClass.h
	@echo "CLI:"
	$(CXX) $(CXXFLAGS) src/cli/mainCLIClass.cpp -c -o bin/mainCLIClass.o

bin/node.o: src/structures/node.cpp src/structures/node.h
	@echo NODE:
	$(CXX) $(CXXFLAGS) src/structures/node.cpp -c -o bin/node.o
	
bin/link.o: src/structures/link.cpp src/structures/link.h
	@echo link:
	$(CXX) $(CXXFLAGS) src/structures/link.cpp -c -o bin/link.o



# # GUI
bin/mainGUIClass.o: src/gui/mainGUIClass.cpp src/gui/mainGUIClass.h
	@echo GUI:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/gui/mainGUIClass.cpp -c -o bin/mainGUIClass.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/gui/mainGUIClassRemoved.cpp -c -o bin/mainGUIClassRemoved.o
	
# bin/mainGUIClassRemoved.o: mainGUIClassRemoved.cpp src/gui/mainGUIClass.h
# 	@echo REMOVE GUI:
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/gui/mainGUIClassRemoved.cpp -c -o bin/mainGUIClassRemoved.o
	
bin/box.o: src/structures/box.cpp src/structures/box.h src/structures/node.h
	@echo BOX:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/structures/box.cpp -c -o bin/box.o
	
bin/connector.o: src/structures/connector.cpp src/structures/connector.h src/structures/link.h
	@echo CONNECTOR:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/structures/connector.cpp -c -o bin/connector.o


clean:
	rm -f bin/*





