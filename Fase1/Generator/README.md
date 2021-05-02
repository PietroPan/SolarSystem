# Make
    cmake CMakeLists.txt
    make

# Run
## Inputs
    plane x y filepath
    box x y z divisions(optional) filepath
    sphere radius slices stacks filepath
    cone bottomRadius height slices stacks filepath
    bezierPatch fileWithControlPoints numberOfPatches outputFilepath
    terrain heightMapImage outputFilepath
## Examples
    ./generator plane 10 10 plane.3d
    ./generator box 10 10 10 10 box.3d
    ./generator spere 8 30 30 sphere.3d
    ./generator cone 8 12 30 30 cone.3d
    ./generator bezierPatch teapot.patch 32 teapot.3d
    ./generator terrain terrain.jpg terrain.3d
