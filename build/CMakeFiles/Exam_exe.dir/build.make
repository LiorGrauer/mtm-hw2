# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build"

# Include any dependencies generated for this target.
include CMakeFiles/Exam_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exam_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exam_exe.dir/flags.make

CMakeFiles/Exam_exe.dir/part_a_test.cpp.obj: CMakeFiles/Exam_exe.dir/flags.make
CMakeFiles/Exam_exe.dir/part_a_test.cpp.obj: ../part_a_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Exam_exe.dir/part_a_test.cpp.obj"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Exam_exe.dir\part_a_test.cpp.obj -c "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\part_a_test.cpp"

CMakeFiles/Exam_exe.dir/part_a_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Exam_exe.dir/part_a_test.cpp.i"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\part_a_test.cpp" > CMakeFiles\Exam_exe.dir\part_a_test.cpp.i

CMakeFiles/Exam_exe.dir/part_a_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Exam_exe.dir/part_a_test.cpp.s"
	C:\TDM-GCC-64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\part_a_test.cpp" -o CMakeFiles\Exam_exe.dir\part_a_test.cpp.s

# Object files for target Exam_exe
Exam_exe_OBJECTS = \
"CMakeFiles/Exam_exe.dir/part_a_test.cpp.obj"

# External object files for target Exam_exe
Exam_exe_EXTERNAL_OBJECTS =

Exam_exe.exe: CMakeFiles/Exam_exe.dir/part_a_test.cpp.obj
Exam_exe.exe: CMakeFiles/Exam_exe.dir/build.make
Exam_exe.exe: CMakeFiles/Exam_exe.dir/linklibs.rsp
Exam_exe.exe: CMakeFiles/Exam_exe.dir/objects1.rsp
Exam_exe.exe: CMakeFiles/Exam_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Exam_exe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Exam_exe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exam_exe.dir/build: Exam_exe.exe

.PHONY : CMakeFiles/Exam_exe.dir/build

CMakeFiles/Exam_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Exam_exe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Exam_exe.dir/clean

CMakeFiles/Exam_exe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2" "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2" "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build" "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build" "C:\Users\liorg\OneDrive - Technion\Documents\GitHub\mtm-hw2\build\CMakeFiles\Exam_exe.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Exam_exe.dir/depend

