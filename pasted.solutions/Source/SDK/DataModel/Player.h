#pragma once
#include <SDK/Instance.h>
#include <SDK/DataModel/ModelInstance.h>

namespace RBX {
	class Player : public Instance {
	public:
		f32 GetHealth();
		f32 GetMaxHealth();

		RBX::ModelInstance GetModelInstance();
	};
}