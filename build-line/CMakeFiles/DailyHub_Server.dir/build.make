# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/henrique/A/backend-dh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/henrique/A/backend-dh/build-line

# Include any dependencies generated for this target.
include CMakeFiles/DailyHub_Server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DailyHub_Server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DailyHub_Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DailyHub_Server.dir/flags.make

CMakeFiles/DailyHub_Server.dir/src/main.cpp.o: CMakeFiles/DailyHub_Server.dir/flags.make
CMakeFiles/DailyHub_Server.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/DailyHub_Server.dir/src/main.cpp.o: CMakeFiles/DailyHub_Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DailyHub_Server.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DailyHub_Server.dir/src/main.cpp.o -MF CMakeFiles/DailyHub_Server.dir/src/main.cpp.o.d -o CMakeFiles/DailyHub_Server.dir/src/main.cpp.o -c /media/henrique/A/backend-dh/src/main.cpp

CMakeFiles/DailyHub_Server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DailyHub_Server.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/henrique/A/backend-dh/src/main.cpp > CMakeFiles/DailyHub_Server.dir/src/main.cpp.i

CMakeFiles/DailyHub_Server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DailyHub_Server.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/henrique/A/backend-dh/src/main.cpp -o CMakeFiles/DailyHub_Server.dir/src/main.cpp.s

CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o: CMakeFiles/DailyHub_Server.dir/flags.make
CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o: ../src/core/server.cpp
CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o: CMakeFiles/DailyHub_Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o -MF CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o.d -o CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o -c /media/henrique/A/backend-dh/src/core/server.cpp

CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/henrique/A/backend-dh/src/core/server.cpp > CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.i

CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/henrique/A/backend-dh/src/core/server.cpp -o CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.s

CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o: CMakeFiles/DailyHub_Server.dir/flags.make
CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o: ../src/core/utility.cpp
CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o: CMakeFiles/DailyHub_Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o -MF CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o.d -o CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o -c /media/henrique/A/backend-dh/src/core/utility.cpp

CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/henrique/A/backend-dh/src/core/utility.cpp > CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.i

CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/henrique/A/backend-dh/src/core/utility.cpp -o CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.s

CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o: CMakeFiles/DailyHub_Server.dir/flags.make
CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o: ../src/core/database.cpp
CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o: CMakeFiles/DailyHub_Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o -MF CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o.d -o CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o -c /media/henrique/A/backend-dh/src/core/database.cpp

CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/henrique/A/backend-dh/src/core/database.cpp > CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.i

CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/henrique/A/backend-dh/src/core/database.cpp -o CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.s

CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o: CMakeFiles/DailyHub_Server.dir/flags.make
CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o: ../src/core/rest_client.cpp
CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o: CMakeFiles/DailyHub_Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o -MF CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o.d -o CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o -c /media/henrique/A/backend-dh/src/core/rest_client.cpp

CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/henrique/A/backend-dh/src/core/rest_client.cpp > CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.i

CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/henrique/A/backend-dh/src/core/rest_client.cpp -o CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.s

# Object files for target DailyHub_Server
DailyHub_Server_OBJECTS = \
"CMakeFiles/DailyHub_Server.dir/src/main.cpp.o" \
"CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o" \
"CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o" \
"CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o" \
"CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o"

# External object files for target DailyHub_Server
DailyHub_Server_EXTERNAL_OBJECTS =

DailyHub_Server: CMakeFiles/DailyHub_Server.dir/src/main.cpp.o
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/src/core/server.cpp.o
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/src/core/utility.cpp.o
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/src/core/database.cpp.o
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/src/core/rest_client.cpp.o
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/build.make
DailyHub_Server: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.9.2
DailyHub_Server: /usr/lib/x86_64-linux-gnu/libcurl.so
DailyHub_Server: /usr/lib/x86_64-linux-gnu/libpq.so
DailyHub_Server: /usr/lib/x86_64-linux-gnu/libfmt.so.8.1.1
DailyHub_Server: CMakeFiles/DailyHub_Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/henrique/A/backend-dh/build-line/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable DailyHub_Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DailyHub_Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DailyHub_Server.dir/build: DailyHub_Server
.PHONY : CMakeFiles/DailyHub_Server.dir/build

CMakeFiles/DailyHub_Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DailyHub_Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DailyHub_Server.dir/clean

CMakeFiles/DailyHub_Server.dir/depend:
	cd /media/henrique/A/backend-dh/build-line && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/henrique/A/backend-dh /media/henrique/A/backend-dh /media/henrique/A/backend-dh/build-line /media/henrique/A/backend-dh/build-line /media/henrique/A/backend-dh/build-line/CMakeFiles/DailyHub_Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DailyHub_Server.dir/depend

