#pragma once
#include <SDK/Instance.h>

namespace RBX {
	class ModelInstance : public Instance {
	public:
		RBX::Instance GetHumanoid();
		RBX::Instance GetHumanoidRootPart();
	};
}