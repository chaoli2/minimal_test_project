#include <rclcpp/rclcpp.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <std_msgs/msg/header.hpp>

#include <iostream>
#include <memory>

class MessageFilterTest : public rclcpp::Node
{
public:
  MessageFilterTest() : Node("test") 
  {
    cam_sub_ = std::make_unique<camSub>(this, "/publish1");
    obj_sub_ = std::make_unique<objSub>(this, "/publish2");
    sync_sub_ = std::make_unique<sync>(*cam_sub_, *obj_sub_, 10);
    sync_sub_->registerCallback(std::bind(&MessageFilterTest::callback, this, std::placeholders::_1, std::placeholders::_2));
  };

private:
  using camSub = message_filters::Subscriber<std_msgs::msg::Header>;
  using objSub = message_filters::Subscriber<std_msgs::msg::Header>;

  using sync =
     message_filters::TimeSynchronizer<std_msgs::msg::Header, std_msgs::msg::Header>;
 
  std::unique_ptr<camSub> cam_sub_;
  std::unique_ptr<objSub> obj_sub_;
  std::unique_ptr<sync> sync_sub_;

  void callback(const std_msgs::msg::Header::ConstSharedPtr msg1, const std_msgs::msg::Header::ConstSharedPtr msg2)
  {
    std::cout << "callback" << std::endl;
  };
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  //rclcpp::executors::SingleThreadedExecutor exec;
  auto message_filter_test_node = std::make_shared<MessageFilterTest>();

  rclcpp::spin(message_filter_test_node);
  rclcpp::shutdown();

  return 0;
}
