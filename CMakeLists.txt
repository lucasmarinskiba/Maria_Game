// CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(MariaGame VERSION 1.0 LANGUAGES CXX)

# Configuración básica
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Opciones de compilación para Windows
if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)  # Windows 10
    add_compile_options(/W4 /WX)  # Máximo nivel de warnings
endif()

# 1. Buscar Raylib
find_package(raylib REQUIRED)
if(NOT raylib_FOUND)
    message(FATAL_ERROR "Raylib no encontrado. Instálalo desde: https://www.raylib.com")
endif()

# 2. Configurar assets (copiar al directorio de salida)
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
    "src/utils/*.h"
)

file(GLOB HEADERS
    "include/*.h"
    "src/*.h"
    "src/core/*.h"
    "src/levels/*.h"
    "src/utils/*.h"
    "src/utils/*.cpp"
    "src/utils/*.c"
    "src/utils/*.hpp"
    "src/utils/*.cxx"
    "src/utils/*.cpp"
    "src/utils/*.c"
    "src/utils/*.hxx"
    "src/utils/*.h"
    "src/utils/*.hpp"
    "src/utils/*.hxx"
    "src/utils/*.cxx"
)

# 4. Ejecutable principal
add_executable(maria_game
    ${SOURCES}
    ${HEADERS}
)

# 5. Enlazar dependencias
target_include_directories(maria_game PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src/core"
    "${CMAKE_SOURCE_DIR}/src/utils"
)

target_link_libraries(maria_game PRIVATE
    raylib
    opengl32
    gdi32
    winmm
)

# 6. Configuración para Windows
if(WIN32)
    set(RESOURCE_FILE "${CMAKE_SOURCE_DIR}/assets/icon.rc")
    if(EXISTS ${RESOURCE_FILE})
        target_sources(maria_game PRIVATE ${RESOURCE_FILE})
    endif()
    # Copiar DLLs necesarias
    add_custom_command(TARGET maria_game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${raylib_LIBRARY_DIR}/raylib.dll"
        "$<TARGET_FILE_DIR:maria_game>"
    )

    # Icono del ejecutable (opcional)
    set_target_properties(maria_game PROPERTIES
        WIN32_EXECUTABLE ON
        LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()

# 7. Instalación (opcional)
install(TARGETS maria_game
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

# 8. Mensaje final
message(STATUS "Configuración completada. Genera el proyecto con:")
message(STATUS "  cmake --build ${CMAKE_BINARY_DIR}")
message(STATUS "Ejecutable en: ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
