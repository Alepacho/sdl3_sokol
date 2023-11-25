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
> git submodule update --init --recursive --progress
> mkdir build
> cd build
> cmake -G "Unix Makefiles" ..
> make
> ../bin/SDL3_Sokol.exe
```

### UNIX:

```bash
$ git submodule update --init --recursive --progress
$ mkdir build && cd build
$ cmake -G "Unix Makefiles" ..
$ make
$ ../bin/SDL3_Sokol
```

## Resources

https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md

https://github.com/floooh/sokol
