CC=g++
 
#CFLAGSLINK= -Wall -lGL -lGLU -lglut -std=c++11

CFLAGSLINK= -Wall -Ofast -lGL -lGLU -lglut -std=c++11

CFLAGS=$(CFLAGSLINK) -c

all: floor

floor: main.o 
	$(CC) main.o spatium.o body.o color.o -o floor $(CFLAGSLINK)
	
main.o: main.cpp spatium.o
	$(CC) $(CFLAGS) main.cpp

spatium.o: spatium.h spatium.cpp body.o
	$(CC) $(CFLAGS) spatium.cpp

body.o: body.h body.cpp color.o
	$(CC) $(CFLAGS) body.cpp

color.o: color.h color.cpp audax.h shared.h
	$(CC) $(CFLAGS) color.cpp

clean:
	rm -rf *.o *.h.gch twobody nbody floor
