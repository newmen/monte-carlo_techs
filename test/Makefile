GCC_PATH = /opt/gcc47
C = $(GCC_PATH)/bin/g++47
FLAGS = -Wall -O3 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64
APP_NAME = test_mc

all :
	$(C) $(FLAGS) *.cpp *.h -o $(APP_NAME)

clean :
	rm -rf *.o
	rm $(APP_NAME)
