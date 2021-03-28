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

#ifndef __NEUROMORE_BRAINFLOWGANGLIONNODE_H
#define __NEUROMORE_BRAINFLOWGANGLIONNODE_H

#include "../../Config.h"

#ifdef INCLUDE_DEVICE_BRAINFLOW

#include "BrainFlowDevices.h"
#include "BrainFlowNodes.h"
#include "../../Graph/DeviceInputNode.h"
#include <brainflow/board_controller/brainflow_input_params.h>

class ENGINE_API BrainFlowGanglionNode : public BrainFlowNode
{
public:
	int mBoardID;
	BrainFlowInputParams mParams;

	enum { TYPE_ID = 0xD00000 | BrainFlowGanglionDevice::TYPE_ID };
	static const char* Uuid()												{ return "203fc2da-fe3b-12e4-a322-1693f925ec7b"; }

	~BrainFlowGanglionNode()				   																{}
	BrainFlowGanglionNode(Graph* parentGraph) : BrainFlowNode(NULL, BrainFlowGanglionNode::TYPE_ID)		    { mBoardID = (int)BoardIds::GANGLION_BOARD; }

	const char* GetReadableType() const override							{ return "BrainFlowGanglionDevice"; }
	virtual const char* GetTypeUuid() const override					    { return BrainFlowGanglionNode::Uuid(); }
	virtual uint32 GetType() const override									{ return BrainFlowGanglionNode::TYPE_ID; }
	GraphObject* Clone(Graph* parentGraph) override							{ BrainFlowGanglionNode* clone = new BrainFlowGanglionNode(parentGraph); return clone; }

	void Init() override;

protected:
	void SynchronizeParams() override;

};


#endif

#endif
