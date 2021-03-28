#include "BrainFlowGanglionNode.h"

#ifdef INCLUDE_DEVICE_BRAINFLOW

#include "../../EngineManager.h"
#include <brainflow/utils/brainflow_constants.h>
#include <brainflow/cpp-package/board_shim.h>


void BrainFlowGanglionNode::Init()
{
	DeviceInputNode::Init();
	{
		Core::AttributeSettings* attribute = RegisterAttribute("Serial port", "serialPort", "Serial port", Core::ATTRIBUTE_INTERFACETYPE_STRING);
		attribute->SetDefaultValue(Core::AttributeString::Create(""));
	}
	{
		Core::AttributeSettings* attribute = RegisterAttribute("MAC address", "macAddress", "MAC address", Core::ATTRIBUTE_INTERFACETYPE_STRING);
		attribute->SetDefaultValue(Core::AttributeString::Create(""));
	}
	{
		Core::AttributeSettings* attribute = RegisterAttribute("Timeout", "timeout", "Timeout", Core::ATTRIBUTE_INTERFACETYPE_INTSPINNER);
		attribute->SetDefaultValue(Core::AttributeInt32::Create(0));
		attribute->SetMinValue(Core::AttributeInt32::Create(0));
		attribute->SetMaxValue(Core::AttributeInt32::Create(CORE_INT32_MAX));
	}
	{
		Core::AttributeSettings* attribute = RegisterAttribute("Apply", "apply", "Apply", Core::ATTRIBUTE_INTERFACETYPE_CHECKBOX);
		attribute->SetDefaultValue(Core::AttributeBool::Create(false));
	}

	GetAttributeSettings(ATTRIB_RAWOUTPUT)->SetVisible(false);
	GetAttributeSettings(ATTRIB_UPLOAD)->SetVisible(false);
	GetAttributeSettings(ATTRIB_DEVICEINDEX)->SetVisible(false);
}

void BrainFlowGanglionNode::SynchronizeParams()
{
	mParams.serial_port = GetStringAttributeByName("serialPort");
	mParams.mac_address = GetStringAttributeByName("macAddress");
	mParams.timeout = GetInt32AttributeByName("timeout");
}

#endif
