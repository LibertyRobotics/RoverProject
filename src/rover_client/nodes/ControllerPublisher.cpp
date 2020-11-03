#include "ros/ros.h"

#include "rover_client/ControlService.h"
#include "rover_main/controllerMap.h"
#include <string>

int main(int argc, char **argv){
    ros::init(argc, argv, "controller_info_publisher");


    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<rover_client::ControlService>("controller_service");

    rover_client::ControlService srv;

    ros::Publisher controller_publisher = n.advertise<rover_main::controllerMap>("rover_control_stream", 1);
    ros::Rate loop_rate(250);

    while (ros::ok()){
        if(client.call(srv)){
            ROS_INFO("Publishing Data...");
            controller_publisher.publish(srv.response.controllerState);
        }
        else{
            ROS_INFO("Failed to call ControllerService");
            return 1;
        }
        loop_rate.sleep();
    }
   
    return 0;
}