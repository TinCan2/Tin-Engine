# Tin Engine
Tin engine is a small modular game engine written in c++ using the SDL2 library. Since the project is still in its pre-release state, expect incomaptiblities between versions.


## Table of Contents
- [Compilation](#compilation)
- [Usage](#usage)
- [Features](#features)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)


## Compilation
Clone the git repository from github using
```bash
git clone https://github.com/TinCan2/Tin-Engine.git
```

If you are aiming to use the engine in you own CMake project, refer to the section ["Using with CMake]. If not, follow the below given steps.
1. Create a build directory and change into it with the `mkdir Build` command followed by `cd Build`.
2. Run the command `ccmake ..` or `cmake-gui` to specify build options.
3. Decide whether the engine and the SDL2 libraries should be built statically or dynamically using the `TIN_BUILD_SHARED` and `TIN_LINK_SDL_DYNAMIC` options respectively.
4. Choose which modules should be included in the compilation using the `TIN_MODULES_INCLUDE_` options.
5. Exit cmake configuration and run the build system of you choice. On unix this is probably the command `make`.

The output of the build process should now be accumulated under the "Tin-Build" directory.
