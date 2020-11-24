/****************************************************************************
**
** Copyright 2019 neuromore co
** Contact: https://neuromore.com/contact
**
** Commercial License Usage
** Licensees holding valid commercial neuromore licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and neuromore. For licensing terms
** and conditions see https://neuromore.com/licensing. For further
** information use the contact form at https://neuromore.com/contact.
**
** neuromore Public License Usage
** Alternatively, this file may be used under the terms of the neuromore
** Public License version 1 as published by neuromore co with exceptions as 
** appearing in the file neuromore-class-exception.md included in the 
** packaging of this file. Please review the following information to 
** ensure the neuromore Public License requirements will be met: 
** https://neuromore.com/npl
**
****************************************************************************/

// include required files
#include "BrainFlowDriver.h"
#include "../DeviceHelpers.h"
#include <Devices/BrainFlow/BrainFlowDevices.h>
#include <EngineManager.h>
#include <System/SerialPort.h>
#include <QApplication>

#include <memory>

#ifdef INCLUDE_DEVICE_BRAINFLOW

using namespace Core;

BrainFlowDevice* BrainFlowDriver::deviceConnect(int boardId, const BrainFlowInputParams& params)
{
	auto device = std::make_unique<BrainFlowDevice>(boardId, params, this);
	device->Init();
	mDevices.Add(device.release());
	return mDevices.GetLast();
}

void BrainFlowDriver::deviceDisconnect(BrainFlowDevice& device)
{
	auto deviceIndex = mDevices.Find(&device);
	if (deviceIndex == CORE_INVALIDINDEX32)
	{
		// FAIL
		return;
	}
	device.Release();
	mDevices.Remove(deviceIndex);
}
#endif
