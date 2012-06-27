GCC_PATH = /opt/gcc47
CXX = $(GCC_PATH)/bin/g++47
CXX_CFLAGS = -Wall -O3 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64
LIBS = ../*.o
NAME = test_mc

default:	$(NAME)

$(NAME):
	$(CXX) $(CXX_CFLAGS) $(LIBS) *.cpp -o $(NAME)

heap_test:
	$(CXX) $(CXX_CFLAGS) $(LIBS) -ltcmalloc *.cpp -o $@

clean:
	rm $(NAME)
