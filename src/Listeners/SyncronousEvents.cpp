/*
 * SyncronousEvents.cpp
 *
 *  Created on: May 6, 2015
 *      Author: romanripp
 */

#include "SyncronousEvents.h"
#include "Utility/Exceptions.h"
#include "Utility/SharedConstants.h"
#include "BebopCommandsAndData.h"
#include <math.h>

namespace Roman{
namespace BebopDroneApi{

SyncronousEventsListener::SyncronousEventsListener(const std::weak_ptr<IBebopInterface>& bebop
		, const ros::NodeHandle& handle) : _bebop(bebop)
			, _handle(handle)
			, _rpyg(_handle.subscribe(Topics::Controls::RPYG, 50, &SyncronousEventsListener::OnRpygControls, this))
{
	// TODO Auto-generated constructor stub

}

SyncronousEventsListener::~SyncronousEventsListener()
{
	// TODO Auto-generated destructor stub
}

void SyncronousEventsListener::OnRpygControls(const nav_msgs::Odometry& msg) const
{
	const auto& bebopLocked(_bebop.lock());
	if (!bebopLocked)
	{
		ROS_FATAL("Bebop expired");
		return;
	}

	commands::bebop::navigation::TPilotCommand command
	{
		1,
		_toInt(msg.twist.twist.linear.x),
		_toInt(msg.twist.twist.linear.y),
		_toInt(msg.twist.twist.linear.z),
		_toInt(msg.pose.pose.position.z),
		0
	};

	if (!bebopLocked->SendPilotCommand(command))
	{
		ROS_ERROR("Failed to send commend");
	}
}

int8_t SyncronousEventsListener::_toInt(double val) const
{
	double intpart = 0.0;
	modf(val , &intpart);
	return ((int8_t)intpart);
}

} /* namespace BebopDroneApi */
} /* namespace Roman */
