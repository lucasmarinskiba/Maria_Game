# Maria_Game

¡Bienvenido a **Maria_Game**!  
Este es un juego en C++ que utiliza [Raylib](https://www.raylib.com/) para gráficos y entrada, diseñado como una aventura en tercera persona con movimiento, cámara, combate, inventario, misiones y más.

---

## Requisitos

- **C++17** o superior
- [Raylib](https://www.raylib.com/) (versión 4.0 o superior)
- Compilador C++ (GCC, MinGW, Clang o MSVC)
- CMake (opcional pero recomendado)
- Git (opcional)
- (Opcional) Visual Studio, Code::Blocks o cualquier IDE C++ moderno

---

## Instalación de Raylib

### Windows

1. Descarga Raylib desde [raylib.com](https://www.raylib.com/).
2. Sigue la guía de instalación oficial para MinGW o Visual Studio:  
   [Guía de Raylib para Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
3. Añade la carpeta de `raylib` a tu variable de entorno `PATH` si es necesario.

### Linux (Ubuntu/Debian)

```sh
sudo apt install libraylib-dev
```

### MacOS

```sh
brew install raylib
```

---

## Compilación

### Método 1: Usando CMake (recomendado)

```sh
git clone https://github.com/lucasmarinskiba/Maria_Game.git
cd Maria_Game
mkdir build
cd build
cmake ..
cmake --build .
```

- El ejecutable aparecerá en la carpeta `build/` (busca `Maria_Game.exe` en Windows, `Maria_Game` en Linux/Mac).

### Método 2: Línea de comandos (Windows, MinGW)

```sh
g++ -o Maria_Game.exe src/*.cpp -Iinclude -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Método 3: Línea de comandos (Linux)

```sh
g++ -o Maria_Game src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Método 4: Visual Studio

- Abre el archivo `.sln` incluido (si existe) o crea un nuevo proyecto y añade todos los archivos fuente.
- Asegúrate de que las rutas de Raylib estén bien configuradas (include y lib).
- Compila y ejecuta el proyecto con `F5`.

---

## Ejecución

- En la terminal, desde la carpeta de compilación o raíz del proyecto:
  - **Windows:**  
    ```sh
    Maria_Game.exe
    ```
  - **Linux/Mac:**  
    ```sh
    ./Maria_Game
    ```

---

## Controles Básicos

- **WASD**: Mover al personaje
- **Mouse**: Rotar cámara (mantén click derecho)
- **Rueda Mouse**: Zoom de cámara
- **Espacio**: Atacar o acción (según implementación)
- **E**: Interactuar con NPC/objeto
- **I**: Abrir inventario
- **ESC**: Salir del juego

---

## Notas

- Si el juego no inicia, verifica que Raylib esté correctamente instalado y que el compilador encuentre las librerías.
- Si tienes errores de compilación relacionados con Raylib, revisa los paths de `include` y `lib`.
- Para cualquier duda o problema, revisa los [issues](https://github.com/lucasmarinskiba/Maria_Game/issues) o abre uno nuevo.

---

## Colaboración

¡Pull requests y sugerencias son bienvenidas!  
Lee las issues abiertas para ver tareas pendientes y mejoras propuestas.

---
