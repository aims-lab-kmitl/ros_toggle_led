#include <ros.h>
#include <std_msgs/Empty.h>

// Function for subscriber
void toggle_led(const std_msgs::Empty &toggle_msg){
    digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
}

// init ros node
ros::NodeHandle nh;

// init ros scriber topic
ros::Subscriber<std_msgs::Empty> toggle_sub("/toggle_led", &toggle_led);

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);

    // init ros
    nh.initNode();
    nh.subscribe(toggle_sub);
}

void loop(){
    nh.spinOnce();
    delay(30);
}