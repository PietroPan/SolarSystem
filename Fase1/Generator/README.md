# Make
    cmake CMakeLists.txt
    make

# Run
## Inputs
    plane x y filepath
    box x y z divisions(optional) rep(optional) filepath
    invertedBox x y z divisions(optional) rep(optional) filepath
    sphere radius slices stacks filepath
    cone bottomRadius height slices stacks filepath
    cilinder radius height slices stacks filepath
    torus innerRadius outerRadius rings sides filepath
    bezierPatch fileWithControlPoints numberOfPatches outputFilepath
    terrain heightMapImage heightMultiplicationFactor outputFilepath
## Examples
    ./generator plane 10 10 plane.3d
    ./generator invertedBox 10 10 10 10 box.3d
    ./generator invertedBox 10 10 10 10 rep repBox.3d
    ./generator box 10 10 10 10 invbox.3d
    ./generator box 10 10 10 10 rep invboxRep.3d
    ./generator sphere 8 30 30 sphere.3d
    ./generator cone 8 12 30 30 cone.3d
    ./generator cilinder 8 12 30 30 cilinder.3d
    ./generator torus 3 6 30 30 torus.3d
    ./generator bezierPatch teapot.patch 32 teapot.3d
    ./generator terrain terrain.jpg 0.8 terrain.3d
