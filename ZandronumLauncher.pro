QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/config/launchconfig.cpp \
    src/config/maclaunchconfig.cpp \
    src/launchgame.cpp \
    src/main.cpp \
    src/maindialog.cpp

HEADERS += \
    include/config/launchconfig.h \
    include/config/maclaunchconfig.h \
    include/launchgame.h \
    include/maindialog.h

INCLUDEPATH += \
    include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

# Resources

RESOURCES += \
  resources.qrc

macx:RESOURCES += resources-mac.qrc
win32:RESOURCES += resources-win.qrc

macBinaries.files = $$PWD/resource/executable/mac/Zandronum.app \
                    $$PWD/resource/executable/doom.wad \
                    $$files($$PWD/resource/executable/mod.*)
macBinaries.path = Contents/Resources
macx:QMAKE_BUNDLE_DATA += macBinaries

# Icons

macx:ICON = icon.icns
win32:RC_ICONS = icon.ico
