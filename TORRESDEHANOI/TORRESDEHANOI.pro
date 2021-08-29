TEMPLATE = app
TARGET = inicio
QT = core gui widgets \
    quick

SOURCES += \
    disco.cpp \
    janelas.cpp \
    main.cpp \
    torreespecial.cpp \
    torrenormal.cpp \
    torres.cpp

HEADERS += \
    disco.h \
    janelas.h \
    torreAbstrata.h \
    torreespecial.h \
    torrenormal.h \
    torres.h
