GCC_PATH = /usr
CXX = $(GCC_PATH)/bin/g++
CXXFLAGS = -Wall -O2 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64 -I../../src

NAME = test_mc
HEAP_NAME = heap_test

LIB_DIRS = contexts datas roles
LIBS = $(wildcard $(addsuffix /*.o, $(addprefix ../../obj/, $(LIB_DIRS))))

SOURCE_FILES = $(wildcard src/*.cpp)

default:	$(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(LIBS) $(SOURCE_FILES) -o $@

$(HEAP_NAME):
	$(CXX) $(CXXFLAGS) $(LIBS) $(SOURCE_FILES) -ltcmalloc -o $@

clean:
	rm -f $(NAME)
	rm -f $(HEAP_NAME)
