# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hcsr04: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ihcsr04:/home/orangepi/catkin_ws/src/hcsr04/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hcsr04_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_custom_target(_hcsr04_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hcsr04" "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hcsr04
  "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hcsr04
)

### Generating Services

### Generating Module File
_generate_module_cpp(hcsr04
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hcsr04
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hcsr04_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hcsr04_generate_messages hcsr04_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_dependencies(hcsr04_generate_messages_cpp _hcsr04_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hcsr04_gencpp)
add_dependencies(hcsr04_gencpp hcsr04_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hcsr04_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(hcsr04
  "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hcsr04
)

### Generating Services

### Generating Module File
_generate_module_eus(hcsr04
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hcsr04
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(hcsr04_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(hcsr04_generate_messages hcsr04_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_dependencies(hcsr04_generate_messages_eus _hcsr04_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hcsr04_geneus)
add_dependencies(hcsr04_geneus hcsr04_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hcsr04_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hcsr04
  "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hcsr04
)

### Generating Services

### Generating Module File
_generate_module_lisp(hcsr04
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hcsr04
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hcsr04_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hcsr04_generate_messages hcsr04_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_dependencies(hcsr04_generate_messages_lisp _hcsr04_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hcsr04_genlisp)
add_dependencies(hcsr04_genlisp hcsr04_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hcsr04_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(hcsr04
  "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hcsr04
)

### Generating Services

### Generating Module File
_generate_module_nodejs(hcsr04
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hcsr04
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(hcsr04_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(hcsr04_generate_messages hcsr04_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_dependencies(hcsr04_generate_messages_nodejs _hcsr04_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hcsr04_gennodejs)
add_dependencies(hcsr04_gennodejs hcsr04_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hcsr04_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hcsr04
  "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hcsr04
)

### Generating Services

### Generating Module File
_generate_module_py(hcsr04
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hcsr04
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hcsr04_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hcsr04_generate_messages hcsr04_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/hcsr04/msg/distance.msg" NAME_WE)
add_dependencies(hcsr04_generate_messages_py _hcsr04_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hcsr04_genpy)
add_dependencies(hcsr04_genpy hcsr04_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hcsr04_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hcsr04)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hcsr04
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(hcsr04_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(hcsr04_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hcsr04_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hcsr04)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hcsr04
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(hcsr04_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(hcsr04_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(hcsr04_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hcsr04)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hcsr04
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(hcsr04_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(hcsr04_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hcsr04_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hcsr04)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hcsr04
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(hcsr04_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(hcsr04_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(hcsr04_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hcsr04)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hcsr04\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hcsr04
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(hcsr04_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(hcsr04_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hcsr04_generate_messages_py std_msgs_generate_messages_py)
endif()
