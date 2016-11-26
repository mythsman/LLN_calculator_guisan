CC		=g++
INCLUDE	=-I guisan/include/ 
LDFLAGS	=-L guisan/lib/
LIBS	=-lSDL2_mixer -lguisan -lSDL2_ttf -lSDL2_image -lSDL2
CFLAGS	=-w -O3 $(INCLUDE) $(LDFLAGS)
CXXFLAGS=$(CFLAGS)

.PHONY: guisan all clean  
 
all	:guisan calculator

guisan:
	cd guisan&&mkdir lib&&make all&&cd ..

calculator:src/calculator.o src/parser.o
	$(CC) $(CXXFLAGS) -o calculator src/calculator.o src/parser.o $(LIBS)

clean:
	rm -rf calculator src/*.o
	cd guisan && make clean && cd ..
