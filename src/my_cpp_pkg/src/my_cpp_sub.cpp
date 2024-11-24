#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberSubscriber : public rclcpp::Node 
{
public:
    NumberSubscriber() : Node("number_sub") 
    {
        subscription_ = this->create_subscription<example_interfaces::msg::Int64>("Number",10,std::bind(&NumberSubscriber::sub_callback,this,std::placeholders::_1));
    }

private:
    void sub_callback(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(),"Message Received");
        auto number = msg->data;
        RCLCPP_INFO(this->get_logger(), "Number: %ld",number);

    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberSubscriber>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
