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
		lateralsite_data.cpp \
		lateralcell_data.cpp \
		lateraldimer_data.cpp \
    neighbouring_role.h \
    reaction_data.h \
    cellreaction_data.cpp \
    dimerreactionexchange_data.cpp \
    dimerreactioncapture_data.cpp \
    dimerreactionstabilization_data.cpp \
    dimerreactiondualstabilization_data.cpp \
    reactionactivation_data.cpp \
    lateralreaction_data.cpp \
    celllateralreaction_data.cpp \
    dimerlateralreactionexplosion_data.cpp \
    reactorbase_context.cpp \
    abcdreactor_context.cpp \
    abcdcellreactor_context.cpp \
    abcddimerreactor_context.cpp \
    rtreactor_context.cpp \
    nocoreactor_context.cpp \
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
    storing_role.h \
    eventinfo_data.cpp

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
