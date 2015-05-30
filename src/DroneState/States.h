/*
 * States.h
 *
 *  Created on: May 7, 2015
 *      Author: romanripp
 */

#pragma once

#include "IState.h"

namespace Roman{
namespace BebopDroneApi{

class Base : public virtual IState
{
public:
	virtual std::string GetStatusMessage() const;
	virtual DroneState GetType() const;

protected:
	Base(DroneState type);
	virtual ~Base();

	std::string _status;
	DroneState _type;
};

class Normal : public Base
{
public:
	Normal();
	virtual ~Normal();
};

class Critical : public Base
{
public:
	Critical();
	virtual ~Critical();
};

class Fatal : public Base
{
public:
	Fatal();
	virtual ~Fatal();
};

} /* namespace BebopDroneApi */
} /* namespace Roman */
