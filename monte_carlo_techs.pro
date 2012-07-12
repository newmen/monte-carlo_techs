#TEMPLATE = lib
TEMPLATE = app
CONFIG += console
#CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    area_data.cpp \
    simulationbase_context.cpp \
    simplesimulation_context.cpp \
    eventbasedsimulation_context.cpp \
    rejectionsimulation_context.cpp \
    rejectionfreesimulation_context.cpp \
    dynamicsimulation_context.cpp \
    percell.cpp \
    perdimer.cpp \
    kineticsimulation_context.cpp \
    mctree.cpp \
    nodebase.cpp \
    noden.cpp \
    treebasedsimulation_context.cpp \
    store_context.cpp \
    main.cpp

HEADERS += \
    area_data.h \
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
    simulationbase_context.h \
    simplesimulation_context.h \
    baseevent.h \
    event.h \
    eventbasedsimulation_context.h \
    rejectionsimulation_context.h \
    rejectionfreesimulation_context.h \
    dynamicsimulation_context.h \
    ipersite.h \
    persite.h \
    percell.h \
    perdimer.h \
    sitebasedsimulation_context.h \
    kineticsimulation_context.h \
    mctree.h \
    nodebase.h \
    noden.h \
    inodes.h \
    nodes.h \
    treebasedsimulation_context.h \
    store_context.h \
    storing_role.h

OTHER_FILES += \
    .gitignore \
    README.md
