QT       += core gui
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    main.cpp \
    shotsave_context.cpp \
    renderarea_context.cpp

HEADERS += \
    shotsave_context.h \
    renderarea_context.h \
    drawing_role.h \
    config.h

unix:!macx:!symbian: LIBS += -L$$PWD/../../lib/ -lmonte_carlo

INCLUDEPATH += $$PWD/../../lib/
DEPENDPATH += $$PWD/../../lib/
