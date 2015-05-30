cmake_minimum_required(VERSION 2.8.3)
project(bebop_api)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bebop_api
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

## Specify additional locations of header files
## Your package locations should be listed before other locations
#Bind with BebopRebopAPI project
set(workspace_DIR /Users/romanripp/documents/eclipse/Cworkspace)
set(rosWorkspace_DIR ${workspace_DIR}/rosWorkspace)
set(bebopApi_DIR ${workspace_DIR}/BebopRebopAPI)
set(bebopApi_DEPS_DIR ${bebopApi_DIR}/ThirdPartyLibs)
set(ardrone_SDK_DIR ${bebopApi_DEPS_DIR}/ArDroneSDK3/lib)
set(bebopApiNode_DIR ${rosWorkspace_DIR}/src/${PROJECT_NAME})

include_directories(${rosWorkspace_DIR}/src)
include_directories(${bebopApi_DIR}/source)
include_directories(${bebopApi_DEPS_DIR}/ArDroneSDK3/include)
include_directories(${bebopApi_DEPS_DIR}/easyloggingpp/include)
include_directories(${bebopApi_DEPS_DIR}/rapidjson/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(bebop_api
#   src/${PROJECT_NAME}/bebop_api.cpp
# )

## Declare a cpp executable
file(GLOB_RECURSE bebopApi_SRC
    ${bebopApi_DIR}/source/*.h
    ${bebopApi_DIR}/source/*.cpp
)

file(GLOB_RECURSE bebopApiNode_SRC
    src/*.h
    src/*.cpp
)

#add_executable(bebop_api ${bebopApiNode_SRC} ${bebopApi_SRC})
add_library(bebop_api ${bebopApiNode_SRC} ${bebopApi_SRC})

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(bebop_api_node bebop_api_generate_messages_cpp)

## Specify libraries to link a library or executable target against
file(GLOB bebopApi_LIBS ${ardrone_SDK_DIR}/*.dylib)

target_link_libraries(bebop_api
   ${catkin_LIBRARIES}
   ${bebopApi_LIBS}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS bebop_api bebop_api_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
find_package(gtest REQUIRED)
#find_package(gmock REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/Headers)


file(GLOB_RECURSE bebop_api_test_SRC_DIR
    "${bebopApiNode_DIR}/Test/*.cpp"
)

message("node dir")
message("${bebopApiNode_DIR}")

message("node src")
message("${bebop_api_test_SRC_DIR}")

file(GLOB_RECURSE bebop_api_test_LIBS_DIR
    ${GTEST_LIBRARIES}/*.a
)

catkin_add_gtest(${PROJECT_NAME}_test ${bebop_api_test_SRC_DIR})
target_link_libraries(${PROJECT_NAME}_test ${bebop_api_test_LIBS_DIR})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

##############
## Cleaning ##
##############

unset(workspace_DIR)
unset(bebopApi_DIR)
unset(bebopApi_DEPS_DIR)
unset(ardrone_SDK_DIR)
unset(bebopApi_LIBS)
unset(bebopApi_SRC)
unset(bebopApiNode_SRC)
unset(rosWorkspace_DIR)
