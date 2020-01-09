DEFINES +=MACRONAME="1"

INCLUDEPATH +=  $$PWD/../plugindepends/core/ \
                $$PWD/../plugindepends/pluginframework/ \
                $$PWD/../plugindepends/

win32-msvc*{
# for windows visual studio 2015 x64 msvc compiler
CONFIG(debug, debug|release){
equals(QT_ARCH, x86_64): LIBS += -L$${PWD}/lib-windows-x64-msvc-debug -lCTKCore -lCTKPluginFramework
DEFINES += CTK_PLUGIN_LIBS=$${PWD}/lib-windows-x64-msvc-debug
}else{
equals(QT_ARCH, x86_64): LIBS += -L$${PWD}/lib-windows-x64-msvc-release -lCTKCore -lCTKPluginFramework
DEFINES += CTK_PLUGIN_LIBS=$${PWD}/lib-windows-x64-msvc-release
}
}

win32-g++{
# for mingw x64 compiler
equals(QT_ARCH, x86_64){
LIBS += -L$$PWD/../plugindepends/lib-windows-x64-mingw/ -lCTKCore -lCTKPluginFramework
DEFINES += CTK_PLUGIN_LIBS=$${PWD}/lib-windows-x64-mingw
}
}

linux{
# for linux gcc x64 compiler
equals(QT_ARCH, x86_64){
LIBS += -L$$PWD/../plugindepends/lib-gcc-x64/ -lCTKCore -lCTKPluginFramework
DEFINES += CTK_PLUGIN_LIBS=$${PWD}/lib-gcc-x64
}
# for linux gcc arm64 compiler
equals(QT_ARCH, arm64){
LIBS += -L$$PWD/../plugindepends/lib-gcc-arm64/ -lCTKCore -lCTKPluginFramework
DEFINES += CTK_PLUGIN_LIBS=$${PWD}/lib-gcc-arm64
}
}
