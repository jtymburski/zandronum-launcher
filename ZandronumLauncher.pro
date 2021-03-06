QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 file_copies

SOURCES += \
    src/config/launchconfig.cpp \
    src/config/maclaunchconfig.cpp \
    src/config/winlaunchconfig.cpp \
    src/launchgame.cpp \
    src/main.cpp \
    src/maindialog.cpp \
    src/network/networkinfo.cpp

HEADERS += \
    include/config/launchconfig.h \
    include/config/maclaunchconfig.h \
    include/config/winlaunchconfig.h \
    include/launchgame.h \
    include/maindialog.h \
    include/network/networkinfo.h

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
