cmake_minimum_required(VERSION 3.15)
project(MariaGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    add_compile_options(/W4 /WX)
endif()

# 1. Buscar SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# 2. Configurar assets
configure_file(
    "${CMAKE_SOURCE_DIR}/assets/"
    "${CMAKE_BINARY_DIR}/assets/"
    COPYONLY
)

# 3. Fuentes del proyecto
file(GLOB SOURCES
    "src/*.cpp"
    "src/core/*.cpp"
    "src/levels/*.cpp"
)
file(GLOB HEADERS
    "include/*.h"
    "src/*.h"
    "src/core/*.h"
    "src/levels/*.h"
    "src/utils/*.h"
    "src/utils/*.hpp"
    "src/utils/*.hxx"
    "src/utils/*.cxx"
    "src/utils/*.cpp"
    "src/utils/*.c"
)

add_executable(maria_game
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(maria_game PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src/core"
    "${CMAKE_SOURCE_DIR}/src/utils"
)

target_link_libraries(maria_game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# 6. Configuración para Windows (opcional: icono)
if(WIN32)
    set(RESOURCE_FILE "${CMAKE_SOURCE_DIR}/assets/icon.rc")
    if(EXISTS ${RESOURCE_FILE})
        target_sources(maria_game PRIVATE ${RESOURCE_FILE})
    endif()
    set_target_properties(maria_game PROPERTIES
        WIN32_EXECUTABLE ON
        LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()

install(TARGETS maria_game
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

message(STATUS "Configuración completada. Genera el proyecto con:")
message(STATUS "  cmake --build ${CMAKE_BINARY_DIR}")
message(STATUS "Ejecutable en: ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
