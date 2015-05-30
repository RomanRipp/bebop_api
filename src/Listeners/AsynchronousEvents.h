/*
 * AsynchronousEvents.h
 *
 *  Created on: May 6, 2015
 *      Author: romanripp
 */

#pragma once

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "IBebopInterface.h"

namespace Roman{
namespace BebopDroneApi{

using namespace rebop;

class AsynchronousEventsListener
{
public:
	AsynchronousEventsListener(const std::weak_ptr<IBebopInterface>& bebop
			, const ros::NodeHandle& handle);
	virtual ~AsynchronousEventsListener();

	virtual void OnEmergency(const std_msgs::Bool &data);
	virtual void OnTakeoff(const std_msgs::Bool &data);

private:
	std::weak_ptr<IBebopInterface> _bebop;
	ros::NodeHandle _handle;
	ros::Subscriber _emergency;
	ros::Subscriber _takeOff;
	bool _isInTheAir;
};

} /* namespace BebopDroneApi */
} /* namespace Roman */
