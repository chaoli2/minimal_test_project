#include <rclcpp/rclcpp.hpp>
#include <rclcpp/clock.hpp>
#include <rclcpp/time.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/int32.hpp>

#include <iostream>
#include <memory>
#include <unistd.h>



class subscriber : public rclcpp::Node
{
public:
  subscriber() : Node("subscriber") { };

  void callback(std_msgs::msg::Header msg)
  {
    auto node = rclcpp::Node::make_shared("publisher1");

    rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr pub_;
    pub_ = node->create_publisher<std_msgs::msg::Header>("/publish2", 16);

    std_msgs::msg::Header msg2;
    while (rclcpp::ok())
    {
      std::cout << "publishing" << std::endl;
      rclcpp::Time time= node->now();
      msg2.stamp = msg.stamp;
      pub_->publish(msg2);
      rclcpp::spin_some(node);
      sleep(1);
    }
  }

//private:

};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher1");

  rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr sub_;
  sub_ = node->create_subscription<std_msgs::msg::Header>("/publisher1", 100, subscriber::callback);

  //rclcpp::spin(node);
  //rclcpp::shutdown();
}
