all: Test

Test: Test.o BuildRoadNetwork.o
	g++-4.9 -fsanitize=address Test.o BuildRoadNetwork.o -o Test

Test.o: Test.cpp BuildRoadNetwork.h
	g++-4.9 -std=c++14 -Wall -Werror -O2 -fsanitize=address -c Test.cpp
	
BuildRoadNetwork.o: BuildRoadNetwork.cpp BuildRoadNetwork.h
	g++-4.9 -std=c++14 -Wall -Werror -O2 -fsanitize=address -c BuildRoadNetwork.cpp

clean:
	rm *o Test
