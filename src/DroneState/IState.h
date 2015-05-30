/*
 * IState.h
 *
 *  Created on: May 7, 2015
 *      Author: romanripp
 */

# pragma once

#include <string>

namespace Roman{
namespace BebopDroneApi{

enum DroneState
{
	NORMAL,
	CRITICAL,
	FATAL
};

class IState
{
	//virtual std::string GetStatusMessage() const = 0;
};

}
}


