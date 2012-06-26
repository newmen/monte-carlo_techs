TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    process_mem_usage.h \
    performancesaver.h \
    solving_ode.h \
    pathbuilder.h

SOURCES += \
    test.cpp \
    process_mem_usage.cpp \
    performancesaver.cpp \
    pathbuilder.cpp \
    solving_ode.cpp

OTHER_FILES += \
    run.sh \
    plots.rb \
    Makefile

unix:!macx:!symbian: LIBS += -L$$PWD/../ -lmonte_carlo

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
