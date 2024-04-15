cmake_minimum_required(VERSION 3.28)

# project configuration
project(xblock)
set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)

# set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the SFML library
set(SFML_DIR "libraries/SFML-2.6.1/lib/cmake/SFML")  # TODO: edit this path to the SFMLConfig.cmake file
set(BUILD_SHARED_LIBS TRUE)
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)

link_libraries(sfml-audio sfml-graphics sfml-window sfml-system)

# add the executable
add_executable(xblock main.cpp
        res/res.rc
        units/topology.cpp
        units/topology.h
        units/ui.h
        units/ui.cpp
        units/event_handling.cpp
        units/event_handling.h
        units/resources.cpp
        units/resources.h
)

# copy the SFML DLLs to the build directory
set(SFML_BIN_DIR ${SFML_DIR}/../../../bin)
file(COPY ${SFML_BIN_DIR}/openal32.dll DESTINATION ${CMAKE_BINARY_DIR})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")  # Debug mode
    file(COPY ${SFML_BIN_DIR}/sfml-graphics-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-window-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-system-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-audio-d-2.dll DESTINATION ${CMAKE_BINARY_DIR})
else()                                  # Release mode
    file(COPY ${SFML_BIN_DIR}/sfml-graphics-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-window-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-system-2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SFML_BIN_DIR}/sfml-audio-2.dll DESTINATION ${CMAKE_BINARY_DIR})
endif()

# copy the resources to the build directory
file(COPY LICENSE DESTINATION ${CMAKE_BINARY_DIR})
file(COPY res/arial.ttf DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/arialbd.ttf DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/xblock.png DESTINATION ${CMAKE_BINARY_DIR}/res)
file(COPY res/xnftj.mp3 DESTINATION ${CMAKE_BINARY_DIR}/res)


if(WIN32)
    set_target_properties(xblock PROPERTIES WIN32_EXECUTABLE TRUE)
endif()



