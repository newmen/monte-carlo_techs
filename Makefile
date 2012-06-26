C = g++
FLAGS = -Wall -O3 -std=c++0x

obj :
	$(C) $(FLAGS) -c *.cpp

clean :
	rm -rf *.o
