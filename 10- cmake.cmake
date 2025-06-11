cmake_minimum_required(VERSION 3.10)
project(MariaGame)

set(CMAKE_CXX_STANDARD 17)

# Configuración para Windows 64-bit
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-m64")
endif()

add_executable(maria_game
    src/main.cpp
    src/Player.cpp
    src/NPC.cpp
    src/Game.cpp
    src/FatimaLevel.cpp
    src/ResourceManager.cpp
)

# Buscar Raylib
find_package(raylib REQUIRED)

# Archivos fuente
file(GLOB SOURCES "src/*.cpp")

# Ejecutable
add_executable(maria_game ${SOURCES})

# Enlazar Raylib
target_link_libraries(maria_game raylib)