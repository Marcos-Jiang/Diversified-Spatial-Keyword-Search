OBJS = RoadNetwork.o test.o Edge.o Node.o Obj.o
CC = g++
DEBUG = -g
#CFLAGS = -Wall -Werror -O2 -std=c++14 -fsanitize=address -c $(DEBUG)
CFLAGS = -Wall -Werror -O2 -std=c++14 -c
LFLAGS = -Wall $(DEBUG)

test : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test

test.o : test.cpp RoadNetwork.h Node.h Edge.h Obj.h
	$(CC) $(CFLAGS) test.cpp

RoadNetwork.o : RoadNetwork.cpp RoadNetwork.h Node.h Edge.h Obj.h
	$(CC) $(CFLAGS) RoadNetwork.cpp

Edge.o : Edge.cpp Node.h Edge.h Obj.h
	$(CC) $(CFLAGS) Edge.cpp

Node.o : Node.cpp Node.h Edge.h Obj.h
	$(CC) $(CFLAGS) Node.cpp

Obj.o : Obj.cpp Obj.h
	$(CC) $(CFLAGS) Obj.cpp


clean:
	rm *o
