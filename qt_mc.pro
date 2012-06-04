QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    main.cpp \
    area_data.cpp \
    mainwindow_context.cpp \
    renderarea_context.cpp \
    site_data.cpp \
    dynamicsimulation_context.cpp \
    simulationbase_context.cpp \
    kineticsimulation_context.cpp \
    playbutton.cpp \
    rejectionsimulation_context.cpp

HEADERS += \
    drawing_role.h \
    mainwindow_context.h \
    renderarea_context.h \
    area_data.h \
    site_data.h \
    dynamicsimulation_context.h \
    simulating_role.h \
    reaction12_data.h \
    reaction21_data.h \
    reaction23_data.h \
    reaction3113m_data.h \
    reaction_data.h \
    reacting_role.h \
    ireacting_role.h \
    reactionmigrating_role.h \
    simulationbase_context.h \
    kineticsimulation_context.h \
    playbutton.h \
    reaction35_data.h \
    reaction51mr_data.h \
    reaction34ms_data.h \
    reactiondissolutionmigrating_role.h \
    stabilizationreacting_role.h \
    rejectionsimulation_context.h

OTHER_FILES += \
    .gitignore \
    README.md
