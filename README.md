# SDL3 + Sokol Project

## Dependencies

```
    * Git
    * Clang
    * Make
    * CMake
```

## How to compile


### Windows:

```powershell
PS X:\sdl3_sokol> mkdir build
PS X:\sdl3_sokol> cd build
PS X:\sdl3_sokol> cmake -G "Unix Makefiles" ..
PS X:\sdl3_sokol> make
PS X:\sdl3_sokol> ../bin/SDL3_Sokol.exe
```

### UNIX:

```bash
$ mkdir build && cd build
$ cmake -G "Unix Makefiles" ..
$ make
$ ../bin/SDL3_Sokol
```

## Resources

https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md

https://github.com/floooh/sokol
