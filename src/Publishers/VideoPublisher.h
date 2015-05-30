/*
 * VideoPublisher.h
 *
 *  Created on: May 27, 2015
 *      Author: romanripp
 */

#ifndef VIDEOPUBLISHER_H_
#define VIDEOPUBLISHER_H_

#include "BebopCommandsAndData.h"

using namespace rebop::commands::bebop::video;

namespace Roman {
namespace BebopDroneApi {

class VideoPublisher
{
public:
	VideoPublisher(ros::NodeHandle& handle);
	virtual ~VideoPublisher();

	virtual void xUpdate(const TFrame& frame);

private:
	ros::Publisher _video;
};

} /* namespace BebopDroneApi */
} /* namespace Roman */

#endif /* VIDEOPUBLISHER_H_ */
