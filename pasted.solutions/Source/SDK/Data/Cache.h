#pragma once
#include <Windows.h>
#include <unordered_map>

#include <SDK/DataModel/DataModel.h>
#include <SDK/VisualEngine/VisualEngine.h>
#include <SDK/DataModel/Player.h>

namespace Cache {
	inline i32 ScreenX = GetSystemMetrics(SM_CXSCREEN);
	inline i32 ScreenY = GetSystemMetrics(SM_CYSCREEN);

	inline std::string LocalVersion = "version-c2c9efad42eb44e5"; // wait for ts json
	inline std::string RemoteVersion = "version-c2c9efad42eb44e5"; // https://clientsettings.roblox.com/v2/client-version/WindowsPlayer

	inline RBX::DataModel DataModel;
	inline RBX::VisualEngine VisualEngine;

	inline std::vector<RBX::Player> PlayerList;
	inline std::unordered_map<u64, void*> PlayerAvatars;
}