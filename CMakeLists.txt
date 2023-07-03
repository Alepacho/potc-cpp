cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
#  -O2
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -g3 -Wno-unused-variable -Wno-unused-parameter")
set(PROJECT_NAME "game")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(INCLUDE "inc/")
set(SPATH "${CMAKE_SOURCE_DIR}/src/")
set(SOURCES
    "${SPATH}main.cpp"
    "${SPATH}game.cpp"
    "${SPATH}engine.cpp"
    "${SPATH}gui/screen.cpp"
    "${SPATH}level/block/block.cpp"
    "${SPATH}level/level.cpp"
    "${SPATH}entities/entity.cpp"
    "${SPATH}entities/player.cpp"
    "${SPATH}entities/enemy.cpp"
    "${SPATH}gui/bitmap.cpp"
    "${SPATH}gui/bitmap3d.cpp"
    "${SPATH}menu/menu.cpp"
    "${SPATH}art.cpp"
    "${SPATH}sound.cpp"
)

project(${PROJECT_NAME} CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

# Compilation is OS Specific
IF (WIN32)
    # 
ELSEIF (APPLE)
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${INCLUDE}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    )
    target_link_libraries(${PROJECT_NAME}
        SDL2::Main
        SDL2::Mixer
        SDL2::Image
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
ELSEIF (LINUX)
    # 
ENDIF ()