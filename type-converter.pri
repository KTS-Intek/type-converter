INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines

contains( QT, network) {
HEADERS += \
    $$PWD/src/shared/networkconverthelper.h

SOURCES += \
    $$PWD/src/shared/networkconverthelper.cpp
}

HEADERS += \
    $$PWD/src/base/convertatype.h \
    $$PWD/src/base/prettyvalues.h \
    $$PWD/src/base/valuevalidator.h \
    $$PWD/src/shared/embeedefaultreadcommandlist.h \
    $$PWD/src/shared/ifacehelper.h \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.h \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.h \
    $$PWD/src/matilda/aes128cifradofromphp.h


SOURCES += \
    $$PWD/src/base/convertatype.cpp \
    $$PWD/src/base/prettyvalues.cpp \
    $$PWD/src/base/valuevalidator.cpp \
    $$PWD/src/shared/embeedefaultreadcommandlist.cpp \
    $$PWD/src/shared/ifacehelper.cpp \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.cpp \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.cpp \
    $$PWD/src/matilda/aes128cifradofromphp.cpp

