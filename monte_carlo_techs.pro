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
    kineticsimulation_context.cpp \
    treebasedsimulation_context.cpp \
    nodebase.cpp \
    noden.cpp \
    store_context.cpp \
    ineighbouring_role.cpp \
    main.cpp \
    perdatasimulation_context.cpp

HEADERS += \
    area_data.h \
    site_data.h \
    dimer_data.h \
    baseevent_data.h \
    event_data.h \
    reaction12_data.h \
    reaction21_data.h \
    reaction23_data.h \
    reaction31_data.h \
    reaction34_data.h \
    reaction35_data.h \
    reaction51_data.h \
    reaction_data.h \
    simulationbase_context.h \
    eventbasedsimulation_context.h \
    rejectionsimulation_context.h \
    rejectionfreesimulation_context.h \
    dynamicsimulation_context.h \
    perdatasimulation_context.h \
    kineticsimulation_context.h \
    persiteordimer_data.h \
    treebasedsimulation_context.h \
    mctree.h \
    nodebase.h \
    nodes.h \
    noden.h \
    store_context.h \
    storing_role.h \
    simulating_role.h \
    ineighbouring_role.h \
    siteneighbouring_role.h \
    dimerneighbouring_role.h \
    simplesimulation_context.h \
    ireacting_role.h \
    sitereacting_role.h \
    dimerreactionexchanging_role.h \
    dimerreactioncapturing_role.h \
    dimerreactionstabilizing_role.h

OTHER_FILES += \
    .gitignore \
    README.md
