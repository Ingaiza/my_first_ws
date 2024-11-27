from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    number_publisher_node = Node(

        package="my_cpp_pkg",
        executable="number_publisher",
        name="number_pub",
        parameters=[
            {"temperature": 17}],
        remappings=[
            ("Number","Interger"),
            ("Weather","Forecast")
        ] 
                        
    )
    number_subscriber_node = Node(

        package="my_cpp_pkg",
        executable="number_subscriber",
        name="number_sub"
    )
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
    py_subscriber = Node(
        
        package="my_py_pkg",
        executable="py_subscriber",
        name="numberpy_sub"
    )

    ld.add_action(number_publisher_node)
    ld.add_action(number_subscriber_node)
    ld.add_action(server_node)
    ld.add_action(client_node)
    ld.add_action(py_subscriber)

    return ld