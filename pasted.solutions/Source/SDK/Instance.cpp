#include <Global.h>
#include <SDK/Instance.h>
#include <SDK/Data/Offsets.h>

std::string RBX::Instance::GetName() {
	u64 Name = Driver->PRead<u64>(this->Address + Offsets::TypeInfo::Name);

	if (Name) {
		return Driver->ReadStr(Name);
	}

	return "Unknown";
}

std::string RBX::Instance::GetClassName() {
	u64 ClassDescriptor = Driver->PRead<u64>(this->Address + Offsets::TypeInfo::ClassDescriptor);
	u64 Size = Driver->PRead<u64>(ClassDescriptor + Offsets::TypeInfo::Size);

	if (Size) {
		return Driver->ReadStr(Size);
	}

	return "Unknown";
}

RBX::Instance RBX::Instance::FindFirstChild(const std::string& Name) {
	std::vector<RBX::Instance> Children = this->GetChildren();

	for (RBX::Instance& Child : Children) {
		if (Child.GetName() == Name) {
			return Child;
		}
	}

	return RBX::Instance();
}

RBX::Instance RBX::Instance::FindFirstChildByClass(const std::string& Class) {
	std::vector<RBX::Instance> Children = this->GetChildren();

	for (RBX::Instance& Child : Children) {
		if (Child.GetClassName() == Class) {
			return Child;
		}
	}

	return RBX::Instance();
}

std::vector<RBX::Instance> RBX::Instance::GetChildren() {
	std::vector<RBX::Instance> Instances;

	u64 Start = Driver->PRead<u64>(this->Address + Offsets::TypeInfo::Children);
	u64 End = Driver->PRead<u64>(Start + Offsets::TypeInfo::Size);

	for (u64 Children = Driver->PRead<u64>(Start); Children != End; Children += Offsets::TypeInfo::Index) {
		Instances.emplace_back(RBX::Instance(Driver->PRead<u64>(Children)));
	}

	return Instances;
}