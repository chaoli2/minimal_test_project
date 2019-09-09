cmake_minimum_required(VERSION 3.5)
project(my_test)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils REQUIRED)
find_package(message_filters REQUIRED)

#include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)
ament_target_dependencies(${PROJECT_NAME}
  "std_msgs"
  "sensor_msgs"
  "rclcpp"
  "rcutils"
  "message_filters"
)

add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher
  "std_msgs"
  "sensor_msgs"
  "rclcpp"
  "message_filters"
)

#add_executable(publisher2 src/publisher2.cpp)
#ament_target_dependencies(publisher2
#  "std_msgs"
#  "sensor_msgs"
#  "rclcpp"
#)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
