# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/kivi/workspace/parallel/parallel-mpi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kivi/workspace/parallel/parallel-mpi

# Include any dependencies generated for this target.
include CMakeFiles/parallel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/parallel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/parallel.dir/flags.make

CMakeFiles/parallel.dir/main.cpp.o: CMakeFiles/parallel.dir/flags.make
CMakeFiles/parallel.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kivi/workspace/parallel/parallel-mpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/parallel.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/parallel.dir/main.cpp.o -c /home/kivi/workspace/parallel/parallel-mpi/main.cpp

CMakeFiles/parallel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parallel.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kivi/workspace/parallel/parallel-mpi/main.cpp > CMakeFiles/parallel.dir/main.cpp.i

CMakeFiles/parallel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parallel.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kivi/workspace/parallel/parallel-mpi/main.cpp -o CMakeFiles/parallel.dir/main.cpp.s

CMakeFiles/parallel.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/parallel.dir/main.cpp.o.requires

CMakeFiles/parallel.dir/main.cpp.o.provides: CMakeFiles/parallel.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/parallel.dir/build.make CMakeFiles/parallel.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/parallel.dir/main.cpp.o.provides

CMakeFiles/parallel.dir/main.cpp.o.provides.build: CMakeFiles/parallel.dir/main.cpp.o


# Object files for target parallel
parallel_OBJECTS = \
"CMakeFiles/parallel.dir/main.cpp.o"

# External object files for target parallel
parallel_EXTERNAL_OBJECTS =

parallel: CMakeFiles/parallel.dir/main.cpp.o
parallel: CMakeFiles/parallel.dir/build.make
parallel: /usr/lib/openmpi/lib/libmpi_cxx.so
parallel: /usr/lib/openmpi/lib/libmpi.so
parallel: CMakeFiles/parallel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kivi/workspace/parallel/parallel-mpi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable parallel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parallel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/parallel.dir/build: parallel

.PHONY : CMakeFiles/parallel.dir/build

CMakeFiles/parallel.dir/requires: CMakeFiles/parallel.dir/main.cpp.o.requires

.PHONY : CMakeFiles/parallel.dir/requires

CMakeFiles/parallel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/parallel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/parallel.dir/clean

CMakeFiles/parallel.dir/depend:
	cd /home/kivi/workspace/parallel/parallel-mpi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kivi/workspace/parallel/parallel-mpi /home/kivi/workspace/parallel/parallel-mpi /home/kivi/workspace/parallel/parallel-mpi /home/kivi/workspace/parallel/parallel-mpi /home/kivi/workspace/parallel/parallel-mpi/CMakeFiles/parallel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/parallel.dir/depend

