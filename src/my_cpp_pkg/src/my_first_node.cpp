#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"


class NumberPublisherNode : public rclcpp::Node 
{
public:
    NumberPublisherNode() : Node("number_pub") 
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("Number", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1),std::bind(&NumberPublisherNode::timer_callback,this));

    }

private:

    void timer_callback()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = 10;
        publisher_->publish(msg);

    }

    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}