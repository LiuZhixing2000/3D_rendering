# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuzhixing/workspace/PathTracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuzhixing/workspace/PathTracing/release

# Include any dependencies generated for this target.
include CMakeFiles/PathTracing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PathTracing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PathTracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PathTracing.dir/flags.make

CMakeFiles/PathTracing.dir/src/main.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/PathTracing.dir/src/main.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PathTracing.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/main.cpp.o -MF CMakeFiles/PathTracing.dir/src/main.cpp.o.d -o CMakeFiles/PathTracing.dir/src/main.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/main.cpp

CMakeFiles/PathTracing.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/main.cpp > CMakeFiles/PathTracing.dir/src/main.cpp.i

CMakeFiles/PathTracing.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/main.cpp -o CMakeFiles/PathTracing.dir/src/main.cpp.s

CMakeFiles/PathTracing.dir/src/vector.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/vector.cpp.o: ../src/vector.cpp
CMakeFiles/PathTracing.dir/src/vector.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PathTracing.dir/src/vector.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/vector.cpp.o -MF CMakeFiles/PathTracing.dir/src/vector.cpp.o.d -o CMakeFiles/PathTracing.dir/src/vector.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/vector.cpp

CMakeFiles/PathTracing.dir/src/vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/vector.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/vector.cpp > CMakeFiles/PathTracing.dir/src/vector.cpp.i

CMakeFiles/PathTracing.dir/src/vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/vector.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/vector.cpp -o CMakeFiles/PathTracing.dir/src/vector.cpp.s

CMakeFiles/PathTracing.dir/src/string_reader.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/string_reader.cpp.o: ../src/string_reader.cpp
CMakeFiles/PathTracing.dir/src/string_reader.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PathTracing.dir/src/string_reader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/string_reader.cpp.o -MF CMakeFiles/PathTracing.dir/src/string_reader.cpp.o.d -o CMakeFiles/PathTracing.dir/src/string_reader.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/string_reader.cpp

CMakeFiles/PathTracing.dir/src/string_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/string_reader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/string_reader.cpp > CMakeFiles/PathTracing.dir/src/string_reader.cpp.i

CMakeFiles/PathTracing.dir/src/string_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/string_reader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/string_reader.cpp -o CMakeFiles/PathTracing.dir/src/string_reader.cpp.s

CMakeFiles/PathTracing.dir/src/camera.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/camera.cpp.o: ../src/camera.cpp
CMakeFiles/PathTracing.dir/src/camera.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PathTracing.dir/src/camera.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/camera.cpp.o -MF CMakeFiles/PathTracing.dir/src/camera.cpp.o.d -o CMakeFiles/PathTracing.dir/src/camera.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/camera.cpp

CMakeFiles/PathTracing.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/camera.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/camera.cpp > CMakeFiles/PathTracing.dir/src/camera.cpp.i

CMakeFiles/PathTracing.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/camera.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/camera.cpp -o CMakeFiles/PathTracing.dir/src/camera.cpp.s

CMakeFiles/PathTracing.dir/src/light.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/light.cpp.o: ../src/light.cpp
CMakeFiles/PathTracing.dir/src/light.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PathTracing.dir/src/light.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/light.cpp.o -MF CMakeFiles/PathTracing.dir/src/light.cpp.o.d -o CMakeFiles/PathTracing.dir/src/light.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/light.cpp

CMakeFiles/PathTracing.dir/src/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/light.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/light.cpp > CMakeFiles/PathTracing.dir/src/light.cpp.i

CMakeFiles/PathTracing.dir/src/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/light.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/light.cpp -o CMakeFiles/PathTracing.dir/src/light.cpp.s

CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o: ../src/tiny_obj_loader.cpp
CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o -MF CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o.d -o CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/tiny_obj_loader.cpp

CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/tiny_obj_loader.cpp > CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.i

CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/tiny_obj_loader.cpp -o CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.s

