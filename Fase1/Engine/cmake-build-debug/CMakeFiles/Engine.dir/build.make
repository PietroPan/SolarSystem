# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mane/github/CG/Fase1/Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mane/github/CG/Fase1/Engine/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Engine.dir/flags.make

CMakeFiles/Engine.dir/figura3d.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/figura3d.cpp.o: ../figura3d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Engine.dir/figura3d.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/figura3d.cpp.o -c /home/mane/github/CG/Fase1/Engine/figura3d.cpp

CMakeFiles/Engine.dir/figura3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/figura3d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/figura3d.cpp > CMakeFiles/Engine.dir/figura3d.cpp.i

CMakeFiles/Engine.dir/figura3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/figura3d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/figura3d.cpp -o CMakeFiles/Engine.dir/figura3d.cpp.s

CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o: ../tinyxml/tinyxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o -c /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxml.cpp

CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxml.cpp > CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.i

CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxml.cpp -o CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.s

CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o: ../tinyxml/tinystr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o -c /home/mane/github/CG/Fase1/Engine/tinyxml/tinystr.cpp

CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/tinyxml/tinystr.cpp > CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.i

CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/tinyxml/tinystr.cpp -o CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.s

CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o: ../tinyxml/tinyxmlparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o -c /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlparser.cpp

CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlparser.cpp > CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.i

CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlparser.cpp -o CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.s

CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o: ../tinyxml/tinyxmlerror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o -c /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlerror.cpp

CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlerror.cpp > CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.i

CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/tinyxml/tinyxmlerror.cpp -o CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.s

CMakeFiles/Engine.dir/engine.cpp.o: CMakeFiles/Engine.dir/flags.make
CMakeFiles/Engine.dir/engine.cpp.o: ../engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Engine.dir/engine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/engine.cpp.o -c /home/mane/github/CG/Fase1/Engine/engine.cpp

CMakeFiles/Engine.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mane/github/CG/Fase1/Engine/engine.cpp > CMakeFiles/Engine.dir/engine.cpp.i

CMakeFiles/Engine.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mane/github/CG/Fase1/Engine/engine.cpp -o CMakeFiles/Engine.dir/engine.cpp.s

# Object files for target Engine
Engine_OBJECTS = \
"CMakeFiles/Engine.dir/figura3d.cpp.o" \
"CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o" \
"CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o" \
"CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o" \
"CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o" \
"CMakeFiles/Engine.dir/engine.cpp.o"

# External object files for target Engine
Engine_EXTERNAL_OBJECTS =

Engine: CMakeFiles/Engine.dir/figura3d.cpp.o
Engine: CMakeFiles/Engine.dir/tinyxml/tinyxml.cpp.o
Engine: CMakeFiles/Engine.dir/tinyxml/tinystr.cpp.o
Engine: CMakeFiles/Engine.dir/tinyxml/tinyxmlparser.cpp.o
Engine: CMakeFiles/Engine.dir/tinyxml/tinyxmlerror.cpp.o
Engine: CMakeFiles/Engine.dir/engine.cpp.o
Engine: CMakeFiles/Engine.dir/build.make
Engine: /usr/lib/x86_64-linux-gnu/libOpenGL.so
Engine: /usr/lib/x86_64-linux-gnu/libGLX.so
Engine: /usr/lib/x86_64-linux-gnu/libGLU.so
Engine: /usr/lib/x86_64-linux-gnu/libglut.so
Engine: CMakeFiles/Engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Engine.dir/build: Engine

.PHONY : CMakeFiles/Engine.dir/build

CMakeFiles/Engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Engine.dir/clean

CMakeFiles/Engine.dir/depend:
	cd /home/mane/github/CG/Fase1/Engine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mane/github/CG/Fase1/Engine /home/mane/github/CG/Fase1/Engine /home/mane/github/CG/Fase1/Engine/cmake-build-debug /home/mane/github/CG/Fase1/Engine/cmake-build-debug /home/mane/github/CG/Fase1/Engine/cmake-build-debug/CMakeFiles/Engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Engine.dir/depend

