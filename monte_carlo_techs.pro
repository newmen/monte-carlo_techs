#TEMPLATE = lib
TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    src/contexts/basesimulation_context.h \
    src/contexts/simplesimulation_context.h \
    src/contexts/eventbasedsimulation_context.h \
    src/contexts/rejectionsimulation_context.h \
    src/contexts/rejectionfreesimulation_context.h \
    src/contexts/dynamicsimulation_context.h \
    src/contexts/sitebasedsimulation_context.h \
    src/contexts/kineticsimulation_context.h \
    src/contexts/treebasedsimulation_context.h \
    src/contexts/store_context.h \
    src/contexts/store_concentrations_context.h \
    src/contexts/storeevent_context.h \
    src/contexts/readevent_context.h \
    src/contexts/basereactor_context.h \
    src/contexts/abcdreactor_context.h \
    src/contexts/abcdcellreactor_context.h \
    src/contexts/abcddimerreactor_context.h \
    src/contexts/rtreactor_context.h \
    src/contexts/nocoreactor_context.h \
    src/contexts/lotkareactor_context.h \
    src/contexts/lotkathreereactor_context.h \
    src/contexts/basedistribution_context.h \
    src/contexts/simpledistribution_context.h \
    src/contexts/wavedistribution_context.h \
    src/contexts/flatwavedistribution_context.h \
    src/contexts/spiralwavedistribution_context.h \
    src/datas/area_data.h \
    src/datas/cell_data.h \
    src/datas/dimer_data.h \
    src/datas/lateralsite_data.h \
    src/datas/lateralcell_data.h \
    src/datas/lateraldimer_data.h \
    src/datas/reaction_data.h \
    src/datas/cellreaction_data.h \
    src/datas/dimerreactioncapture_data.h \
    src/datas/dimerreactionexchange_data.h \
    src/datas/dimerreactionstabilization_data.h \
    src/datas/dimerreactiondualstabilization_data.h \
    src/datas/reactionactivation_data.h \
    src/datas/lateralreaction_data.h \
    src/datas/celllateralreaction_data.h \
    src/datas/dimerlateralreactionexplosion_data.h \
    src/datas/baseevent_data.h \
    src/datas/event_data.h \
    src/datas/basepersite_data.h \
    src/datas/persite_data.h \
    src/datas/percell_data.h \
    src/datas/perdimer_data.h \
    src/datas/mctree_data.h \
    src/datas/basenode_data.h \
    src/datas/node_data.h \
    src/datas/nodesite_data.h \
    src/datas/eventinfo_data.h \
    src/datas/eventrecord_data.h \
    src/roles/neighbouring_role.h \
    src/roles/node_role.h \
    src/roles/storing_role.h

SOURCES += \
    src/contexts/basesimulation_context.cpp \
    src/contexts/simplesimulation_context.cpp \
    src/contexts/eventbasedsimulation_context.cpp \
    src/contexts/rejectionsimulation_context.cpp \
    src/contexts/rejectionfreesimulation_context.cpp \
    src/contexts/dynamicsimulation_context.cpp \
    src/contexts/kineticsimulation_context.cpp \
    src/contexts/treebasedsimulation_context.cpp \
    src/contexts/store_context.cpp \
    src/contexts/store_concentrations_context.cpp \
    src/contexts/storeevent_context.cpp \
    src/contexts/readevent_context.cpp \
    src/contexts/basereactor_context.cpp \
    src/contexts/abcdreactor_context.cpp \
    src/contexts/abcdcellreactor_context.cpp \
    src/contexts/abcddimerreactor_context.cpp \
    src/contexts/rtreactor_context.cpp \
    src/contexts/nocoreactor_context.cpp \
    src/contexts/lotkareactor_context.cpp \
    src/contexts/lotkathreereactor_context.cpp \
    src/contexts/wavedistribution_context.cpp \
    src/contexts/simpledistribution_context.cpp \
    src/datas/area_data.cpp \
    src/datas/lateralsite_data.cpp \
    src/datas/lateralcell_data.cpp \
    src/datas/lateraldimer_data.cpp \
    src/datas/cellreaction_data.cpp \
    src/datas/dimerreactioncapture_data.cpp \
    src/datas/dimerreactionexchange_data.cpp \
    src/datas/dimerreactionstabilization_data.cpp \
    src/datas/dimerreactiondualstabilization_data.cpp \
    src/datas/reactionactivation_data.cpp \
    src/datas/lateralreaction_data.cpp \
    src/datas/celllateralreaction_data.cpp \
    src/datas/dimerlateralreactionexplosion_data.cpp \
    src/datas/percell_data.cpp \
    src/datas/perdimer_data.cpp \
    src/datas/mctree_data.cpp \
    src/datas/basenode_data.cpp \
    src/datas/node_data.cpp \
    src/datas/eventinfo_data.cpp \
    src/datas/eventrecord_data.cpp \
    src/main.cpp

OTHER_FILES += \
    .gitignore \
    README.md \
    classes_tree.png
