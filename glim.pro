QT = core

CONFIG += c++20 cmdline

DEFINES += USING_QT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FMT += \
    fmt/src/format.cc \
    fmt/src/os.cc

SOURCES += \
        $${FMT} \
        work/Cmd.cpp \
        work/FullTextIndexer.cpp \
        work/FullTextSearcher.cpp \
        work/Task.cpp \
        work/Core.cpp \
        work/main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    work/Cmd.h \
    work/Const.h \
    work/FullTextIndexer.h \
    work/FullTextSearcher.h \
    work/Task.h \
    work/Core.h

INCLUDEPATH += \
    fmt/include \
    json/include \
    work

INCLUDEPATH += env/include
LIBS += -L"$$_PRO_FILE_PWD_/env/lib" -lclownfish -llucy
