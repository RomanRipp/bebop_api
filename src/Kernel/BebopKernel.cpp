/*
 * BebopKernel.cpp
 *
 *  Created on: May 5, 2015
 *      Author: romanripp
 */

#include "Kernel/BebopKernel.h"
#include "Utility/Exceptions.h"
#include "Utility/SharedConstants.h"
#include "CBebopInterface.h"

namespace Roman{
namespace BebopDroneApi{

  BebopKernel::BebopKernel()
  	  : _handle()
  	  , _bebopInterface(std::shared_ptr<rebop::CBebopInterface>())
  	  , _asyncListener(_bebopInterface, _handle)
  	  , _syncListener(_bebopInterface, _handle)
  	  , _videoPublisher(_handle)
  {
	// TODO Auto-generated constructor stub
  }

  BebopKernel::BebopKernel(std::shared_ptr<rebop::IBebopInterface> bebopInterface)
	: _handle()
	, _bebopInterface(bebopInterface)
	, _asyncListener(_bebopInterface, _handle)
	, _syncListener(_bebopInterface, _handle)
  	, _videoPublisher(_handle)
  {

  }

  BebopKernel::~BebopKernel()
  {
	// TODO Auto-generated destructor stub
	if(_bebopInterface)
	{
		_bebopInterface->StopVideo();
		_bebopInterface->Cleanup();
	}

	ros::shutdown();
  }

  void BebopKernel::xInit()
  {
    ROS_INFO("Initializing bebop kernel");
    ROS_INFO("1. Initializing ROS...");

    if (!ros::isInitialized())
    {
    	throw Exceptions::Critical("Ros failed to initialize");
    }
    ros::Rate loop_rate(1);
    ROS_INFO("Success");

    ROS_INFO("2. Initializing bebop");
    if (!_bebopInterface)
    	throw Exceptions::Critical("Bebop interface is invalid");

    ROS_INFO("Connecting...");
    _bebopInterface->Initialize();
    while (!_bebopInterface->IsConnected())
    {
    	ROS_WARN("Retrying...");
    	loop_rate.sleep();
    	_bebopInterface->Initialize();
    }

    ROS_INFO("Flat trim");
    if (!_bebopInterface->FlatTrim())
    {
    	throw Exceptions::Critical("Failed flat trim");
    }
    loop_rate.sleep();

    ROS_INFO("Setting max altitude to %f m", BebopParams::Controls::MAXALTITIDE);
    if (!_bebopInterface->SetMaxAltitude(BebopParams::Controls::MAXALTITIDE))
    {
    	throw Exceptions::Critical("Failed to set max altitude");
    }
    loop_rate.sleep();

    ROS_INFO("Starting the video");
    if (!_bebopInterface->StartVideo())
    {
    	throw Exceptions::Critical("Failed to start a video feed");
    }
    loop_rate.sleep();

    ROS_INFO("Drone initialized");
  }

  void BebopKernel::xLoop()
  {
	  //in a thread
	  ros::Rate loop_rate(30); //30 Hz, pretty slow.

	  while(ros::ok())
	  {
		  ROS_INFO("Looping");
		  //Process video
		  _videoPublisher.xUpdate(_bebopInterface->GetVideoFrame());

		  ros::spinOnce();
		  loop_rate.sleep();
	  }
  }

  void BebopKernel::Emergency()
  {
    ROS_INFO("Emergency routine initialized");
    if (!_bebopInterface)
    {
    	ROS_FATAL("Drone xpired");
    }

	ros::Rate loop_rate(1);
	while (!_bebopInterface->IsConnected())
	{
		ROS_INFO("Recovering connection");
		_bebopInterface->Initialize();
		loop_rate.sleep();
	}
	ROS_INFO("Connection recovered!");
  }

}
}
