#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import  Int64
from my_first_interfaces.msg import WeatherDrone



class NumberSub(Node): 
    def __init__(self):
        super().__init__("numberpy_sub") 
        self.subscriber = self.create_subscription(Int64, "Number",self.sub_callback,1)
        self.drone_subscriber = self.create_subscription(WeatherDrone, "Weather",self.drone_callback,1)

    def sub_callback(self,msg):
        self.get_logger().warn(str(msg.data))

    def drone_callback(self,msg):
        if(msg.motor_status):
            self.get_logger().warn("Motor is Running")
            self.get_logger().info("Temperature: " + str(msg.temperature) + " Humidity: " + str(msg.humidity))
            self.get_logger().error(str(msg.debug_message))
        else:
            self.get_logger().warn("Motor is not running")
            self.get_logger().info("Temperature: " + str(msg.temperature) + " Humidity: " + str(msg.humidity))
            self.get_logger().error(str(msg.debug_message))
        
        
def main(args=None):
    rclpy.init(args=args)
    node = NumberSub() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
