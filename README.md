# Framework
Voxel Game Engine written in C++. Runs on OpenGL. Still in super-alpha, pls be patient.

# Requirements
- CMake 3.29+

# Run unit tests
```sh
$ cd framework-core
$ cmake -G "Unix Makefiles" -B build -S . 
$ cmake --build build -- -j 6 # or however many jobs you want to use 
$ cd build
$ ctest
```

# Contributing/Reading
Check the [syntax specification](syntax_spec.md) for an overview of Framework Engine's coding conventions.
