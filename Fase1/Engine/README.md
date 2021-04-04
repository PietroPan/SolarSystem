# Make
    Use cmake on CMakeLists.txt to a build directory

# Run
    Runnable takes the path to a xml file as argument

## Inputs Examples (if runnable is in a build dir)
    ./Engine ../demos/solar_system.xml
    ./Engine ../demos/plane.xml
    ./Engine ../demos/box.xml
    ./Engine ../demos/cone.xml
    ./Engine ../demos/shpere.xml

# Engine Controls
 Key          | Effect
 -------------|----------------------------------------
 mouse        | moves camera
 mouse wheel  | zooms camera 
 c            | changes camera between fps and centered
 w            | moves camera foward (fps)
 s            | moves camera backwards (fps)
 q            | increases camera speed (fps)
 e            | decreases camera speed (fps)
 t            | toggles xyz axis