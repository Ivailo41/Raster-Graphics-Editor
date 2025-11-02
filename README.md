# Raster Graphics Editor
This project is a simple `raster graphics editor` developed for my university course "Computer Graphics". It is aimed to serve for `drawing primitives` like lines, circle, elipses and others to `explore different algorithms for drawing` and compare their execution time. It is also being developed to `support different rendering backends and platforms`.

# Features
- Abstracted rendering pipeline designed for multiple backends, currently implemented with SDL
- Input handling
- Drawing lines with Bresenham's algorithm and with the rounded algorithm

# Build and how to run the project
Make sure to clone the project with the containing submodule:
```
git clone --recurse-submodules https://github.com/Ivailo41/Raster-Graphics-Editor.git
```
The project uses CMake for build system, I prefer using Visual Studio to deal with CMake automatically, but if you preffer other IDE that doesnt build automatically, then you can check [here](https://hsf-training.github.io/hsf-training-cmake-webpage/02-building/index.html) for more information about building with CMake. 
> [!NOTE]
> Make sure to add BUILD_SHARED_LIBS=OFF option in cached variables if you want to link SDL staticly (Should be inside the CMakePresets.json file, "SDL_SHARED": "OFF" and "SDL_STATIC": "ON" also do the job)

# Libraries
- SDL - window creation and renderer

# Gallery
Colored lines are the ones added from the code drawn with both methods, <br >
white lines are drawn in runtime from mouse input using Bresenham's method.
<img width="801" height="631" alt="RGE_Demo2" src="https://github.com/user-attachments/assets/a3da42e9-533b-410e-9e5f-d75e3e4a65fd" /> <br >
120x120 pixels grid
