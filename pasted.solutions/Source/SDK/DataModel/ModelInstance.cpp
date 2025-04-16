#include <SDK/DataModel/ModelInstance.h>

RBX::Instance RBX::ModelInstance::GetHumanoid() {
	return this->FindFirstChild("Humanoid");
}

RBX::Instance RBX::ModelInstance::GetHumanoidRootPart() {
	return this->FindFirstChild("HumanoidRootPart");
}