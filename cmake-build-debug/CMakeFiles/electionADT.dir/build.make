# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/electionADT.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/electionADT.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/electionADT.dir/flags.make

CMakeFiles/electionADT.dir/main.c.o: CMakeFiles/electionADT.dir/flags.make
CMakeFiles/electionADT.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/electionADT.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/electionADT.dir/main.c.o   -c "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/main.c"

CMakeFiles/electionADT.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/electionADT.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/main.c" > CMakeFiles/electionADT.dir/main.c.i

CMakeFiles/electionADT.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/electionADT.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/main.c" -o CMakeFiles/electionADT.dir/main.c.s

# Object files for target electionADT
electionADT_OBJECTS = \
"CMakeFiles/electionADT.dir/main.c.o"

# External object files for target electionADT
electionADT_EXTERNAL_OBJECTS =

electionADT: CMakeFiles/electionADT.dir/main.c.o
electionADT: CMakeFiles/electionADT.dir/build.make
electionADT: CMakeFiles/electionADT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable electionADT"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/electionADT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/electionADT.dir/build: electionADT

.PHONY : CMakeFiles/electionADT.dir/build

CMakeFiles/electionADT.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/electionADT.dir/cmake_clean.cmake
.PHONY : CMakeFiles/electionADT.dir/clean

CMakeFiles/electionADT.dir/depend:
	cd "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT" "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT" "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug" "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug" "/Users/rond/Desktop/רון/טכניון/מבוא לתכנות מערכות/hw1/electionADT/cmake-build-debug/CMakeFiles/electionADT.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/electionADT.dir/depend
