QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 file_copies

SOURCES += \
    src/file/filereader.cpp \
    src/game/config/launchconfig.cpp \
    src/game/config/maclaunchconfig.cpp \
    src/game/config/winlaunchconfig.cpp \
    src/game/launchgame.cpp \
    src/main.cpp \
    src/model/argument.cpp \
    src/network/networkinfo.cpp \
    src/ui/maindialog.cpp

HEADERS += \
    include/file/filereader.h \
    include/game/config/launchconfig.h \
    include/game/config/maclaunchconfig.h \
    include/game/config/winlaunchconfig.h \
    include/game/launchgame.h \
    include/model/argument.h \
    include/network/networkinfo.h \
    include/ui/maindialog.h

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

macx {
  ICON = icon.icns
  RESOURCES += resources-mac.qrc

  macBinaries.files = $$PWD/resource/executable/mac/Zandronum.app \
                      $$files($$PWD/resource/executable/generic/*)
  macBinaries.path = Contents/Resources
  QMAKE_BUNDLE_DATA += macBinaries
}

win32 {
  RC_ICONS = icon.ico
  RESOURCES += resources-win.qrc

  winBinaries.files = $$files($$PWD/resource/executable/win/*) \
                      $$files($$PWD/resource/executable/generic/*)
  winBinaries.path = $$OUT_PWD/debug

  COPIES += winBinaries
}
