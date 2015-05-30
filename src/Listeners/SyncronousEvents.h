/*
 * SyncronousEvents.h
 *
 *  Created on: May 6, 2015
 *      Author: romanripp
 */

#pragma once

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "IBebopInterface.h"


namespace Roman{
namespace BebopDroneApi{

using namespace rebop;

class SyncronousEventsListener
{
public:
	SyncronousEventsListener(const std::weak_ptr<IBebopInterface>& bebop
			, const ros::NodeHandle& handle);
	virtual ~SyncronousEventsListener();

	virtual void OnRpygControls(const nav_msgs::Odometry& msg) const;

private:
	virtual int8_t _toInt(double val) const;

private:
	std::weak_ptr<IBebopInterface> _bebop;
	ros::NodeHandle _handle;
	ros::Subscriber _rpyg;
};

} /* namespace BebopDroneApi */
} /* namespace Roman */
