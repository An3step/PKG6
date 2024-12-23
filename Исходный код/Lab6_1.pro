QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += C:/Apps/Qt Projects/freeglut/include
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -lopengl32 -lglu32
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    letter.cpp \
    main.cpp \
    mainwindow.cpp \
    rotating.cpp \
    scaling.cpp \
    transferring.cpp

HEADERS += \
    letter.h \
    mainwindow.h \
    rotating.h \
    scaling.h \
    transferring.h

FORMS += \
    mainwindow.ui \
    rotating.ui \
    scaling.ui \
    transferring.ui
#LIBS += -L"C:/Apps/Qt Projects/freeglut/lib" -lglut -lglu32 -lopengl32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
