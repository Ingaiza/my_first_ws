#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


class AddTwoIntsClient : public rclcpp::Node 
{
public:
    AddTwoIntsClient() : Node("int_client") 
    {
        // addclientservice(2 , 3);
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClient::addclientservice,this,2,3)));
        // threads_.push_back(std::thread(std::bind(&AddTwoIntsClient::addclientservice,this,4,5)));
     
    }

    void addclientservice(int a , int b)//wait for server to be active : send request to server (a & b):then wait for response: then fetch result
    {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_server");
        while(!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(),"Waiting for server ...");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;
        
        auto result = client->async_send_request(request);
        try
        {
            auto response = result.get();
           RCLCPP_INFO(this->get_logger(),"%d + %d = %ld",a,b, response->sum);
        }
        catch(const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(),"Service Failed");
        }

    }

private:
    std::vector<std::thread> threads_;

 };

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClient>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
