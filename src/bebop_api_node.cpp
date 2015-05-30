/*
 * main.cpp
 *
 *  Created on: May 3, 2015
 *      Author: romanripp
 */

#include "ros/ros.h"
#include "Utility/Exceptions.h"
#include "Kernel/BebopKernel.h"

using namespace rebop::commands::bebop::navigation;
using namespace Roman::BebopDroneApi;

int main(int argc, char **argv)
{
	ROS_INFO("Bebop drone ROS API launched");
	ROS_INFO("Initializing bebop kernel");

	ros::init(argc, argv, "bebop_kernel");
	ros::spin();

	BebopKernel kernel;
	try
	{
	    kernel.xInit();
	    kernel.xLoop();
	}
	catch(Exceptions::Base& e)
	{
	    ROS_ERROR("Kernel exception: %s", e.what().c_str());
	    kernel.Emergency();
	}

	return 0;
}


