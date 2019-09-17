CXX = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
OBJECTS = main.o Category.o Clock.o CNote.o CNoteList.o Date.o functions.o Letters.o Rectangle.o RGBA.o Text.o Texture.o Time.o Window.o
RM = rm -f
R = -r
OUT = eyvazemi

all: $(OBJECTS)

main.o: ./src/main.cpp
	$(CXX) -c ./src/main.cpp

Category.o: ./src/Category.cpp ./src/Category.h
	$(CXX) -c ./src/Category.cpp

Clock.o: ./src/Clock.cpp ./src/Clock.h
	$(CXX) -c ./src/Clock.cpp

CNote.o: ./src/CNote.cpp ./src/CNote.h
	$(CXX) -c ./src/CNote.cpp

CNoteList.o: ./src/CNoteList.cpp ./src/CNoteList.h
	$(CXX) -c ./src/CNoteList.cpp

Date.o: ./src/Date.cpp ./src/Date.h
	$(CXX) -c ./src/Date.cpp

functions.o: ./src/functions.cpp ./src/functions.h
	$(CXX) -c ./src/functions.cpp

Letters.o: ./src/Letters.cpp ./src/Letters.h
	$(CXX) -c ./src/Letters.cpp

Rectangle.o: ./src/Rectangle.cpp ./src/Rectangle.h
	$(CXX) -c ./src/Rectangle.cpp

RGBA.o: ./src/RGBA.cpp ./src/RGBA.h
	$(CXX) -c ./src/RGBA.cpp

Text.o: ./src/Text.cpp ./src/Text.h
	$(CXX) -c ./src/Text.cpp

Texture.o: ./src/Texture.cpp ./src/Texture.h
	$(CXX) -c ./src/Texture.cpp

Time.o: ./src/Time.cpp ./src/Time.h
	$(CXX) -c ./src/Time.cpp

Window.o: ./src/Window.cpp ./src/Window.h
	$(CXX) -c ./src/Window.cpp $(LIBS)

compile: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(OUT) $(LIBS)

run:
	./$(OUT)

clean: $(OUT)
	$(RM) *.o
	$(RM) $(OUT)
	$(RM) $(R) ./doc

doc:
	mkdir doc
	cd ./src && doxygen -g ./config && doxygen ./config
	mv ./src/config ./doc/
	mv ./src/html ./doc/
	mv ./doc/html/index.html ./doc/
	mv ./src/latex ./doc/
