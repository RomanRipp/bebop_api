/*
 * BebopKernel.h
 *
 *  Created on: May 5, 2015
 *      Author: romanripp
 */
#pragma once

#include "IBebopInterface.h"
#include "ros/ros.h"
#include "Listeners/AsynchronousEvents.h"
#include "Listeners/SyncronousEvents.h"

#include "Publishers/VideoPublisher.h"

namespace Roman{
namespace BebopDroneApi{

class BebopKernel {
public:
  BebopKernel();
  BebopKernel(std::shared_ptr<rebop::IBebopInterface> bebopInterface);
  virtual ~BebopKernel();

  virtual void xInit();
  virtual void xLoop();
  virtual void Emergency();

private:
  std::shared_ptr<rebop::IBebopInterface> _bebopInterface;
  ros::NodeHandle _handle;
  AsynchronousEventsListener _asyncListener;
  SyncronousEventsListener _syncListener;

  VideoPublisher _videoPublisher;
};

}
}
