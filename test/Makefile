GCC_PATH = /usr
CXX = $(GCC_PATH)/bin/g++
CXX_CFLAGS = -Wall -O3 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64
LIBS = ../*.o
NAME = test_mc
HEAP_NAME = heap_test

default:	$(NAME)

$(NAME):
	$(CXX) $(CXX_CFLAGS) $(LIBS) *.cpp -o $(NAME)

$(HEAP_NAME):
	$(CXX) $(CXX_CFLAGS) $(LIBS) -ltcmalloc *.cpp -o $@

clean:
	rm $(NAME)
	rm $(HEAP_NAME)
