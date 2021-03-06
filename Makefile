# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/anon/Work/gridfire_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anon/Work/gridfire_c

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local

.PHONY : install/local/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/anon/Work/gridfire_c/CMakeFiles /home/anon/Work/gridfire_c/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/anon/Work/gridfire_c/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named all_unity

# Build rule for target.
all_unity: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 all_unity
.PHONY : all_unity

# fast build rule for target.
all_unity/fast:
	$(MAKE) -f CMakeFiles/all_unity.dir/build.make CMakeFiles/all_unity.dir/build
.PHONY : all_unity/fast

#=============================================================================
# Target rules for targets named gridfire

# Build rule for target.
gridfire: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gridfire
.PHONY : gridfire

# fast build rule for target.
gridfire/fast:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/build
.PHONY : gridfire/fast

# Manual pre-install relink rule for target.
gridfire/preinstall:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/preinstall
.PHONY : gridfire/preinstall

#=============================================================================
# Target rules for targets named gridfire_pch

# Build rule for target.
gridfire_pch: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gridfire_pch
.PHONY : gridfire_pch

# fast build rule for target.
gridfire_pch/fast:
	$(MAKE) -f CMakeFiles/gridfire_pch.dir/build.make CMakeFiles/gridfire_pch.dir/build
.PHONY : gridfire_pch/fast

#=============================================================================
# Target rules for targets named clean_cotire

# Build rule for target.
clean_cotire: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 clean_cotire
.PHONY : clean_cotire

# fast build rule for target.
clean_cotire/fast:
	$(MAKE) -f CMakeFiles/clean_cotire.dir/build.make CMakeFiles/clean_cotire.dir/build
.PHONY : clean_cotire/fast

#=============================================================================
# Target rules for targets named all_pch

# Build rule for target.
all_pch: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 all_pch
.PHONY : all_pch

# fast build rule for target.
all_pch/fast:
	$(MAKE) -f CMakeFiles/all_pch.dir/build.make CMakeFiles/all_pch.dir/build
.PHONY : all_pch/fast

#=============================================================================
# Target rules for targets named gridfire_unity

# Build rule for target.
gridfire_unity: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gridfire_unity
.PHONY : gridfire_unity

# fast build rule for target.
gridfire_unity/fast:
	$(MAKE) -f CMakeFiles/gridfire_unity.dir/build.make CMakeFiles/gridfire_unity.dir/build
.PHONY : gridfire_unity/fast

cotire/gridfire_C_unity.o: cotire/gridfire_C_unity.c.o

.PHONY : cotire/gridfire_C_unity.o

# target to build an object file
cotire/gridfire_C_unity.c.o:
	$(MAKE) -f CMakeFiles/gridfire_unity.dir/build.make CMakeFiles/gridfire_unity.dir/cotire/gridfire_C_unity.c.o
.PHONY : cotire/gridfire_C_unity.c.o

cotire/gridfire_C_unity.i: cotire/gridfire_C_unity.c.i

.PHONY : cotire/gridfire_C_unity.i

# target to preprocess a source file
cotire/gridfire_C_unity.c.i:
	$(MAKE) -f CMakeFiles/gridfire_unity.dir/build.make CMakeFiles/gridfire_unity.dir/cotire/gridfire_C_unity.c.i
.PHONY : cotire/gridfire_C_unity.c.i

cotire/gridfire_C_unity.s: cotire/gridfire_C_unity.c.s

.PHONY : cotire/gridfire_C_unity.s

# target to generate assembly for a file
cotire/gridfire_C_unity.c.s:
	$(MAKE) -f CMakeFiles/gridfire_unity.dir/build.make CMakeFiles/gridfire_unity.dir/cotire/gridfire_C_unity.c.s
.PHONY : cotire/gridfire_C_unity.c.s

src/engine/game_object.o: src/engine/game_object.c.o

.PHONY : src/engine/game_object.o

# target to build an object file
src/engine/game_object.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_object.c.o
.PHONY : src/engine/game_object.c.o

src/engine/game_object.i: src/engine/game_object.c.i

.PHONY : src/engine/game_object.i

# target to preprocess a source file
src/engine/game_object.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_object.c.i
.PHONY : src/engine/game_object.c.i

src/engine/game_object.s: src/engine/game_object.c.s

.PHONY : src/engine/game_object.s

# target to generate assembly for a file
src/engine/game_object.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_object.c.s
.PHONY : src/engine/game_object.c.s

src/engine/game_ui.o: src/engine/game_ui.c.o

.PHONY : src/engine/game_ui.o

# target to build an object file
src/engine/game_ui.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_ui.c.o
.PHONY : src/engine/game_ui.c.o

src/engine/game_ui.i: src/engine/game_ui.c.i

.PHONY : src/engine/game_ui.i

# target to preprocess a source file
src/engine/game_ui.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_ui.c.i
.PHONY : src/engine/game_ui.c.i

src/engine/game_ui.s: src/engine/game_ui.c.s

.PHONY : src/engine/game_ui.s

