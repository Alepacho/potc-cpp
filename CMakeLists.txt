cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -g3")
set(PROJECT_NAME "game")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(INCLUDE "inc/")
set(SOURCES
    "src/main.cpp"
    "src/game.cpp"
    "src/engine.cpp"
    "src/gui/screen.cpp"
    "src/level/block/block.cpp"
    "src/level/level.cpp"
    "src/entities/entity.cpp"
    "src/entities/player.cpp"
    "src/entities/enemy.cpp"
    "src/gui/bitmap.cpp"
    "src/gui/bitmap3d.cpp"
    "src/menu/menu.cpp"
    "src/art.cpp"
    "src/sound.cpp"
)

project(${PROJECT_NAME} CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

# Compilantion is OS Specific
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