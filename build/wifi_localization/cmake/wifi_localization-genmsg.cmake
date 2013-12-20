# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "wifi_localization: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iwifi_localization:/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg;-Istd_msgs:/opt/ros/hydro/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(wifi_localization_generate_messages ALL)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/WifiData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wifi_localization
)
_generate_msg_cpp(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wifi_localization
)

### Generating Services

### Generating Module File
_generate_module_cpp(wifi_localization
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wifi_localization
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(wifi_localization_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(wifi_localization_generate_messages wifi_localization_generate_messages_cpp)

# target for backward compatibility
add_custom_target(wifi_localization_gencpp)
add_dependencies(wifi_localization_gencpp wifi_localization_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wifi_localization_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/WifiData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wifi_localization
)
_generate_msg_lisp(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wifi_localization
)

### Generating Services

### Generating Module File
_generate_module_lisp(wifi_localization
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wifi_localization
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(wifi_localization_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(wifi_localization_generate_messages wifi_localization_generate_messages_lisp)

# target for backward compatibility
add_custom_target(wifi_localization_genlisp)
add_dependencies(wifi_localization_genlisp wifi_localization_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wifi_localization_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/WifiData.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/hydro/share/std_msgs/cmake/../msg/Header.msg;/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization
)
_generate_msg_py(wifi_localization
  "/home/tim/Dropbox/Workspaces/tim-ros-pkgs/src/wifi_localization/msg/AccessPoint.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization
)

### Generating Services

### Generating Module File
_generate_module_py(wifi_localization
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(wifi_localization_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(wifi_localization_generate_messages wifi_localization_generate_messages_py)

# target for backward compatibility
add_custom_target(wifi_localization_genpy)
add_dependencies(wifi_localization_genpy wifi_localization_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS wifi_localization_generate_messages_py)


debug_message(2 "wifi_localization: Iflags=${MSG_I_FLAGS}")


if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wifi_localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/wifi_localization
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(wifi_localization_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wifi_localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/wifi_localization
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(wifi_localization_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/wifi_localization
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(wifi_localization_generate_messages_py std_msgs_generate_messages_py)
