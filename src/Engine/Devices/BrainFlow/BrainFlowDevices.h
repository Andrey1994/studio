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

#include "brainflow/board_shim.h"

#ifdef INCLUDE_DEVICE_BRAINFLOW

// the base class for all BrainFlow Devices
class ENGINE_API BrainFlowDeviceBase : public BciDevice
{
	protected:
		int mBoardId;
		BoardShim* mBoardShim;

	public:
		// constructors & destructor
		BrainFlowDeviceBase(int boardId, DeviceDriver* driver);
		virtual ~BrainFlowDeviceBase() = default;
		
		// set/get board shim brainflow object
		void CreateBoardShim(BrainFlowInputParams params);
		BoardShim* GetBoardShim();
		void ReleaseBoardShim();
		
		// information
		double GetSampleRate() const override;

		void CreateElectrodes () override;
		void Update(const Core::Time& elapsed, const Core::Time& delta) override;
		//void Update(const Core::Time& elapsed, const Core::Time& delta) override;

};



// the default OpenBCI device class
class ENGINE_API BrainFlowDeviceCyton : public BrainFlowDeviceBase
{
public:
	enum {
		TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW_CYTON 
	};

	// constructors & destructor
	BrainFlowDeviceCyton(DeviceDriver* driver = NULL);

	Device* Clone() override										{ return new BrainFlowDeviceCyton(); }

	// information
	uint32 GetType() const override									{ return TYPE_ID; }
	const char* GetTypeName() const override						{ return "BrainFlowDeviceCyton_type"; }
	const char* GetHardwareName() const override					{ return "BrainFlowDeviceCyton_hardware"; }
	const char* GetUuid() const override							{ return "5108993a-fe1b-11e4-a322-1697f925e999"; }
	static const char* GetRuleName()								{ return "DEVICE_BrainFlowCyton_rule"; }
	double GetLatency () const override								{ return 0.1; }
	double GetExpectedJitter () const override						{ return 0.1; }
	bool IsWireless () const override								{ return true; }
	double GetTimeoutLimit() const override							{ return 60; } // Long timeout limit because channel config takes so long
};

class BrainFlowDevice : public Device
{
public:
	enum { TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW_BASE};

	BrainFlowDevice(int boardId, BrainFlowInputParams params, DeviceDriver* deviceDriver = nullptr)
		: Device(deviceDriver), mBoardId(boardId), mParams(params), mBoard(mBoardId, mParams) {
		CreateSensors();
	};

	void Init() {
		mBoard.prepare_session();
		mBoard.start_stream();
	}

	void Release()
	{
		mBoard.stop_stream();
		mBoard.release_session();
	}

	uint32 GetType() const override { return TYPE_ID; }
	const char* GetTypeName() const override { return "BrainFlowDevice_type"; }
	const char* GetHardwareName() const override { return "BrainFlowDevice_hardware"; }
	const char* GetUuid() const override { return "5108993a-fe1b-11e4-a322-1697f925e000"; }
	static const char* GetRuleName() { return "BrainFlowDevice_rule"; }
	Device* Clone() override { return new BrainFlowDevice(mBoardId, mParams); }
	void CreateSensors();
	void CreateElectrodes();
	void Update(const Core::Time& elapsed, const Core::Time& delta) override;

private:
	int mBoardId;
	BrainFlowInputParams mParams;
	BoardShim mBoard;

	Core::Array<EEGElectrodes::Electrode>	mElectrodes;		// electrode positions for the neuro sensors

};


// the default OpenBCI device class
class ENGINE_API BrainFlowDeviceSynthetic : public BrainFlowDeviceBase
{
public:
	enum {
		TYPE_ID = DeviceTypeIDs::DEVICE_TYPEID_BRAINFLOW_SYNTHETIC
	};

	// constructors & destructor
	BrainFlowDeviceSynthetic(DeviceDriver* driver = NULL);

	Device* Clone() override { return new BrainFlowDeviceSynthetic(); }
	void Init() override;
	// information
	uint32 GetType() const override { return TYPE_ID; }
	const char* GetTypeName() const override { return "BrainFlowDeviceSynthetic_type"; }
	const char* GetHardwareName() const override { return "BrainFlowDeviceSynthetic_hardware"; }
	const char* GetUuid() const override { return "5108993a-fe1b-11e4-a322-1697f925e888"; }
	static const char* GetRuleName() { return "DEVICE_BrainFlowDeviceSynthetic_rule"; }
	double GetLatency() const override { return 0.1; }
	double GetExpectedJitter() const override { return 0.1; }
	bool IsWireless() const override { return true; }
	double GetTimeoutLimit() const override { return 60; } // Long timeout limit because channel config takes so long
};



#endif

#endif
