/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/mygui/qnode.hpp"
#include "robot_manager_msgs/GetMode.h"
#include "robot_manager_msgs/SetMode.h"
#include "robot_manager_msgs/GetMap.h"
#include "robot_manager_msgs/SetNavGoal.h"
#include "robot_manager_msgs/SetInitPose.h"
#include "robot_manager_msgs/UpdateMap.h"
#include "robot_manager_msgs/UpdateMapFromServer.h"
#include "robot_manager_msgs/MapRefPoseStamped.h"
#include "robot_manager_msgs/ModeRegister.h"
#include "robot_manager_msgs/ModeDeregister.h"
#include "robot_manager_msgs/SaveMap.h"
#include "robot_manager_msgs/ChangeMap.h"
#include "robot_manager_msgs/GetAllMapName.h"
#include "robot_manager_msgs/GetCurrentMapName.h"
#include "robot_manager_msgs/GetVelocity.h"
#include "robot_manager_msgs/SetVelocity.h"
/**************************************************
***************************
** Namespaces
*****************************************************************************/

namespace mygui {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"mygui");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"mygui");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}

void QNode::run() {
	ros::Rate loop_rate(1);
    count = 0;
	while ( ros::ok() ) {

		std_msgs::String msg;
		std::stringstream ss;
		ss << "hello world " << count;
		msg.data = ss.str();
		chatter_publisher.publish(msg);
        //log(Info,std::string("I sent: ")+msg.data);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

void QNode::setModeDo()
  {
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_manager_msgs::SetMode>("/robot_manager/SetMode");
    robot_manager_msgs::SetMode  srv;
    srv.request.expectedMode =2;
    if(client.call(srv))
         {
             count  =srv.response.currentMode;
         }
     else{
             count  = 100;
         }
   }

void QNode::getModeDo()
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_manager_msgs::GetMode>("/robot_manager/GetMode");
    robot_manager_msgs::GetMode  srv;
     if(client.call(srv))
     {
         //count  =srv.response.currentMode;
          if( srv.response.currentMode ==1)
          {
              log(Info,std::string(" nav "));
          }
          else if(srv.response.currentMode ==2)
          {
              log(Info,std::string(" scan map "));
          }
     }
     else{
         log(Info,std::string("Get mode  error "));
     }
}
void QNode::GetAllMapDo()
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_manager_msgs::GetAllMapName>("/robot_manager/GetAllMapName");
    robot_manager_msgs::GetAllMapName  srv;

    if(client.call(srv))
     {
        // count  =srv.response.mapNums;
         ROS_INFO("mapNums: %d",srv.response.mapNums );
         std::string str="";
         for(int i =0; i<srv.response.mapNums ; i++)
         {
             str = str+srv.response.map[i]+" \n";
         }
         log(Info,std::string("all map: ")+str);
     }
     else{
            log(Info,std::string("get all map error "));
     }
}

void QNode::GetCurrentMapDo()
{

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_manager_msgs::GetCurrentMapName>("/robot_manager/GetCurrentMapName");
    robot_manager_msgs::GetCurrentMapName  srv;
    if(client.call(srv))
     {
         std::string str="";

             str = str+srv.response.map+" \n";

         log(Info,std::string("GetCurrentMapName : ")+str);
     }
     else{
            log(Info,std::string("get  Current map error "));
     }
}
void QNode::ChangeMapDo(std::string str)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<robot_manager_msgs::ChangeMap>("/robot_manager/ChangeMap");
    robot_manager_msgs::ChangeMap  srv;
    srv.request.mapName =str;
    if(client.call(srv))
         {
            int  count1  =srv.response.result;
             switch (count1) {
             case 1:
                  log(Info,std::string(" change map SUCCESS "));
                 break;
             case 2:
                  log(Info,std::string(" change map FAILED "));
                 break;
             case 3:
                  log(Info,std::string("  map not found "));
                 break;
             default:
                 break;
             }

         }
     else{
            log(Info,std::string("  change map error "));
         }



}
}  // namespace mygui
