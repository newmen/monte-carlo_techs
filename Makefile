GCC_PATH = /opt/gcc47
CXX = $(GCC_PATH)/bin/g++
CXX_CFLAGS = -Wall -O3 -std=c++0x -I$(GCC_PATH)/include -L$(GCC_PATH)/lib64

NAME = monte_carlo
EXEC = lib$(NAME).a
SO = $(NAME).so

LIB_FILES = \
    area_data.cpp \
    site_data.h \
    dimer_data.h \
    baseevent_data.h \
    event_data.h \
    persiteordimer_data.h \
    simulating_role.h \
    reaction12_data.h \
    reaction21_data.h \
    reaction23_data.h \
    reaction31_data.h \
    reaction34_data.h \
    reaction35_data.h \
    reaction51_data.h \
    reaction_data.h \
    simulationbase_context.cpp \
    simplesimulation_context.cpp \
    eventbasedsimulation_context.cpp \
    rejectionsimulation_context.cpp \
    rejectionfreesimulation_context.cpp \
    dynamicsimulation_context.cpp \
    perdatasimulation_context.cpp \
    kineticsimulation_context.cpp \
    mctree.h \
    nodebase.cpp \
    noden.cpp \
    nodes.h \
    treebasedsimulation_context.cpp \
    ineighbouring_role.cpp \
    siteneighbouring_role.h \
    dimerneighbouring_role.h \
    ireacting_role.h \
    sitereacting_role.h \
    dimerreactionexchanging_role.h \
    dimerreactioncapturing_role.h \
    dimerreactionstabilizing_role.h \
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
