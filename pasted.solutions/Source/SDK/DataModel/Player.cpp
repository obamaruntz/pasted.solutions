#include <Global.h>
#include <SDK/Data/Offsets.h>
#include <SDK/DataModel/Player.h>

RBX::ModelInstance RBX::Player::GetModelInstance() {
	return Driver->PRead<RBX::ModelInstance>(this->Address + Offsets::PlayerInfo::ModelInstance);
}

f32 RBX::Player::GetHealth() {
	return Driver->PRead<f32>(this->GetModelInstance().GetHumanoid().Address + Offsets::PlayerInfo::Health);
}

f32 RBX::Player::GetMaxHealth() {
	return Driver->PRead<f32>(this->GetModelInstance().GetHumanoid().Address + Offsets::PlayerInfo::MaxHealth);
}