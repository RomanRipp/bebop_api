/*
 * VideoPublisher.cpp
 *
 *  Created on: May 27, 2015
 *      Author: romanripp
 */

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "VideoPublisher.h"
#include "Utility/SharedConstants.h"
#include <algorithm>

namespace Roman
{
namespace BebopDroneApi
{

VideoPublisher::VideoPublisher(ros::NodeHandle& handle)
	: _video (handle.advertise<sensor_msgs::Image>(Topics::Video::FRAME, 50))
{

}

VideoPublisher::~VideoPublisher()
{

}

void VideoPublisher::xUpdate(const TFrame& frame)
{
	//FILE* videoFile = fopen("./video_fifo", "w");
	if (frame.IsValid())
	{
	  ROS_INFO("Frame is valid");
	  auto skipped = frame.GetNumberOfSkippedFrames();

	  sensor_msgs::Image imageMsg;
	  imageMsg.width = 800;
	  imageMsg.height = 600;
	  //imageMsg.encoding = "mjpeg";
	  imageMsg.encoding = "h264";
	  imageMsg.is_bigendian = false;
	  imageMsg.step = 800 * 3;
	  //imageMsg.data.resize(D1_STREAM_WIDTH * D1_STREAM_HEIGHT * 3);

	  auto data = frame.GetData();
	  for(auto i = 0; i < frame.GetFrameDataSize(); i++)
	  {
		  unsigned char temp = data[i];
		  imageMsg.data.push_back(temp);
	  }

	  _video.publish(imageMsg);
//	  std::fwrite(frame.GetData(), frame.GetFrameDataSize(), 1, videoFile);
//	  fflush(videoFile);
	}
}

} /* namespace BebopDroneApi */
} /* namespace Roman */
