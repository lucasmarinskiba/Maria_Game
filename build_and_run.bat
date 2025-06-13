@echo off
cd /d "%~dp0"
if exist build rmdir /s /q build
mkdir build
cd build
:: Si usas vcpkg, descomenta la siguiente línea:
:: cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake ..
cmake --build .
if exist maria_game.exe (
    echo Ejecutando el juego...
    maria_game.exe
) else (
    echo No se pudo encontrar maria_game.exe
)
pause
