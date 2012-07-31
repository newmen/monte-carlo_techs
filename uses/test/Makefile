GCC_PATH = /opt/gcc47
CXX = $(GCC_PATH)/bin/g++
CXX_CFLAGS = -Wall -O2 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64
NAME = test_mc
HEAP_NAME = heap_test

LIB_DIRS = contexts datas roles
LIBS = $(wildcard $(addsuffix /*.o, $(addprefix ../../obj/, $(LIB_DIRS))))

default:	$(NAME)

$(NAME):
	$(CXX) $(CXX_CFLAGS) $(LIBS) *.cpp -o $@

heap_test:
	$(CXX) $(CXX_CFLAGS) $(LIBS) -ltcmalloc *.cpp -o $@

clean:
	rm $(NAME)
	rm $(HEAP_NAME)