# target to generate assembly for a file
src/engine/game_ui.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/game_ui.c.s
.PHONY : src/engine/game_ui.c.s

src/engine/radar.o: src/engine/radar.c.o

.PHONY : src/engine/radar.o

# target to build an object file
src/engine/radar.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/radar.c.o
.PHONY : src/engine/radar.c.o

src/engine/radar.i: src/engine/radar.c.i

.PHONY : src/engine/radar.i

# target to preprocess a source file
src/engine/radar.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/radar.c.i
.PHONY : src/engine/radar.c.i

src/engine/radar.s: src/engine/radar.c.s

.PHONY : src/engine/radar.s

# target to generate assembly for a file
src/engine/radar.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/radar.c.s
.PHONY : src/engine/radar.c.s

src/engine/starfield.o: src/engine/starfield.c.o

.PHONY : src/engine/starfield.o

# target to build an object file
src/engine/starfield.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/starfield.c.o
.PHONY : src/engine/starfield.c.o

src/engine/starfield.i: src/engine/starfield.c.i

.PHONY : src/engine/starfield.i

# target to preprocess a source file
src/engine/starfield.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/starfield.c.i
.PHONY : src/engine/starfield.c.i

src/engine/starfield.s: src/engine/starfield.c.s

.PHONY : src/engine/starfield.s

# target to generate assembly for a file
src/engine/starfield.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/starfield.c.s
.PHONY : src/engine/starfield.c.s

src/engine/weapon_control.o: src/engine/weapon_control.c.o

.PHONY : src/engine/weapon_control.o

# target to build an object file
src/engine/weapon_control.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/weapon_control.c.o
.PHONY : src/engine/weapon_control.c.o

src/engine/weapon_control.i: src/engine/weapon_control.c.i

.PHONY : src/engine/weapon_control.i

# target to preprocess a source file
src/engine/weapon_control.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/weapon_control.c.i
.PHONY : src/engine/weapon_control.c.i

src/engine/weapon_control.s: src/engine/weapon_control.c.s

.PHONY : src/engine/weapon_control.s

# target to generate assembly for a file
src/engine/weapon_control.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/engine/weapon_control.c.s
.PHONY : src/engine/weapon_control.c.s

src/game.o: src/game.c.o

.PHONY : src/game.o

# target to build an object file
src/game.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/game.c.o
.PHONY : src/game.c.o

src/game.i: src/game.c.i

.PHONY : src/game.i

# target to preprocess a source file
src/game.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/game.c.i
.PHONY : src/game.c.i

src/game.s: src/game.c.s

.PHONY : src/game.s

# target to generate assembly for a file
src/game.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/game.c.s
.PHONY : src/game.c.s

src/gridfire.o: src/gridfire.c.o

.PHONY : src/gridfire.o

# target to build an object file
src/gridfire.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/gridfire.c.o
.PHONY : src/gridfire.c.o

src/gridfire.i: src/gridfire.c.i

.PHONY : src/gridfire.i

# target to preprocess a source file
src/gridfire.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/gridfire.c.i
.PHONY : src/gridfire.c.i

src/gridfire.s: src/gridfire.c.s

.PHONY : src/gridfire.s

# target to generate assembly for a file
src/gridfire.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/gridfire.c.s
.PHONY : src/gridfire.c.s

src/logic/audio_control.o: src/logic/audio_control.c.o

.PHONY : src/logic/audio_control.o

# target to build an object file
src/logic/audio_control.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/audio_control.c.o
.PHONY : src/logic/audio_control.c.o

src/logic/audio_control.i: src/logic/audio_control.c.i

.PHONY : src/logic/audio_control.i

# target to preprocess a source file
src/logic/audio_control.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/audio_control.c.i
.PHONY : src/logic/audio_control.c.i

src/logic/audio_control.s: src/logic/audio_control.c.s

.PHONY : src/logic/audio_control.s

# target to generate assembly for a file
src/logic/audio_control.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/audio_control.c.s
.PHONY : src/logic/audio_control.c.s

src/logic/cartographer.o: src/logic/cartographer.c.o

.PHONY : src/logic/cartographer.o

# target to build an object file
src/logic/cartographer.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/cartographer.c.o
.PHONY : src/logic/cartographer.c.o

src/logic/cartographer.i: src/logic/cartographer.c.i

.PHONY : src/logic/cartographer.i

# target to preprocess a source file
src/logic/cartographer.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/cartographer.c.i
.PHONY : src/logic/cartographer.c.i

src/logic/cartographer.s: src/logic/cartographer.c.s

.PHONY : src/logic/cartographer.s

# target to generate assembly for a file
src/logic/cartographer.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/cartographer.c.s
.PHONY : src/logic/cartographer.c.s

src/logic/game_ai.o: src/logic/game_ai.c.o

.PHONY : src/logic/game_ai.o

# target to build an object file
src/logic/game_ai.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/game_ai.c.o
.PHONY : src/logic/game_ai.c.o

src/logic/game_ai.i: src/logic/game_ai.c.i

