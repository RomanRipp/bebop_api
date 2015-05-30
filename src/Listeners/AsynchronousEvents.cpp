/*
 * AsynchronousEvents.cpp
 *
 *  Created on: May 6, 2015
 *      Author: romanripp
 */

#include "AsynchronousEvents.h"
#include "Utility/Exceptions.h"
#include "Utility/SharedConstants.h"

namespace Roman{
namespace BebopDroneApi{

AsynchronousEventsListener::AsynchronousEventsListener(const std::weak_ptr<IBebopInterface>& bebop
		, const ros::NodeHandle& handle) : _bebop(bebop)
			, _handle(handle)
			, _emergency(_handle.subscribe(Topics::Controls::EMERGENCY, 50, &AsynchronousEventsListener::OnEmergency, this))
			, _takeOff(_handle.subscribe(Topics::Controls::TAKEOFF, 50, &AsynchronousEventsListener::OnTakeoff, this))
			, _isInTheAir(false)
{
	ROS_INFO("Asynchronous listener started");
}

AsynchronousEventsListener::~AsynchronousEventsListener()
{
	// TODO Auto-generated destructor stub
}

void AsynchronousEventsListener::OnEmergency(const std_msgs::Bool &data)
{
	const auto& bebopLocked(_bebop.lock());
	if (!bebopLocked)
		throw Exceptions::Critical("Bebop expired");

	if (!bebopLocked->Emergency())
		throw Exceptions::Fatal("Things are really bad... pray...");

	ROS_WARN("Emergency mode initiated");
}
void AsynchronousEventsListener::OnTakeoff(const std_msgs::Bool &data)
{
	ROS_INFO("Take off bitch");

	const auto& bebopLocked(_bebop.lock());
	if (!bebopLocked)
	{
		ROS_ERROR("Bebop expired");
		return;
	}

	if (!_isInTheAir)
	{
		if (!bebopLocked->Takeoff())
		{
			ROS_ERROR("Bebop failed to take off");
			return;
		}

		ROS_INFO("Taking off");
		_isInTheAir = true;
	}
	else
	{
		if (!bebopLocked->Land())
		{
			ROS_ERROR("Bebop failed to take off");
			return;
		}

		ROS_INFO("Landing");
		_isInTheAir = false;
	}
}

} /* namespace BebopDroneApi */
} /* namespace Roman */
