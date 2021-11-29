# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /Users/eovertoo/bin/cmake

# The command to remove a file.
RM = /Users/eovertoo/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/eovertoo/projects-advanced/npuzzle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/eovertoo/projects-advanced/npuzzle

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Users/eovertoo/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Users/eovertoo/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/eovertoo/projects-advanced/npuzzle/CMakeFiles /Users/eovertoo/projects-advanced/npuzzle//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/eovertoo/projects-advanced/npuzzle/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named npuzzle

# Build rule for target.
npuzzle: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 npuzzle
.PHONY : npuzzle

# fast build rule for target.
npuzzle/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/build
.PHONY : npuzzle/fast

Node.o: Node.cpp.o
.PHONY : Node.o

# target to build an object file
Node.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Node.cpp.o
.PHONY : Node.cpp.o

Node.i: Node.cpp.i
.PHONY : Node.i

# target to preprocess a source file
Node.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Node.cpp.i
.PHONY : Node.cpp.i

Node.s: Node.cpp.s
.PHONY : Node.s

# target to generate assembly for a file
Node.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Node.cpp.s
.PHONY : Node.cpp.s

Puzzle.o: Puzzle.cpp.o
.PHONY : Puzzle.o

# target to build an object file
Puzzle.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Puzzle.cpp.o
.PHONY : Puzzle.cpp.o

Puzzle.i: Puzzle.cpp.i
.PHONY : Puzzle.i

# target to preprocess a source file
Puzzle.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Puzzle.cpp.i
.PHONY : Puzzle.cpp.i

Puzzle.s: Puzzle.cpp.s
.PHONY : Puzzle.s

# target to generate assembly for a file
Puzzle.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/Puzzle.cpp.s
.PHONY : Puzzle.cpp.s

getinput.o: getinput.cpp.o
.PHONY : getinput.o

# target to build an object file
getinput.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/getinput.cpp.o
.PHONY : getinput.cpp.o

getinput.i: getinput.cpp.i
.PHONY : getinput.i

# target to preprocess a source file
getinput.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/getinput.cpp.i
.PHONY : getinput.cpp.i

getinput.s: getinput.cpp.s
.PHONY : getinput.s

# target to generate assembly for a file
getinput.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/getinput.cpp.s
.PHONY : getinput.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/main.cpp.s
.PHONY : main.cpp.s

readfile.o: readfile.cpp.o
.PHONY : readfile.o

# target to build an object file
readfile.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/readfile.cpp.o
.PHONY : readfile.cpp.o

readfile.i: readfile.cpp.i
.PHONY : readfile.i

# target to preprocess a source file
readfile.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/readfile.cpp.i
.PHONY : readfile.cpp.i

readfile.s: readfile.cpp.s
.PHONY : readfile.s

# target to generate assembly for a file
readfile.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/readfile.cpp.s
.PHONY : readfile.cpp.s

solvable.o: solvable.cpp.o
.PHONY : solvable.o

# target to build an object file
solvable.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/solvable.cpp.o
.PHONY : solvable.cpp.o

solvable.i: solvable.cpp.i
.PHONY : solvable.i

# target to preprocess a source file
solvable.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/solvable.cpp.i
.PHONY : solvable.cpp.i

solvable.s: solvable.cpp.s
.PHONY : solvable.s

# target to generate assembly for a file
solvable.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/npuzzle.dir/build.make CMakeFiles/npuzzle.dir/solvable.cpp.s
.PHONY : solvable.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... npuzzle"
	@echo "... Node.o"
	@echo "... Node.i"
	@echo "... Node.s"
	@echo "... Puzzle.o"
	@echo "... Puzzle.i"
	@echo "... Puzzle.s"
	@echo "... getinput.o"
	@echo "... getinput.i"
	@echo "... getinput.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... readfile.o"
	@echo "... readfile.i"
	@echo "... readfile.s"
	@echo "... solvable.o"
	@echo "... solvable.i"
	@echo "... solvable.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

