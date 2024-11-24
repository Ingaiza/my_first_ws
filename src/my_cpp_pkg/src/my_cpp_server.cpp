#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoIntServer : public rclcpp::Node 
{
public:
    AddTwoIntServer() : Node("int_server") 
    {
        server_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_server",
        std::bind(&AddTwoIntServer::server_callback,this,std::placeholders::_1,std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(),"Server is Active");
    }

private:
    void server_callback(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
                         const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)//request received , response sent
    {
        // request has two values a and b . a+b then return the sum as a response
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(),"%ld + %ld = %ld", request->a , request->b,response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntServer>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