CMakeFiles/PathTracing.dir/src/object.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/object.cpp.o: ../src/object.cpp
CMakeFiles/PathTracing.dir/src/object.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PathTracing.dir/src/object.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/object.cpp.o -MF CMakeFiles/PathTracing.dir/src/object.cpp.o.d -o CMakeFiles/PathTracing.dir/src/object.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/object.cpp

CMakeFiles/PathTracing.dir/src/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/object.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/object.cpp > CMakeFiles/PathTracing.dir/src/object.cpp.i

CMakeFiles/PathTracing.dir/src/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/object.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/object.cpp -o CMakeFiles/PathTracing.dir/src/object.cpp.s

CMakeFiles/PathTracing.dir/src/renderer.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/renderer.cpp.o: ../src/renderer.cpp
CMakeFiles/PathTracing.dir/src/renderer.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PathTracing.dir/src/renderer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/renderer.cpp.o -MF CMakeFiles/PathTracing.dir/src/renderer.cpp.o.d -o CMakeFiles/PathTracing.dir/src/renderer.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/renderer.cpp

CMakeFiles/PathTracing.dir/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/renderer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/renderer.cpp > CMakeFiles/PathTracing.dir/src/renderer.cpp.i

CMakeFiles/PathTracing.dir/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/renderer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/renderer.cpp -o CMakeFiles/PathTracing.dir/src/renderer.cpp.s

CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o: ../src/bvh_node.cpp
CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o -MF CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o.d -o CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/bvh_node.cpp

CMakeFiles/PathTracing.dir/src/bvh_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/bvh_node.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/bvh_node.cpp > CMakeFiles/PathTracing.dir/src/bvh_node.cpp.i

CMakeFiles/PathTracing.dir/src/bvh_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/bvh_node.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/bvh_node.cpp -o CMakeFiles/PathTracing.dir/src/bvh_node.cpp.s

CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o: CMakeFiles/PathTracing.dir/flags.make
CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o: ../src/bvh_tree.cpp
CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o: CMakeFiles/PathTracing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o -MF CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o.d -o CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o -c /Users/liuzhixing/workspace/PathTracing/src/bvh_tree.cpp

CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuzhixing/workspace/PathTracing/src/bvh_tree.cpp > CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.i

CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuzhixing/workspace/PathTracing/src/bvh_tree.cpp -o CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.s

# Object files for target PathTracing
PathTracing_OBJECTS = \
"CMakeFiles/PathTracing.dir/src/main.cpp.o" \
"CMakeFiles/PathTracing.dir/src/vector.cpp.o" \
"CMakeFiles/PathTracing.dir/src/string_reader.cpp.o" \
"CMakeFiles/PathTracing.dir/src/camera.cpp.o" \
"CMakeFiles/PathTracing.dir/src/light.cpp.o" \
"CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o" \
"CMakeFiles/PathTracing.dir/src/object.cpp.o" \
"CMakeFiles/PathTracing.dir/src/renderer.cpp.o" \
"CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o" \
"CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o"

# External object files for target PathTracing
PathTracing_EXTERNAL_OBJECTS =

PathTracing: CMakeFiles/PathTracing.dir/src/main.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/vector.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/string_reader.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/camera.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/light.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/tiny_obj_loader.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/object.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/renderer.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/bvh_node.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/src/bvh_tree.cpp.o
PathTracing: CMakeFiles/PathTracing.dir/build.make
PathTracing: CMakeFiles/PathTracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liuzhixing/workspace/PathTracing/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable PathTracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PathTracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PathTracing.dir/build: PathTracing
.PHONY : CMakeFiles/PathTracing.dir/build

CMakeFiles/PathTracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PathTracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PathTracing.dir/clean

CMakeFiles/PathTracing.dir/depend:
	cd /Users/liuzhixing/workspace/PathTracing/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuzhixing/workspace/PathTracing /Users/liuzhixing/workspace/PathTracing /Users/liuzhixing/workspace/PathTracing/release /Users/liuzhixing/workspace/PathTracing/release /Users/liuzhixing/workspace/PathTracing/release/CMakeFiles/PathTracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PathTracing.dir/depend
