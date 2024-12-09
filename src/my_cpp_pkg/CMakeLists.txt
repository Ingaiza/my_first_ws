cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_first_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# executables
add_executable(number_publisher src/my_first_node.cpp)
ament_target_dependencies(number_publisher rclcpp example_interfaces my_first_interfaces)

add_executable(number_subscriber src/my_cpp_sub.cpp)
ament_target_dependencies(number_subscriber rclcpp example_interfaces my_first_interfaces)

add_executable(add_server src/my_cpp_server.cpp)
ament_target_dependencies(add_server rclcpp example_interfaces)

add_executable(add_client src/my_cpp_client.cpp)
ament_target_dependencies(add_client rclcpp example_interfaces)

# installing executables
install(TARGETS
        number_publisher
        number_subscriber
        add_server
        add_client
        DESTINATION lib/${PROJECT_NAME})

ament_package()
