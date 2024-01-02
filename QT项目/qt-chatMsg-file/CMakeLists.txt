cmake_minimum_required(VERSION 3.5)

project(myWeixin_mysql_next LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Core Gui Network Sql REQUIRED)

if(ANDROID)
  add_library(myWeixin_mysql_next SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logindialog.cpp
    logindialog.h
    logindialog.ui
    registermysql.cpp
    registermysql.h
    registermysql.ui
    changepassword.cpp
    changepassword.h
    changepassword.ui
    msgserver.cpp
    msgserver.h
    ChatMsgType.h
    clientwidget.cpp
    clientwidget.h
    clientwidget.ui
    serverwidget.cpp
    serverwidget.h
    serverwidget.ui
#    fileserver.cpp
#    fileserver.h
#    fileserver.ui
#    fileclient.cpp
#    fileclient.h
  )
else()
  add_executable(myWeixin_mysql_next
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logindialog.cpp
    logindialog.h
    logindialog.ui
    registermysql.cpp
    registermysql.h
    registermysql.ui
    changepassword.cpp
    changepassword.h
    changepassword.ui
    msgserver.cpp
    msgserver.h
    ChatMsgType.h
    clientwidget.cpp
    clientwidget.h
    clientwidget.ui
    serverwidget.cpp
    serverwidget.h
    serverwidget.ui
#    fileserver.cpp
#    fileserver.h
#    fileserver.ui
#    fileclient.cpp
#    fileclient.h
    pictures.qrc
  )
endif()

target_link_libraries(myWeixin_mysql_next PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network Qt5::Sql)
