#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "my_first_interfaces/msg/weather_drone.hpp"

class NumberPublisherNode : public rclcpp::Node 
{
public:
    NumberPublisherNode() : Node("number_pub") 
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("Number", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),std::bind(&NumberPublisherNode::timer_callback,this));
        drone_publisher_ = this->create_publisher<my_first_interfaces::msg::WeatherDrone>("Weather",10);
        drone_timer_ = this->create_wall_timer(std::chrono::seconds(2),std::bind(&NumberPublisherNode::drone_timer_callback,this));
    }   

private:

    void timer_callback()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = 10;
        publisher_->publish(msg);

    }
    void drone_timer_callback()
    {
        auto msg = my_first_interfaces::msg::WeatherDrone();
        msg.temperature = 67;
        msg.humidity = 30;
        msg.motor_status = true; //motors are running
        msg.debug_message = "Collecting data";
        drone_publisher_->publish(msg);


    }
  
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Publisher<my_first_interfaces::msg::WeatherDrone>::SharedPtr drone_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr drone_timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
