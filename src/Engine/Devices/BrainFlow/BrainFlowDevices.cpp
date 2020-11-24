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
#include "BrainFlowDevices.h"
#include "../../EngineManager.h"
#include "../../Core/LogManager.h"

#include <map>

#ifdef INCLUDE_DEVICE_BRAINFLOW

using namespace Core;

// get the available electrodes of the neuro headset
void BrainFlowDevice::CreateElectrodes()
{
	mElectrodes.Clear();

	try
	{
		int len = 0;
		std::string* eegNames = BoardShim::get_eeg_names(mBoardId, &len);
		mElectrodes.Reserve(len);
		// todo check that BrainFlow IDs match studio IDs
		for (int i = 0; i < len; i++)
		{
			mElectrodes.Add(GetEEGElectrodes()->GetElectrodeByID(eegNames[i].c_str()));
		}
	}
	catch (const BrainFlowException& err)
	{
		LogError(err.what());
	}
}


void BrainFlowDevice::Update(const Core::Time& elapsed, const Core::Time& delta)
{
	if (!mBoard.is_prepared())
		return;

	int data_count;
	double** board_data;
	board_data = mBoard.get_board_data(&data_count);
	int channels_count;
	int* channels_numbers = BoardShim::get_eeg_channels(mBoardId, &channels_count);
	std::string* channels_names = BoardShim::get_eeg_names(mBoardId, &channels_count);
	std::map<std::string, double*> data_by_channel;

	for (int i = 0; i < channels_count; ++i)
	{
		const std::string name = channels_names[i];
		int channels_number = channels_numbers[i];
		data_by_channel[name] = board_data[channels_number];
	}

	for (uint32 i = 0; i < mSensors.Size(); ++i)
	{
		auto* sensor = mSensors[i];
		auto iter = data_by_channel.find(sensor->GetName());
		if (iter == data_by_channel.end())
			continue;
		double* channel_data = iter->second;
		for (int j = 0; j < data_count; ++j)
		{
			double value = channel_data[j];
			sensor->AddQueuedSample(value);
		}
	}
	// update the neuro headset
	Device::Update(elapsed, delta);
}

#endif
