# Arduino Toggle Build-In led with ROS
## Arduino IDE Installation
1. Download Arduino IDE for Ubuntu
    - [AMD64/EM64T](https://downloads.arduino.cc/arduino-1.8.19-linux64.tar.xz)
    - [AARCH64](https://downloads.arduino.cc/arduino-1.8.19-linuxaarch64.tar.xz)
2. Extract Arduino IDE **.tar.xz** file
    - AMD64/EM64T
    ```
    cd ~/.
    tar xvf ~/Downloads/arduino-1.8.19-linux64.tar.xz
    ```
    - AARCH64
    ```
    cd ~/.
    tar xvf ~/Downloads/arduino-1.8.19-linuxaarch64.tar.xz
    ```
3. Install Arduino IDE
    ```
    cd ~/arduino-1.8.19
    sudo ./install.sh
    ```
4. First open Arduino IDE
    ```
    arduino
    ```
## ROS Library for Arduino
Using ROS Package for rosserial communication between microcontroller and High Level
1. Installing [rosserial_package](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup#Installing_from_Source_onto_the_ROS_workstation)
    ```
    cd ~/catkin_ws/src
    git clone https://github.com/ros-drivers/rosserial.git
    cd ~/catkin_ws
    catkin_make
    source devel/setup.bash
    ```
2. Installing [rosserial_library](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup#Install_ros_lib_into_the_Arduino_Environment)
    ```
    cd ~/Arduino/libraries
    rosrun rosserial_arduino make_libraries.py .
    ```
3. Installing pyserial
    ```
    sudo apt install python-is-python3
    sudo apt install python3-serial
    ```
## Arduino Code Tutorial
- Open permission for arduino
    ```
    sudo chmod +x /dev/ttyACM0
    ```
- Example code for toggle arduino led build-in
    ```
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
    ```
## ROS rosserial testing
- Terminal 1 run roscore
    ```
    roscore
    ```
- Terminal 2 run rosserial communication
    ```
    rosrun rosserial_python serial_node.py /dev/ttyACM0
    ```
- Terminal 3 pub topic data
    ```
    rostopic pub /toggle_led std_msgs/Empty --once
    ```