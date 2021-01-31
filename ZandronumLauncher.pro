QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
                      $$PWD/resource/executable/doom.wad \
                      $$files($$PWD/resource/executable/mod.*)
  macBinaries.path = Contents/Resources
  QMAKE_BUNDLE_DATA += macBinaries
}

win32 {
  RC_ICONS = icon.ico
  RESOURCES += resources-win.qrc

  copydoom.commands = $(COPY_FILE) $$shell_path($$PWD/resource/executable/doom.wad) $$shell_path($$OUT_PWD/debug)
  copymod.commands = $(COPY_FILE) $$shell_path($$PWD/resource/executable/mod.*) $$shell_path($$OUT_PWD/debug)
  copyzd.commands = $(COPY_FILE) $$shell_path($$PWD/resource/executable/win/*) $$shell_path($$OUT_PWD/debug)
  first.depends = $(first) copydoom copymod copyzd
  export(first.depends)
  export(copydoom.commands)
  export(copymod.commands)
  export(copyzd.commands)
  QMAKE_EXTRA_TARGETS += first copydoom copymod copyzd
}