.PHONY : src/logic/game_ai.i

# target to preprocess a source file
src/logic/game_ai.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/game_ai.c.i
.PHONY : src/logic/game_ai.c.i

src/logic/game_ai.s: src/logic/game_ai.c.s

.PHONY : src/logic/game_ai.s

# target to generate assembly for a file
src/logic/game_ai.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/game_ai.c.s
.PHONY : src/logic/game_ai.c.s

src/logic/scoreboard.o: src/logic/scoreboard.c.o

.PHONY : src/logic/scoreboard.o

# target to build an object file
src/logic/scoreboard.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/scoreboard.c.o
.PHONY : src/logic/scoreboard.c.o

src/logic/scoreboard.i: src/logic/scoreboard.c.i

.PHONY : src/logic/scoreboard.i

# target to preprocess a source file
src/logic/scoreboard.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/scoreboard.c.i
.PHONY : src/logic/scoreboard.c.i

src/logic/scoreboard.s: src/logic/scoreboard.c.s

.PHONY : src/logic/scoreboard.s

# target to generate assembly for a file
src/logic/scoreboard.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/logic/scoreboard.c.s
.PHONY : src/logic/scoreboard.c.s

src/utils/config_parser.o: src/utils/config_parser.c.o

.PHONY : src/utils/config_parser.o

# target to build an object file
src/utils/config_parser.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/config_parser.c.o
.PHONY : src/utils/config_parser.c.o

src/utils/config_parser.i: src/utils/config_parser.c.i

.PHONY : src/utils/config_parser.i

# target to preprocess a source file
src/utils/config_parser.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/config_parser.c.i
.PHONY : src/utils/config_parser.c.i

src/utils/config_parser.s: src/utils/config_parser.c.s

.PHONY : src/utils/config_parser.s

# target to generate assembly for a file
src/utils/config_parser.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/config_parser.c.s
.PHONY : src/utils/config_parser.c.s

src/utils/geometry.o: src/utils/geometry.c.o

.PHONY : src/utils/geometry.o

# target to build an object file
src/utils/geometry.c.o:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/geometry.c.o
.PHONY : src/utils/geometry.c.o

src/utils/geometry.i: src/utils/geometry.c.i

.PHONY : src/utils/geometry.i

# target to preprocess a source file
src/utils/geometry.c.i:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/geometry.c.i
.PHONY : src/utils/geometry.c.i

src/utils/geometry.s: src/utils/geometry.c.s

.PHONY : src/utils/geometry.s

# target to generate assembly for a file
src/utils/geometry.c.s:
	$(MAKE) -f CMakeFiles/gridfire.dir/build.make CMakeFiles/gridfire.dir/src/utils/geometry.c.s
.PHONY : src/utils/geometry.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install"
	@echo "... all_unity"
	@echo "... gridfire"
	@echo "... rebuild_cache"
	@echo "... gridfire_pch"
	@echo "... clean_cotire"
	@echo "... all_pch"
	@echo "... gridfire_unity"
	@echo "... install/local"
	@echo "... edit_cache"
	@echo "... list_install_components"
	@echo "... cotire/gridfire_C_unity.o"
	@echo "... cotire/gridfire_C_unity.i"
	@echo "... cotire/gridfire_C_unity.s"
	@echo "... src/engine/game_object.o"
	@echo "... src/engine/game_object.i"
	@echo "... src/engine/game_object.s"
	@echo "... src/engine/game_ui.o"
	@echo "... src/engine/game_ui.i"
	@echo "... src/engine/game_ui.s"
	@echo "... src/engine/radar.o"
	@echo "... src/engine/radar.i"
	@echo "... src/engine/radar.s"
	@echo "... src/engine/starfield.o"
	@echo "... src/engine/starfield.i"
	@echo "... src/engine/starfield.s"
	@echo "... src/engine/weapon_control.o"
	@echo "... src/engine/weapon_control.i"
	@echo "... src/engine/weapon_control.s"
	@echo "... src/game.o"
	@echo "... src/game.i"
	@echo "... src/game.s"
	@echo "... src/gridfire.o"
	@echo "... src/gridfire.i"
	@echo "... src/gridfire.s"
	@echo "... src/logic/audio_control.o"
	@echo "... src/logic/audio_control.i"
	@echo "... src/logic/audio_control.s"
	@echo "... src/logic/cartographer.o"
	@echo "... src/logic/cartographer.i"
	@echo "... src/logic/cartographer.s"
	@echo "... src/logic/game_ai.o"
	@echo "... src/logic/game_ai.i"
	@echo "... src/logic/game_ai.s"
	@echo "... src/logic/scoreboard.o"
	@echo "... src/logic/scoreboard.i"
	@echo "... src/logic/scoreboard.s"
	@echo "... src/utils/config_parser.o"
	@echo "... src/utils/config_parser.i"
	@echo "... src/utils/config_parser.s"
	@echo "... src/utils/geometry.o"
	@echo "... src/utils/geometry.i"
	@echo "... src/utils/geometry.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

