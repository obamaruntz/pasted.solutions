#pragma once
#include <string>
#include <vector>

#include <Framework.h>

namespace RBX {
	class Instance {
	public:
		u64 Address;

		Instance() = default;
		Instance(u64 Address) : Address(Address) {}

		std::string GetName();
		std::string GetClassName();

		RBX::Instance FindFirstChild(const std::string& Name);
		RBX::Instance FindFirstChildByClass(const std::string& Class);
		std::vector<RBX::Instance> GetChildren();

		bool operator==(RBX::Instance& Other) {
			return Address == Other.Address;
		}
	};
}