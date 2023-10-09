cmake_minimum_required(VERSION 3.5)

project(Popup-Adventure VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set path to our custom CMAKE scripts
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")






# Include Qt deployment helper function
#include("windeployqt.cmake")

#include("windeploymacro.cmake")

#message("let's set our debug or release?")
#set_debug_or_release_variable()
#message(STATUS ----DEBUG_OR_RELEASE_LOWER_CASE " " ${DEBUG_OR_RELEASE_LOWER_CASE}-----)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES Popup-Adventure_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        popupwindow.h
        popupwindow.cpp
        level.h level.cpp
        choice.h choice.cpp
        game.h game.cpp
        player.h player.cpp
        story.h story.cpp
        storysave.h storysave.cpp
        ${TS_FILES}
)

configure_file(story_short.json ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(story_goncharov.json ${CMAKE_BINARY_DIR} COPYONLY)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Popup-Adventure
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Popup-Adventure SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Popup-Adventure
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Popup-Adventure PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(Popup-Adventure PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE ON
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Popup-Adventure)
endif()

include("packaging.cmake")

#get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
#get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E echo
#                    "winddep file = ${_qt_bin_dir}/windeployqt.exe")

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E echo
#                    "target dir = $<TARGET_FILE:${PROJECT_NAME}>")


#add_custom_command(TARGET ${PROJECT_NAME}
#    POST_BUILD
#    COMMAND ${_qt_bin_dir}/windeployqt.exe
#    $<TARGET_FILE:${PROJECT_NAME}>)

#add_custom_command(Popup-Adventure
#    POST_BUILD
#    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/performCrc32.py
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Running CRC32 check..."
#)

# Copy Qt dependencies to output folder
#set_target_deploy_qt(${PROJECT_NAME} ${DEBUG_OR_RELEASE_LOWER_CASE})

#windeployqt("Popup-Adventure")
