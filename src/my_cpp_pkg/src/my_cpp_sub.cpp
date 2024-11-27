#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "my_first_interfaces/msg/weather_drone.hpp"

class NumberSubscriber : public rclcpp::Node 
{
public:
    NumberSubscriber() : Node("number_sub") 
    {
        subscription_ = this->create_subscription<example_interfaces::msg::Int64>("Number",10,std::bind(&NumberSubscriber::sub_callback,this,std::placeholders::_1));
        drone_subscription_ = this->create_subscription<my_first_interfaces::msg::WeatherDrone>("Weather", 5, std::bind(&NumberSubscriber::drone_sub_callback,this,std::placeholders::_1));
    }

private:
    void sub_callback(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),"Message Received");
        auto number = msg->data;
        RCLCPP_INFO(this->get_logger(), "Number: %ld",number);

    }

    void drone_sub_callback(const my_first_interfaces::msg::WeatherDrone::SharedPtr msg)
    {
        if(msg->motor_status)
        {
            RCLCPP_WARN(this->get_logger(),"Motor is Running");
            auto temperature = msg->temperature;
            auto humidity = msg->humidity;
            RCLCPP_INFO(this->get_logger(),"Temperature: %ld Humidity: %ld", temperature, humidity);
            RCLCPP_WARN(this->get_logger(),msg->debug_message.c_str());
            
        }
        else
        {
            RCLCPP_WARN(this->get_logger(),"Motor is not running");
            auto temperature = msg->temperature;
            auto humidity = msg->humidity;
            RCLCPP_INFO(this->get_logger(),"Temperature: %ld Humidity: %ld", temperature, humidity);
            RCLCPP_WARN(this->get_logger(),msg->debug_message.c_str());
        }

    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscription_;
    rclcpp::Subscription<my_first_interfaces::msg::WeatherDrone>::SharedPtr drone_subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberSubscriber>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
