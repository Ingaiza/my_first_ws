from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    number_publisher_node = Node(

        package="my_cpp_pkg",
        executable="number_publisher",
        name="number_pub"
    )
    number_subscriber_node = Node(

        package="my_cpp_pkg",
        executable="number_subscriber",
        name="number_sub"
    )

    ld.add_action(number_publisher_node)
    ld.add_action(number_subscriber_node)

    return ld