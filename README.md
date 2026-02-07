# Framework
Voxel Game Engine written in C++. Runs on OpenGL. Still in super-alpha, pls be patient.

# Accouncement: The future of this project...
Framework Engine is a long-standing passion of mine. So much of my free time and my research is dedicated to working towards the product of this game engine. I have spent years improving my skills as a programmer and software developer so that I can build this project as thoughtfully as possible. That being said, I should be transparent about the direction of this project.

I don't fully know what I want out of Framework Engine right now. At the moment, I want to explore efficient real-time rendering solutions for voxel simulations, both through studying existing methods, and dedicating my research to improving upon them. In the future, I furthermore want to explore physics simulation and animation, in addition to rendering solutions that are alternative to meshing. As a result, this is a greenfield project that will unlikely ever see a productive release in the next couple of years. I will announce if/when that changes. 

If you are interested in this project and my work, please feel free to join my [Discord server](https://discord.gg/NUTGS43Fjd). 

# Requirements
- CMake 3.29+
- **GCC** or **Clang**, with the Address Sanitizer and UB Sanitizer.

# Run unit tests
```sh
$ cd framework-core
$ cmake -G "Unix Makefiles" -B build -S . 
$ cmake --build build -- -j 6 # or however many jobs you want to use 
$ cd build
$ ctest
```

# Contributing/Reading
Check the [design specification](design_spec.md) for an overview of Framework Engine's coding conventions.
