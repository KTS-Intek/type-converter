# Version=0.0.1
#Dependencies - nothing)
# DEFINES += DONOTINCLUDEIFACEPROCESSOR   - disables iface converters

INCLUDEPATH  += $$PWD\
                $$PWD/../../defines/defines


CONFIG(release, debug|release) {
    QMAKE_POST_LINK=$(STRIP) $(TARGET)
    message($$TARGET ", type-converter: Strip the target")
}


contains( QT, network) {

    contains(DEFINES, DONOTINCLUDEIFACEPROCESSOR){
        message($$TARGET ", type-converter: network is disabled")
    }else{

        message($$TARGET ", type-converter: network is enabled")
HEADERS += \
    $$PWD/src/shared/networkconverthelper.h \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.h \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.h



SOURCES += \
    $$PWD/src/shared/networkconverthelper.cpp \
    $$PWD/matilda-bbb-src/shared/macaddresshelper.cpp \
    $$PWD/matilda-bbb-src/shared/ifacemanagerhelper.cpp
    }
}

contains( QT, serialport) {

    contains(DEFINES, DONOTINCLUDEIFACEPROCESSOR){
        message($$TARGET ", type-converter: serialport is disabled")
    }else{

        message($$TARGET ", type-converter: serialport is enabled")
DEFINES += HASSERIALLIB=1

    }
}

contains( QT, network)|contains( QT, serialport){
    contains(DEFINES, DONOTINCLUDEIFACEPROCESSOR){
        message($$TARGET ", type-converter: iface support is disabled")
    }else{

        message($$TARGET ", type-converter: iface support is enabled")
HEADERS += \
    $$PWD/src/shared/ifacehelper.h \
    $$PWD/src/m2m-service/serializeddatacalculation.h \
    $$PWD/src/shared/embeedefaultreadcommandlist.h

SOURCES += \
    $$PWD/src/shared/ifacehelper.cpp \
    $$PWD/src/m2m-service/serializeddatacalculation.cpp \
    $$PWD/src/shared/embeedefaultreadcommandlist.cpp
    }

}else{
message($$TARGET ", type-converter: the simple mode is enabled")

}

win32 {
DEFINES += BUILDTIME=\\\"$$system('echo %time%')\\\"
DEFINES += BUILDDATE=\\\"$$system('echo %date%')\\\"
} else {
DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y/%m/%d')\\\"
}
DEFINES += MYAPP_VERSION=\\\"$$VERSION\\\"

HEADERS += \
    $$PWD/src/base/convertatype.h \
    $$PWD/src/base/prettyvalues.h \
    $$PWD/src/base/valuevalidator.h \
    $$PWD/src/matilda/aes128cifradofromphp.h \
    $$PWD/src/base/standardmessages.h


SOURCES += \
    $$PWD/src/base/convertatype.cpp \
    $$PWD/src/base/prettyvalues.cpp \
    $$PWD/src/base/valuevalidator.cpp \
    $$PWD/src/matilda/aes128cifradofromphp.cpp \
    $$PWD/src/base/standardmessages.cpp

