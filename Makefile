CXX = g++
CXX_CFLAGS = -Wall -O3 -std=c++0x

NAME = monte_carlo
EXEC = lib$(NAME).a
SO = $(NAME).so

LIB_FILES = \
	area_data.cpp \
	site_data.cpp \
	dynamicsimulation_context.cpp \
	simulationbase_context.cpp \
	kineticsimulation_context.cpp \
	rejectionsimulation_context.cpp \
	rejectionfreesimulation_context.cpp \
	nodebase.cpp \
	store_context.cpp \
	event_data.cpp \
	simulating_role.h \
	reaction12_data.h \
	reaction21_data.h \
	reaction23_data.h \
	reaction34_data.h \
	reaction31_data.h \
	reaction_data.h \
	reacting_role.h \
	ireacting_role.h \
	reactionmigrating_role.h \
	reaction35_data.h \
	reaction51mr_data.h \
	reactiondissolutionmigrating_role.h \
	stabilizationreacting_role.h \
	mctree.h \
	treebasedsimulation_context.h \
	nodes.cpp \
	noden.h \
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
