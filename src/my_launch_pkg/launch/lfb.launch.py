from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    server_node = Node(

        package="my_cpp_pkg",
        executable="add_server",
        name="int_server"
    )
    client_node = Node(

        package="my_cpp_pkg",
        executable="add_client",
        name="int_client"
    )

    ld.add_action(server_node)
    ld.add_action(client_node)

    return ld