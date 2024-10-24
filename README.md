# Tin Engine
Tin engine is a small modular game engine written in c++ using the SDL2 library. Since the project is still in its pre-release state, expect incomaptiblities between versions.


## Table of Contents
- [Compilation](#compilation)
- [Usage](#usage)
- [License](#license)
- [Contact](#contact)


## Compilation
Clone the git repository from github using
```bash
git clone https://github.com/TinCan2/Tin-Engine.git
```

If you are aiming to use the engine in you own CMake project, refer to the section ["Using with CMake"](#using-with-cmake). If not, follow the below given steps.
1. Create a build directory and change into it with the `mkdir Build` command followed by `cd Build`.
2. Run the command `ccmake ..` or `cmake-gui` to specify build options.
3. Decide whether the engine and the SDL2 libraries should be built statically or dynamically using the `TIN_BUILD_SHARED` and `TIN_LINK_SDL_DYNAMIC` options respectively.
4. Choose which modules should be included in the compilation using the `TIN_MODULES_INCLUDE_` options.
5. Exit cmake configuration and run the build system of you choice. On unix this is probably the command `make`.

The output of the build process should now be accumulated under the "Tin-Engine Build" directory.

## Usage
How you can use the engine for your given platform can be found in the below given subsections.

### Using with gcc
- **Tin**: Static  
  **SDL**: Static
  ```bash
  g++ files.cpp -Ipath/to/engine/includes -Lpath/to/engine -Lpath/to/SDL -ltinEngine -lSDL2 -lSDL2_image
  ```
- **Tin**: Dynamic  
  **SDL**: Static
  ```bash
  g++ files.cpp -Ipath/to/engine/includes -Lpath/to/engine  -ltinEngine -Wl,-rpath=path/to/engine
  ```
- **Tin**: Static  
  **SDL**: Dynamic
  ```bash
  g++ files.cpp -Ipath/to/engine/includes -Lpath/to/engine -Lpath/to/SDL -ltinEngine -ltinEngine -lSDL2-2.0 -lSDL2_image-2.0 -Wl,-rpath=path/to/SDL
  ```
- **Tin**: Dynamic  
  **SDL**: Dynamic
  ```bash
  g++ files.cpp -Ipath/to/engine/includes -Lpath/to/engine -Lpath/to/SDL -ltinEngine -ltinEngine -lSDL2-2.0 -lSDL2_image-2.0 -Wl,-rpath=path/to/engine:path/to/SDL
  ```

### Using with Visual Studio
After building the engine, you can link the engine and SDL2 libraries using the visual studios linker option. See, the [document on the matter](https://learn.microsoft.com/en-us/cpp/build/adding-references-in-visual-cpp-projects) at Microsoft Learn for more info.

### Using with CMake
Once the engine repository is in yout project directory, you can use the following cmake commands to link the engine to your project.
```cmake
  add_subdirectory(Tin-Engine)
  target_link_libraries(yourTarget PUBLIC|PRIVATE|INTERFACE tinEngine)
  target_include_directories(yourTarget PUBLIC|PRIVATE|INTERFACE ${CMAKE_BINARY_DIR}/Tin-Engine Build/include)
```


## License
Tin engine is distributed under the [MIT license](https://github.com/TinCan2/Tin-Engine/blob/main/LICENSE).


## Contact
As of the time of writing, I am the only person working on the engine. You can contact me at <cannkadioglu@gmail.com>.
