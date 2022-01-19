# Engine

The [OpenGL](https://www.opengl.org//), [glew](http://glew.sourceforge.net/), [cmake](https://www.opengl.org//), [freeglut](http://freeglut.sourceforge.net/) and [devil](http://openil.sourceforge.net/) packages are required!

## Make

    cmake CMakeLists.txt
    make

## Run Examples
    ./Engine ../demos/solar_system.xml
    ./Engine ../demos/plane.xml
    ./Engine ../demos/box.xml
    ./Engine ../demos/cone.xml
    ./Engine ../demos/shpere.xml

## Engine Controls
 Key          | Effect
 -------------|----------------------------------------
 mouse        | moves camera
 c            | changes camera between fps and centered
 mouse wheel  | zooms camera (centered)
 w            | moves camera foward (fps)
 a            | moves camera left (fps)
 s            | moves camera backwards (fps)
 d            | moves camera right (fps)
 q            | increases camera speed (fps)
 e            | decreases camera speed (fps)
 t            | toggles xyz axis
 m            | toggles rendering of catmull-rom curves
 n            | changes the type of rendering of catmull-rom curves (points or lines)
 l            | changes between GL_LINES and GL_FILL
