#include <rclcpp/rclcpp.hpp>
#include <rclcpp/time.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <std_msgs/msg/header.hpp>

#include <iostream>
#include <memory>
#include <unistd.h>

class Publisher1 : public rclcpp::Node
{
public:
  Publisher1() : Node("publisher") {};
};


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("publisher");

  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr pub1, pub2;
  pub1 = node->create_publisher<std_msgs::msg::Header>("/publish1", 16);
  pub2 = node->create_publisher<std_msgs::msg::Header>("/publish2", 16);

  std_msgs::msg::Header msg1, msg2;

  while (rclcpp::ok())
  {
    std::cout << "publishing" << std::endl;
    rclcpp::Time time= node->now();
    msg1.stamp = time;
    msg2.stamp = time;
    pub1->publish(msg1);
    pub2->publish(msg2);
    rclcpp::spin_some(node);
    sleep(1);
  }
}
