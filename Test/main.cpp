/*
 * main.cpp
 *
 *  Created on: May 10, 2015
 *      Author: romanripp
 */

#include <gtest.h>
#include "ros/ros.h"

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	ros::init(argc, argv, "bebop_kernel");
	return RUN_ALL_TESTS();
}


