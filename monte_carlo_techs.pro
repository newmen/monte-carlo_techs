TEMPLATE = lib
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
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
    nodes.cpp \
    mctree.cpp \
    noden.cpp \
    treebasedsimulation_context.cpp

HEADERS += \
    area_data.h \
    site_data.h \
    dynamicsimulation_context.h \
    simulating_role.h \
    reaction12_data.h \
    reaction21_data.h \
    reaction23_data.h \
    reaction_data.h \
    reacting_role.h \
    ireacting_role.h \
    reactionmigrating_role.h \
    simulationbase_context.h \
    kineticsimulation_context.h \
    reaction35_data.h \
    reaction51mr_data.h \
    reactiondissolutionmigrating_role.h \
    stabilizationreacting_role.h \
    rejectionsimulation_context.h \
    rejectionfreesimulation_context.h \
    reaction34_data.h \
    reaction31_data.h \
    mctree.h \
    treebasedsimulation_context.h \
    nodebase.h \
    nodes.h \
    noden.h \
    storing_role.h \
    store_context.h \
    event_data.h

OTHER_FILES += \
    .gitignore \
    README.md \
    Makefile
