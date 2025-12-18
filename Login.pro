QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    login.cpp \
    signin_dialog.cpp \
    signup_dialog.cpp \
    welcome_dialog.cpp

HEADERS += \
    login.h \
    signin_dialog.h \
    signup_dialog.h \
    welcome_dialog.h

FORMS += \
    login.ui \
    signin_dialog.ui \
    signup_dialog.ui \
    welcome_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

