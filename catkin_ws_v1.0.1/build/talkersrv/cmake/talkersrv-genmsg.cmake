# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "talkersrv: 1 messages, 0 services")

set(MSG_I_FLAGS "-Italkersrv:/home/orangepi/catkin_ws/src/talkersrv/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Imavros_msgs:/opt/ros/noetic/share/mavros_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeographic_msgs:/opt/ros/noetic/share/geographic_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Iuuid_msgs:/opt/ros/noetic/share/uuid_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(talkersrv_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_custom_target(_talkersrv_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "talkersrv" "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" "std_msgs/Header:geometry_msgs/Point:geometry_msgs/Vector3:mavros_msgs/PositionTarget"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(talkersrv
  "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/mavros_msgs/cmake/../msg/PositionTarget.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/talkersrv
)

### Generating Services

### Generating Module File
_generate_module_cpp(talkersrv
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/talkersrv
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(talkersrv_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(talkersrv_generate_messages talkersrv_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_dependencies(talkersrv_generate_messages_cpp _talkersrv_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(talkersrv_gencpp)
add_dependencies(talkersrv_gencpp talkersrv_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS talkersrv_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(talkersrv
  "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/mavros_msgs/cmake/../msg/PositionTarget.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/talkersrv
)

### Generating Services

### Generating Module File
_generate_module_eus(talkersrv
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/talkersrv
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(talkersrv_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(talkersrv_generate_messages talkersrv_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_dependencies(talkersrv_generate_messages_eus _talkersrv_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(talkersrv_geneus)
add_dependencies(talkersrv_geneus talkersrv_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS talkersrv_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(talkersrv
  "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/mavros_msgs/cmake/../msg/PositionTarget.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/talkersrv
)

### Generating Services

### Generating Module File
_generate_module_lisp(talkersrv
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/talkersrv
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(talkersrv_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(talkersrv_generate_messages talkersrv_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_dependencies(talkersrv_generate_messages_lisp _talkersrv_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(talkersrv_genlisp)
add_dependencies(talkersrv_genlisp talkersrv_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS talkersrv_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(talkersrv
  "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/mavros_msgs/cmake/../msg/PositionTarget.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/talkersrv
)

### Generating Services

### Generating Module File
_generate_module_nodejs(talkersrv
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/talkersrv
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(talkersrv_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(talkersrv_generate_messages talkersrv_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_dependencies(talkersrv_generate_messages_nodejs _talkersrv_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(talkersrv_gennodejs)
add_dependencies(talkersrv_gennodejs talkersrv_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS talkersrv_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(talkersrv
  "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/mavros_msgs/cmake/../msg/PositionTarget.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/talkersrv
)

### Generating Services

### Generating Module File
_generate_module_py(talkersrv
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/talkersrv
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(talkersrv_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(talkersrv_generate_messages talkersrv_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/orangepi/catkin_ws/src/talkersrv/msg/contrl.msg" NAME_WE)
add_dependencies(talkersrv_generate_messages_py _talkersrv_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(talkersrv_genpy)
add_dependencies(talkersrv_genpy talkersrv_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS talkersrv_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/talkersrv)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/talkersrv
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(talkersrv_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET mavros_msgs_generate_messages_cpp)
  add_dependencies(talkersrv_generate_messages_cpp mavros_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(talkersrv_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/talkersrv)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/talkersrv
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(talkersrv_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET mavros_msgs_generate_messages_eus)
  add_dependencies(talkersrv_generate_messages_eus mavros_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(talkersrv_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/talkersrv)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/talkersrv
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(talkersrv_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET mavros_msgs_generate_messages_lisp)
  add_dependencies(talkersrv_generate_messages_lisp mavros_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(talkersrv_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/talkersrv)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/talkersrv
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(talkersrv_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET mavros_msgs_generate_messages_nodejs)
  add_dependencies(talkersrv_generate_messages_nodejs mavros_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(talkersrv_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/talkersrv)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/talkersrv\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/talkersrv
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(talkersrv_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET mavros_msgs_generate_messages_py)
  add_dependencies(talkersrv_generate_messages_py mavros_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(talkersrv_generate_messages_py std_msgs_generate_messages_py)
endif()
