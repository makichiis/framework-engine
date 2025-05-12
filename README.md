# Framework
Voxel Game Engine written in C++. Runs on OpenGL. Still in super-alpha, pls be patient.

# Requirements
Building and using Framework Engine and Framework projects requires [Boost v1.49.0](https://www.boost.org/doc/libs/1_49_0/index.html).

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
