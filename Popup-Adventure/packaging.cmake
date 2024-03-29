# Package generation

set(CPACK_PACKAGE_DESCRIPTION "Pop Up Text Adventures")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

set(VERSION_STRING "${VERSION_PATCH}")

if(GIT_COMMIT_HASH)
    set(VERSION_STRING "${VERSION_PATCH}.${GIT_COMMIT_HASH}")
endif()

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STRING}-${CMAKE_SYSTEM_NAME}")

if(STANDALONE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-standalone")
endif()

set(CPACK_PACKAGE_VENDOR "Bandit Bots")
set(CPACK_PACKAGE_CONTACT "the.reakain@gmail.com")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

if(APPLE)
    include("${CMAKE_SOURCE_DIR}/cmake/osx_bundle.cmake")
endif()

include(CPack)
