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
CMAKE_SOURCE_DIR = /home/orangepi/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orangepi/catkin_ws/build

# Utility rule file for hcsr04_generate_messages_py.

# Include the progress variables for this target.
include hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/progress.make

hcsr04/CMakeFiles/hcsr04_generate_messages_py: /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/_distance.py
hcsr04/CMakeFiles/hcsr04_generate_messages_py: /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/__init__.py


/home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/_distance.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/_distance.py: /home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/orangepi/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Python from MSG hcsr04/distance"
	cd /home/orangepi/catkin_ws/build/hcsr04 && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py /home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg -Ihcsr04:/home/orangepi/catkin_ws/src/hcsr04/msg -Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg -Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg -Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg -p hcsr04 -o /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg

/home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/__init__.py: /opt/ros/noetic/lib/genpy/genmsg_py.py
/home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/__init__.py: /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/_distance.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/orangepi/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating Python msg __init__.py for hcsr04"
	cd /home/orangepi/catkin_ws/build/hcsr04 && ../catkin_generated/env_cached.sh /usr/bin/python3 /opt/ros/noetic/share/genpy/cmake/../../../lib/genpy/genmsg_py.py -o /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg --initpy

hcsr04_generate_messages_py: hcsr04/CMakeFiles/hcsr04_generate_messages_py
hcsr04_generate_messages_py: /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/_distance.py
hcsr04_generate_messages_py: /home/orangepi/catkin_ws/devel/lib/python3/dist-packages/hcsr04/msg/__init__.py
hcsr04_generate_messages_py: hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/build.make

.PHONY : hcsr04_generate_messages_py

# Rule to build all files generated by this target.
hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/build: hcsr04_generate_messages_py

.PHONY : hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/build

hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/clean:
	cd /home/orangepi/catkin_ws/build/hcsr04 && $(CMAKE_COMMAND) -P CMakeFiles/hcsr04_generate_messages_py.dir/cmake_clean.cmake
.PHONY : hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/clean

hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/depend:
	cd /home/orangepi/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orangepi/catkin_ws/src /home/orangepi/catkin_ws/src/hcsr04 /home/orangepi/catkin_ws/build /home/orangepi/catkin_ws/build/hcsr04 /home/orangepi/catkin_ws/build/hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hcsr04/CMakeFiles/hcsr04_generate_messages_py.dir/depend

