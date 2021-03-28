#include "BrainFlowCytonNode.h"

#ifdef INCLUDE_DEVICE_BRAINFLOW

#include "../../EngineManager.h"
#include <brainflow/utils/brainflow_constants.h>
#include <brainflow/cpp-package/board_shim.h>


void BrainFlowCytonNode::Init()
{
	DeviceInputNode::Init();
	{
		Core::AttributeSettings* attribute = RegisterAttribute("Serial port", "serialPort", "Serial port", Core::ATTRIBUTE_INTERFACETYPE_STRING);
		attribute->SetDefaultValue(Core::AttributeString::Create(""));
	}
	{
		Core::AttributeSettings* attribute = RegisterAttribute("Apply", "apply", "Apply", Core::ATTRIBUTE_INTERFACETYPE_CHECKBOX);
		attribute->SetDefaultValue(Core::AttributeBool::Create(false));
	}

	GetAttributeSettings(ATTRIB_RAWOUTPUT)->SetVisible(false);
	GetAttributeSettings(ATTRIB_UPLOAD)->SetVisible(false);
	GetAttributeSettings(ATTRIB_DEVICEINDEX)->SetVisible(false);
}

void BrainFlowCytonNode::SynchronizeParams()
{
	mParams.serial_port = GetStringAttributeByName("serialPort");
}

#endif
