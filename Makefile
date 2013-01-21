GCC_PATH	:= /share/home/tools/gcc-4.7.1
CXX		:= $(GCC_PATH)/bin/g++
CXXFLAGS	:= -Wall -O2 -std=c++0x -I$(GCC_PATH)/include/c++/4.7.1 -L$(GCC_PATH)/lib64

NAME	:= monte_carlo
EXEC	:= lib$(NAME).a

SOURCE_SUBDIRS	:= contexts datas roles

SOURCE_DIRS	:= $(addprefix src/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS	:= $(addprefix obj/, $(SOURCE_SUBDIRS))
SOURCE_FILES	:= $(wildcard $(addsuffix /*.cpp, $(SOURCE_DIRS)))
SRC_OBJECTS	:= $(SOURCE_FILES:%.cpp=%.o)
REAL_OBJECTS	:= $(patsubst src/%, obj/%, $(SRC_OBJECTS))

all :	$(EXEC)

$(EXEC) : obj_dirs $(SRC_OBJECTS)
	mkdir -p lib
	rm -f lib/$@
	ar cq lib/$@ $(REAL_OBJECTS)

obj_dirs :
	mkdir -p $(OBJECTS_DIRS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $(patsubst src/%, obj/%, $@) -c $<
 
clean :
	rm -rf lib obj
