
#include <gtest.h>
#include <gmock/gmock.h>
#include "Kernel/BebopKernel.h"
#include "ros/ros.h"
#include "Mock/CBebopInterface.h"
#include "Utility/SharedConstants.h"
#include "Utility/Exceptions.h"

using namespace Roman::BebopDroneApi;
using namespace testing;

TEST(BebopKernelTest, ConnectionTest)
{

	auto bebop = std::make_shared<CBebopInterfaceMock>();

	EXPECT_CALL(*bebop, Initialize());

	EXPECT_CALL(*bebop, IsConnected())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, FlatTrim())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, SetMaxAltitude(BebopParams::Controls::MAXALTITIDE))
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, StartVideo())
		.WillOnce(Return(true));

	BebopKernel kernel(bebop);
	kernel.xInit();

	ASSERT_TRUE(true);
}

TEST(BebopKernelTest, ReconnectionTest)
{

	auto bebop = std::make_shared<CBebopInterfaceMock>();

	EXPECT_CALL(*bebop, Initialize())
		.Times(3);

	EXPECT_CALL(*bebop, IsConnected())
		.Times(3)
		.WillOnce(Return(false))
		.WillOnce(Return(false))
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, FlatTrim())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, SetMaxAltitude(BebopParams::Controls::MAXALTITIDE))
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, StartVideo())
		.WillOnce(Return(true));

	BebopKernel kernel(bebop);
	kernel.xInit();

	ASSERT_TRUE(true);
}

TEST(BebopKernelTest, FlatTrimTest)
{

	auto bebop = std::make_shared<CBebopInterfaceMock>();

	EXPECT_CALL(*bebop, Initialize());

	EXPECT_CALL(*bebop, IsConnected())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, FlatTrim())
		.WillOnce(Return(false));

	EXPECT_CALL(*bebop, SetMaxAltitude(BebopParams::Controls::MAXALTITIDE))
		.Times(0);

	EXPECT_CALL(*bebop, StartVideo())
		.Times(0);

	BebopKernel kernel(bebop);
	ASSERT_THROW(kernel.xInit(), Exceptions::Critical);
}

TEST(BebopKernelTest, SetMaxAltitudeTest)
{

	auto bebop = std::make_shared<CBebopInterfaceMock>();

	EXPECT_CALL(*bebop, Initialize());

	EXPECT_CALL(*bebop, IsConnected())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, FlatTrim())
		.WillOnce(Return(true));

	EXPECT_CALL(*bebop, SetMaxAltitude(BebopParams::Controls::MAXALTITIDE))
		.WillOnce(Return(false));

	EXPECT_CALL(*bebop, StartVideo())
		.Times(0);

	BebopKernel kernel(bebop);
	ASSERT_THROW(kernel.xInit(), Exceptions::Critical);
}
