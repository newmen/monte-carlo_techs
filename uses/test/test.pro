TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    src/process_mem_usage.h \
    src/performancesaver.h \
    src/pathbuilder.h \
    src/simulationcontextfactory.h \
    src/typicalsimcontextfactory.h \
    src/treesimcontextfactory.h

SOURCES += \
    src/process_mem_usage.cpp \
    src/performancesaver.cpp \
    src/pathbuilder.cpp \
    src/treesimcontextfactory.cpp \
    src/test.cpp

OTHER_FILES += \
    run.sh \
    plots.rb \
    noco-test.rb \
    Makefile \
    README.md

unix:!macx:!symbian: LIBS += -L$$PWD/../../lib/ -lmonte_carlo

INCLUDEPATH += $$PWD/../../src/
DEPENDPATH += $$PWD/../../lib/
