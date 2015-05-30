/*
 * CBebopInterfaceFail.h
 *
 *  Created on: May 10, 2015
 *      Author: romanripp
 */
#pragma once

#include <gmock/gmock.h>
#include "IBebopInterface.h"

using namespace rebop::commands::bebop::navigation;
using namespace rebop::commands::bebop::video;

namespace rebop
{
class CBebopInterfaceMock : public IBebopInterface
{
public:

	MOCK_METHOD0(Initialize, void());
	MOCK_METHOD0(Update, void());
	MOCK_METHOD0(Cleanup, void());
	MOCK_METHOD0(IsConnected, bool());

	MOCK_METHOD0(Takeoff, bool());
	MOCK_METHOD0(Land, bool());
	MOCK_METHOD0(Emergency, bool());
	MOCK_METHOD0(FlatTrim, bool());
	MOCK_METHOD1(NavigateHome, bool( ENavigateHome startOrStopIn ));
	MOCK_METHOD1(SendPilotCommand, bool( const TPilotCommand &poseIn ));
	MOCK_METHOD1(SetAutoTakeoffMode, bool( EAutoTakeoffMode modeIn ));
	MOCK_METHOD1(Flip, bool( EFlipDirection directionIn ));
	MOCK_METHOD1(SetMaxAltitude, bool( float maxAltitudeMetersIn ));
	MOCK_METHOD1(SetMaxTilt, bool( float maxTiltDegreesIn ));
	MOCK_METHOD1(SetMaxVerticalSpeed, bool( float maxVerticalSpeedMetersPerSecIn ));
	MOCK_METHOD1(SetMaxRotationSpeed, bool( float maxRotationSpeedDegPerSecIn ));
	MOCK_METHOD1(SetAbsoluteControlMode, bool( EAbsoluteControlMode modeIn ));
	MOCK_METHOD1(SetHullProtectionPresence, bool( EHullPresence presenceIn ));
	MOCK_METHOD1(SetOutdoorMode, bool( EOutdoorMode modeIn ));
	MOCK_METHOD1(SetGpsHomeLocation, bool( const TGpsHomeLocation &locationIn ));
	MOCK_METHOD0(ResetGpsHome, bool());
	MOCK_METHOD0(StartVideo, bool());
	MOCK_METHOD0(StopVideo, bool());

	MOCK_CONST_METHOD0(GetVideoFrame, TFrame());
};
}
