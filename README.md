# Raster Graphics Editor
This project is a simple `raster graphics editor` developed for my university course "Computer Graphics". It is aimed to serve for `drawing primitives` like lines, circle, elipses and others to `explore different algorithms for drawing` and compare their execution time. It is also being developed to `support different rendering backends and platforms`.

# Features
- Abstracted rendering pipeline designed for multiple backends, currently implemented with SDL
- Input handling
- Graphic User Interface
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
- ImGui - UI

# Gallery
Colored lines are the ones added from the code drawn with both methods, (red overlaping blue) <br >
white lines are drawn in runtime from mouse input using Bresenham's method.
<img width="1266" height="742" alt="RGE" src="https://github.com/user-attachments/assets/864aa0c0-9609-411c-9237-a16a0e370632" />
120x120 pixels grid (some stretching is present, to be fixed)
