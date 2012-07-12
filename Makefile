GCC_PATH = /opt/gcc47
CXX = $(GCC_PATH)/bin/g++
CXX_CFLAGS = -Wall -O3 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64

NAME = monte_carlo
EXEC = lib$(NAME).a
SO = $(NAME).so

LIB_FILES = \
    area_data.cpp \
    cell_data.h \
    dimer_data.h \
    neighbouring_role.h \
    reaction12_data.h \
    reaction21_data.h \
    reaction23_data.h \
    reaction31_data.h \
    reaction34_data.h \
    reaction35_data.h \
    reaction51_data.h \
    reaction_data.h \
    ireacting_role.h \
    cellreacting_role.h \
    dimerreactionexchanging_role.h \
    dimerreactioncapturing_role.h \
    dimerreactionstabilizing_role.h \
    simulationbase_context.cpp \
    simplesimulation_context.cpp \
    baseevent.h \
    event.h \
    eventbasedsimulation_context.cpp \
    rejectionsimulation_context.cpp \
    rejectionfreesimulation_context.cpp \
    dynamicsimulation_context.cpp \
    ipersite.h \
    persite.h \
    percell.cpp \
    perdimer.cpp \
    kineticsimulation_context.cpp \
    mctree.cpp \
    nodebase.cpp \
    noden.cpp \
    inodes.h \
    nodes.h \
    treebasedsimulation_context.cpp \
    store_context.cpp \
    storing_role.h

LIBOFILES = $(LIB_FILES:%.cpp=%.o)

default:	$(EXEC)

$(EXEC):
	$(CXX) $(CXX_CFLAGS) -c $(LIB_FILES)
	rm -f $@
	ar cq $@ $(LIBOFILES)

lib:
	$(CXX) $(CXX_CFLAGS) -fPIC -c $(LIB_FILES)
	ld -G *.o -o $(SO)

clean:
	rm -f *.gch
	rm -f *.o
	rm -f *.a
	rm -f *.so
