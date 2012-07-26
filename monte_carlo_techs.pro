#TEMPLATE = lib
TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    area_data.cpp \
    lateralsite_data.cpp \
    lateralcell_data.cpp \
    lateraldimer_data.cpp \
    cellreaction_data.cpp \
    dimerreactioncapture_data.cpp \
    dimerreactionexchange_data.cpp \
    dimerreactionstabilization_data.cpp \
    dimerreactiondualstabilization_data.cpp \
    reactionactivation_data.cpp \
    lateralreaction_data.cpp \
    celllateralreaction_data.cpp \
    dimerlateralreactionexplosion_data.cpp \
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
    reactorbase_context.cpp \
    abcdreactor_context.cpp \
    abcdcellreactor_context.cpp \
    abcddimerreactor_context.cpp \
    rtreactor_context.cpp \
    nocoreactor_context.cpp \
    eventinfo_data.cpp \
    lotkareactor_context.cpp \
    lotkathreereactor_context.cpp

HEADERS += \
    area_data.h \
    cell_data.h \
    dimer_data.h \
    lateralsite_data.h \
    lateralcell_data.h \
    lateraldimer_data.h \
    neighbouring_role.h \
    reaction_data.h \
    cellreaction_data.h \
    dimerreactioncapture_data.h \
    dimerreactionexchange_data.h \
    dimerreactionstabilization_data.h \
    dimerreactiondualstabilization_data.h \
    reactionactivation_data.h \
    lateralreaction_data.h \
    celllateralreaction_data.h \
    dimerlateralreactionexplosion_data.h \
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
    reactorbase_context.h \
    abcdreactor_context.h \
    abcdcellreactor_context.h \
    abcddimerreactor_context.h \
    rtreactor_context.h \
    nocoreactor_context.h \
    eventinfo_data.h \
    lotkareactor_context.h \
    lotkathreereactor_context.h

OTHER_FILES += \
    .gitignore \
    README.md \
    classes_tree.png
