#TEMPLATE = lib
TEMPLATE = app
CONFIG += console
#CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    area_data.cpp \
    cellreaction_data.cpp \
    dimerreactioncapture_data.cpp \
    dimerreactionexchange_data.cpp \
    dimerreactionstabilization_data.cpp \
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
    main.cpp \
    reactorbase_data.cpp \
    abcddimerreactor_data.cpp \
    abcdreactor_data.cpp \
    abcdcellreactor_data.cpp

HEADERS += \
    area_data.h \
    cell_data.h \
    dimer_data.h \
    neighbouring_role.h \
    reaction_data.h \
    cellreaction_data.h \
    dimerreactioncapture_data.h \
    dimerreactionexchange_data.h \
    dimerreactionstabilization_data.h \
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
    storing_role.h \
    reactorbase_data.h \
    abcddimerreactor_data.h \
    abcdreactor_data.h \
    abcdcellreactor_data.h

OTHER_FILES += \
    .gitignore \
    README.md
