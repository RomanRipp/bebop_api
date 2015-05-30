/*
 * State.cpp
 *
 *  Created on: May 7, 2015
 *      Author: romanripp
 */

#include "DroneState/States.h"
#include "DroneState/StateManager.h"
#include "ros/ros.h"
#include <memory.h>

namespace Roman{
namespace BebopDroneApi{

StateManager::StateManager() : _currentState(std::shared_ptr<Normal>())
{
	// TODO Auto-generated constructor stub

}

StateManager::~StateManager()
{
	// TODO Auto-generated destructor stub
}

void StateManager::SetNormal(const std::string& msg)
{
	ROS_INFO("BEBOP IS OK");
	_currentState = std::make_shared<Normal>();
}

void StateManager::SetCritical(const std::string& msg)
{
	_currentState = std::make_shared<Critical>();
}

void StateManager::SetFatal(const std::string& msg)
{
	_currentState = std::make_shared<Fatal>();
}

} /* namespace BebopDroneApi */
} /* namespace Roman */
