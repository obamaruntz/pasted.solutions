#pragma once
#include <Framework.h>

namespace Offsets {
	enum TypeInfo : u64 {
		Size = 0x8,
		Index = 0x10,
		ClassDescriptor = 0x18,
		Parent = 0x50,
		Name = 0x78,
		Children = 0x80,
	};

	enum TaskScheduler : u64 {
		JobsPointer = 0x6310810,
		JobName = 0x18,
		RenderViewPointer = 0x218,
		VisualEnginePointer = 0x10,
		DataModelPointer = 0x208,
		DataModelOffset = 0x1B0,
	};

	enum PlayerInfo : u64 {
		ModelInstance = 0x2e8,
		Health = 0x19C,
		MaxHealth = 0x1BC,
	};
}