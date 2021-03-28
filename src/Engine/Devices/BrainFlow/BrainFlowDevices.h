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

#ifndef __NEUROMORE_BRAINFLOWHEADSET_H
#define __NEUROMORE_BRAINFLOWHEADSET_H

// include required headers
#include "../../BciDevice.h"
#include "../../DeviceDriver.h"

#ifdef INCLUDE_DEVICE_BRAINFLOW

#include "brainflow/cpp-package/board_shim.h"
#include <brainflow/utils/brainflow_constants.h>
#include <brainflow/board_controller/brainflow_input_params.h>
#include <future>

class BrainFlowDevice : public BciDevice
{
public:
	enum { TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW };

	virtual ~BrainFlowDevice() {}
	BrainFlowDevice(DeviceDriver* deviceDriver = nullptr);
	BrainFlowDevice(BoardIds boardId, BrainFlowInputParams params, DeviceDriver* deviceDriver = nullptr);

	bool Connect() override;
	bool Disconnect() override;
	
	virtual uint32 GetType() const override { return BrainFlowDevice::TYPE_ID; }
	const char* GetTypeName() const override { return "BrainFlowDevice_type"; }
	const char* GetHardwareName() const override { return "BrainFlowDevice_hardware"; }
	const char* GetUuid() const override { return "5108993a-fe1b-11e4-a322-1697f925e000"; }
	static const char* GetRuleName() { return "BrainFlowDevice_rule"; }
	void Update(const Core::Time& elapsed, const Core::Time& delta) override;

	const BrainFlowInputParams& GetParams() const { return mParams; }
	int GetBoardId() const;

protected:
	void CreateElectrodes();
	Device* Clone() override { return new BrainFlowDevice(); }
	bool DoesConnectingFinished() const;
	bool InitAfterConnected();

	// information
	double GetSampleRate() const override;

	const BoardIds mBoardId;
	const BrainFlowInputParams mParams;
	std::future<std::unique_ptr<BoardShim>> mFuture;
	std::unique_ptr<BoardShim> mBoard = nullptr;
};

class BrainFlowCytonDevice : public BrainFlowDevice
{
public:
	enum { TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW_CYTON };
	virtual uint32 GetType() const override { return BrainFlowCytonDevice::TYPE_ID; }

	BrainFlowCytonDevice(DeviceDriver* deviceDriver = nullptr) : BrainFlowDevice(deviceDriver)																	 {}
	BrainFlowCytonDevice(BoardIds boardId, BrainFlowInputParams params, DeviceDriver* deviceDriver = nullptr) : BrainFlowDevice(boardId, params, deviceDriver)   {}

	const char* GetTypeName() const override { return "BrainFlowCytonDevice_type"; }
	const char* GetHardwareName() const override { return "BrainFlowCytonDevice_hardware"; }
	const char* GetUuid() const override { return "5308993a-fe1b-11e4-a322-1697f925e000"; }
	static const char* GetRuleName() { return "BrainFlowCytonDevice_rule"; }

protected:
	Device* Clone() override { return new BrainFlowCytonDevice(); }
};

class BrainFlowGanglionDevice : public BrainFlowDevice
{
public:
	enum { TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW_GANGLION };
	virtual uint32 GetType() const override { return BrainFlowGanglionDevice::TYPE_ID; }

	BrainFlowGanglionDevice(DeviceDriver* deviceDriver = nullptr) : BrainFlowDevice(deviceDriver)																	{}
	BrainFlowGanglionDevice(BoardIds boardId, BrainFlowInputParams params, DeviceDriver* deviceDriver = nullptr) : BrainFlowDevice(boardId, params, deviceDriver)   {}

	const char* GetTypeName() const override { return "BrainFlowGanglionDevice_type"; }
	const char* GetHardwareName() const override { return "BrainFlowGanglionDevice_hardware"; }
	const char* GetUuid() const override { return "5208993a-fe1b-11e4-a322-1697f925e000"; }
	static const char* GetRuleName() { return "BrainFlowGanglionDevice_rule"; }

protected:
	Device* Clone() override { return new BrainFlowGanglionDevice(); }
};

#endif

#endif
