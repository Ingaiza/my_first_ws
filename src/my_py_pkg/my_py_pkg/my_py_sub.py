#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import  Int64



class NumberSub(Node): 
    def __init__(self):
        super().__init__("numberpy_sub") 
        self.subscriber = self.create_subscription(Int64, "Number",self.sub_callback,1)

    def sub_callback(self,msg):
        self.get_logger().warn(str(msg.data))

        
def main(args=None):
    rclpy.init(args=args)
    node = NumberSub() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
