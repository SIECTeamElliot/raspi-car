# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/yop/Programmation/Projets/CarPark/raspi_car

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yop/Programmation/Projets/CarPark/raspi_car/build

# Include any dependencies generated for this target.
include CMakeFiles/exec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exec.dir/flags.make

CMakeFiles/exec.dir/src/init_all.c.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/init_all.c.o: ../src/init_all.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yop/Programmation/Projets/CarPark/raspi_car/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/exec.dir/src/init_all.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exec.dir/src/init_all.c.o   -c /home/yop/Programmation/Projets/CarPark/raspi_car/src/init_all.c

CMakeFiles/exec.dir/src/init_all.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exec.dir/src/init_all.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yop/Programmation/Projets/CarPark/raspi_car/src/init_all.c > CMakeFiles/exec.dir/src/init_all.c.i

CMakeFiles/exec.dir/src/init_all.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exec.dir/src/init_all.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yop/Programmation/Projets/CarPark/raspi_car/src/init_all.c -o CMakeFiles/exec.dir/src/init_all.c.s

CMakeFiles/exec.dir/src/init_all.c.o.requires:

.PHONY : CMakeFiles/exec.dir/src/init_all.c.o.requires

CMakeFiles/exec.dir/src/init_all.c.o.provides: CMakeFiles/exec.dir/src/init_all.c.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/init_all.c.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/init_all.c.o.provides

CMakeFiles/exec.dir/src/init_all.c.o.provides.build: CMakeFiles/exec.dir/src/init_all.c.o


CMakeFiles/exec.dir/src/communicationSTM.c.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/communicationSTM.c.o: ../src/communicationSTM.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yop/Programmation/Projets/CarPark/raspi_car/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/exec.dir/src/communicationSTM.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exec.dir/src/communicationSTM.c.o   -c /home/yop/Programmation/Projets/CarPark/raspi_car/src/communicationSTM.c

CMakeFiles/exec.dir/src/communicationSTM.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exec.dir/src/communicationSTM.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yop/Programmation/Projets/CarPark/raspi_car/src/communicationSTM.c > CMakeFiles/exec.dir/src/communicationSTM.c.i

CMakeFiles/exec.dir/src/communicationSTM.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exec.dir/src/communicationSTM.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yop/Programmation/Projets/CarPark/raspi_car/src/communicationSTM.c -o CMakeFiles/exec.dir/src/communicationSTM.c.s

CMakeFiles/exec.dir/src/communicationSTM.c.o.requires:

.PHONY : CMakeFiles/exec.dir/src/communicationSTM.c.o.requires

CMakeFiles/exec.dir/src/communicationSTM.c.o.provides: CMakeFiles/exec.dir/src/communicationSTM.c.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/communicationSTM.c.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/communicationSTM.c.o.provides

CMakeFiles/exec.dir/src/communicationSTM.c.o.provides.build: CMakeFiles/exec.dir/src/communicationSTM.c.o


CMakeFiles/exec.dir/src/listen.c.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/listen.c.o: ../src/listen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yop/Programmation/Projets/CarPark/raspi_car/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/exec.dir/src/listen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/exec.dir/src/listen.c.o   -c /home/yop/Programmation/Projets/CarPark/raspi_car/src/listen.c

CMakeFiles/exec.dir/src/listen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/exec.dir/src/listen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yop/Programmation/Projets/CarPark/raspi_car/src/listen.c > CMakeFiles/exec.dir/src/listen.c.i

CMakeFiles/exec.dir/src/listen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/exec.dir/src/listen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yop/Programmation/Projets/CarPark/raspi_car/src/listen.c -o CMakeFiles/exec.dir/src/listen.c.s

CMakeFiles/exec.dir/src/listen.c.o.requires:

.PHONY : CMakeFiles/exec.dir/src/listen.c.o.requires

CMakeFiles/exec.dir/src/listen.c.o.provides: CMakeFiles/exec.dir/src/listen.c.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/listen.c.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/listen.c.o.provides

CMakeFiles/exec.dir/src/listen.c.o.provides.build: CMakeFiles/exec.dir/src/listen.c.o


# Object files for target exec
exec_OBJECTS = \
"CMakeFiles/exec.dir/src/init_all.c.o" \
"CMakeFiles/exec.dir/src/communicationSTM.c.o" \
"CMakeFiles/exec.dir/src/listen.c.o"

# External object files for target exec
exec_EXTERNAL_OBJECTS =

build/bin/exec: CMakeFiles/exec.dir/src/init_all.c.o
build/bin/exec: CMakeFiles/exec.dir/src/communicationSTM.c.o
build/bin/exec: CMakeFiles/exec.dir/src/listen.c.o
build/bin/exec: CMakeFiles/exec.dir/build.make
build/bin/exec: CMakeFiles/exec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yop/Programmation/Projets/CarPark/raspi_car/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable build/bin/exec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exec.dir/build: build/bin/exec

.PHONY : CMakeFiles/exec.dir/build

CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/init_all.c.o.requires
CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/communicationSTM.c.o.requires
CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/listen.c.o.requires

.PHONY : CMakeFiles/exec.dir/requires

CMakeFiles/exec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exec.dir/clean

CMakeFiles/exec.dir/depend:
	cd /home/yop/Programmation/Projets/CarPark/raspi_car/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yop/Programmation/Projets/CarPark/raspi_car /home/yop/Programmation/Projets/CarPark/raspi_car /home/yop/Programmation/Projets/CarPark/raspi_car/build /home/yop/Programmation/Projets/CarPark/raspi_car/build /home/yop/Programmation/Projets/CarPark/raspi_car/build/CMakeFiles/exec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exec.dir/depend

