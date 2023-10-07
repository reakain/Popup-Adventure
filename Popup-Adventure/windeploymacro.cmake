find_package(Qt6Core REQUIRED)

# get absolute path to qmake, then use it to find windeployqt executable

get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
# Set a variable called DEBUG_OR_RELEASE_LOWER_CASE to either debug or release
# USAGE: set_debug_or_release_variable()
macro (set_debug_or_release_variable)
    if(DEFINED CMAKE_CONFIGURATION_TYPES)
        # defined for Ninja, but not msbuild
        if ("Debug" STREQUAL ${CMAKE_CONFIGURATION_TYPES})
            set(DEBUG_OR_RELEASE_LOWER_CASE debug)
        else()
            set(DEBUG_OR_RELEASE_LOWER_CASE release)
        endif()
    else()
        #defined for msbuild, but not Ninja
        if ("Debug" STREQUAL ${CMAKE_BUILD_TYPE})
            set(DEBUG_OR_RELEASE_LOWER_CASE debug)
        else()
            set(DEBUG_OR_RELEASE_LOWER_CASE release)
        endif()
    endif()
endmacro (set_debug_or_release_variable)

# Based on Jens A. Koch's solution at https://stackoverflow.com/questions/60854495/qt5-cmake-include-all-libraries-into-executable#:~:text=To%20solve%20this%20i%20would%20suggest%20using%20windeployqt.,it%20into%20%2Fcmake%20modules%20folder%20of%20your%20project%3A
# USAGE: set_target_deplay_qt ${PROJECT_NAME} {debug|release}
macro (set_target_deploy_qt arg1 arg2)
    if(NOT EXISTS "${_qt_bin_dir}/windeployqt.exe")
        message(FATAL_ERROR "windeployqt.exe not found in '${_qt_bin_dir}'. Please check that your Qt installation includes the deployment tool.")
    endif()

    message("Hell, windeploy qt is")
    message("${_qt_bin_dir}/windeployqt.exe")
    add_custom_command(TARGET ${arg1} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo
                        "target dir = $<TARGET_FILE:${arg1}>")
    #add_custom_command(TARGET ${arg1} POST_BUILD COMMAND "echo ${_qt_bin_dir}")
    # NOTE: arg2 is lower case 'debug' or 'release'.
#    add_custom_command(TARGET ${arg1} POST_BUILD COMMAND "${_qt_bin_dir}/windeployqt.exe"
#                --${arg2}
#                \"$<TARGET_FILE:${arg1}>\"
#        COMMENT "Deploying Qt libraries using windeployqt.exe for compilation target '${arg1}' ..."
#    )
endmacro (set_target_deploy_qt)

macro(windeploy arg1)
endmacro(windeploy)
