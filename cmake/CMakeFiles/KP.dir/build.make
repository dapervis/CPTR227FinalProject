# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/Final/CPTR227FinalProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Final/CPTR227FinalProject/cmake

# Include any dependencies generated for this target.
include CMakeFiles/KP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KP.dir/flags.make

CMakeFiles/KP.dir/src/main.cpp.o: CMakeFiles/KP.dir/flags.make
CMakeFiles/KP.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/Final/CPTR227FinalProject/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KP.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KP.dir/src/main.cpp.o -c /home/daniel/Final/CPTR227FinalProject/src/main.cpp

CMakeFiles/KP.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KP.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/Final/CPTR227FinalProject/src/main.cpp > CMakeFiles/KP.dir/src/main.cpp.i

CMakeFiles/KP.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KP.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/Final/CPTR227FinalProject/src/main.cpp -o CMakeFiles/KP.dir/src/main.cpp.s

# Object files for target KP
KP_OBJECTS = \
"CMakeFiles/KP.dir/src/main.cpp.o"

# External object files for target KP
KP_EXTERNAL_OBJECTS =

KP: CMakeFiles/KP.dir/src/main.cpp.o
KP: CMakeFiles/KP.dir/build.make
KP: CMakeFiles/KP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniel/Final/CPTR227FinalProject/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable KP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KP.dir/build: KP

.PHONY : CMakeFiles/KP.dir/build

CMakeFiles/KP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KP.dir/clean

CMakeFiles/KP.dir/depend:
	cd /home/daniel/Final/CPTR227FinalProject/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Final/CPTR227FinalProject /home/daniel/Final/CPTR227FinalProject /home/daniel/Final/CPTR227FinalProject/cmake /home/daniel/Final/CPTR227FinalProject/cmake /home/daniel/Final/CPTR227FinalProject/cmake/CMakeFiles/KP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KP.dir/depend

