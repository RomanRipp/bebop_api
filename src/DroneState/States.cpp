/*
 * States.cpp
 *
 *  Created on: May 7, 2015
 *      Author: romanripp
 */

#include "States.h"

namespace Roman
{
namespace BebopDroneApi
{

Base::Base(DroneState type) : _type(type)
{
	// TODO Auto-generated constructor stub
}

Base::~Base()
{
	// TODO Auto-generated destructor stub
}

std::string Base::GetStatusMessage() const
{
	return _status;
}

DroneState Base::GetType() const
{
	return _type;
}

Normal::Normal() : Base(NORMAL)
{
	// TODO Auto-generated constructor stub

}

Normal::~Normal()
{
	// TODO Auto-generated destructor stub
}

Critical::Critical() : Base(CRITICAL)
{
	// TODO Auto-generated constructor stub

}

Critical::~Critical()
{
	// TODO Auto-generated destructor stub
}

Fatal::Fatal() : Base(FATAL)
{
	// TODO Auto-generated constructor stub

}

Fatal::~Fatal()
{
	// TODO Auto-generated destructor stub
}


} /* namespace BebopDroneApi */
} /* namespace Roman */
