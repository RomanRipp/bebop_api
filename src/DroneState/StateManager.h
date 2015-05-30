/*
 * State.h
 *
 *  Created on: May 7, 2015
 *      Author: romanripp
 */

#ifndef STATE_H_
#define STATE_H_

#include "IState.h"

namespace Roman{
namespace BebopDroneApi{

class StateManager
{
public:
	StateManager();
	virtual ~StateManager();

	virtual void SetNormal(const std::string& msg);
	virtual void SetCritical(const std::string& msg);
	virtual void SetFatal(const std::string& msg);

private:
	std::shared_ptr<IState> _currentState;
};

} /* namespace BebopDroneApi */
} /* namespace Roman */

#endif /* STATE_H_ */
