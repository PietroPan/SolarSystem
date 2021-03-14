make:
    cmake CMakeLists.txt
    make

run:
    inputs:
        plane x y filepath
        box x y z divisions(optional) filepath
        sphere radius slices stacks filepath
        cone bottomRadius height slices stacks filepath
    examples:
        ./generator plane 10 10 plane.3d
        ./generator box 10 10 10 10 box.3d
        ./generator spere 8 30 30 sphere.3d
        ./generator cone 8 12 30 30 cone.3d
