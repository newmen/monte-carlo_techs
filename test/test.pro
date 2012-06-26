TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    performancesaver.h \
    solving_ode.h \
    pathbuilder.h

SOURCES += \
    test.cpp \
    performancesaver.cpp \
    pathbuilder.cpp \
    solving_ode.cpp

OTHER_FILES += \
    run.sh \
    plots.rb \
    Makefile
