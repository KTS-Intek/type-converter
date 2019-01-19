INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines



#Dependencies - nothing)
contains( QT, network) {
HEADERS += \
    $$PWD/src/shared/networkconverthelper.h

SOURCES += \
    $$PWD/src/shared/networkconverthelper.cpp
}

contains( QT, serialport) {
DEFINES += HASSERIALLIB=1
}



win32 {
DEFINES += BUILDTIME=\\\"$$system('echo %time%')\\\"
DEFINES += BUILDDATE=\\\"$$system('echo %date%')\\\"
} else {
DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y/%m/%d')\\\"
}


HEADERS += \
    $$PWD/src/base/convertatype.h \
    $$PWD/src/base/prettyvalues.h \
    $$PWD/src/base/valuevalidator.h \
    $$PWD/src/shared/embeedefaultreadcommandlist.h \
    $$PWD/src/shared/ifacehelper.h \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.h \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.h \
    $$PWD/src/m2m-service/serializeddatacalculation.h \
    $$PWD/src/matilda/aes128cifradofromphp.h


SOURCES += \
    $$PWD/src/base/convertatype.cpp \
    $$PWD/src/base/prettyvalues.cpp \
    $$PWD/src/base/valuevalidator.cpp \
    $$PWD/src/shared/embeedefaultreadcommandlist.cpp \
    $$PWD/src/shared/ifacehelper.cpp \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.cpp \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.cpp \
    $$PWD/src/m2m-service/serializeddatacalculation.cpp \
    $$PWD/src/matilda/aes128cifradofromphp.cpp

