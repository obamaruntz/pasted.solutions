#include <thread>
#include <chrono>

#include <Global.h>
#include <Framework.h>
#include <Logging/Logger.h>
#include <Mapper/Mapper.h>
#include <Mapper/Assets/Bytes.h>
#include <Driver/Communication.h>
#include <Overlay/Overlay.h>
#include <SDK/Scheduler/TaskScheduler.h>
#include <SDK/Data/Cache.h>
#include <Cheats/DataCollector.h>
#include <Cheats/Visual/Visuals.h>

auto main(i32 argc, i8** argv) -> i32 {
	Logger::Log(Type::OK, "[Entry] main() called with %d argument(s).\n", argc);

	DriverMapper = std::make_unique<Mapper>();
	DriverMapper->MapDriver(DriverBytes);

	Logger::Log(Type::OK, "[Entry] Driver mapping attempted.\n");

	Driver = std::make_unique<Communication>();

	if (!Driver->IsConnected()) {
		Logger::Log(Type::FAIL, "[Entry] Driver was not mapped successfully.\n");
		Logger::Log(Type::FAIL, "[Entry] Disable HVCI or the Vulnerable Driver Blocklist on W11 then restart.\n");
		SafeExit(true);
	}

	Logger::Log(Type::OK, "[Entry] Connected to driver successfully.\n");

	Driver->FindProcess("RobloxPlayerBeta.exe");

	if (Driver->ProcessID == 0) {
		Logger::Log(Type::FAIL, "Roblox Process not found... is Roblox open and running?\n");
		SafeExit(true);
	}

	Logger::Log(Type::OK, "[Entry] RobloxPlayerBeta.exe Process ID: %u\n", Driver->ProcessID);

	Driver->FindImage();

	if (Driver->ImageAddress == 0) {
		Logger::Log(Type::FAIL, "Failed to get Roblox modules base address, restart your PC.\n");
		SafeExit(true);
	}

	Logger::Log(Type::OK, "[Entry] RobloxPlayerBeta.exe Image Address: 0x%llx\n", Driver->ImageAddress);

	Driver->VAttach(Driver->ProcessID);

	RBX::TaskScheduler TaskScheduler;

	if (TaskScheduler.IsLoaded()) {
		// TaskScheduler.PrintJobs();

		Cache::DataModel = TaskScheduler.GetDataModel();
		Cache::VisualEngine = TaskScheduler.GetVisualEngine();

		Logger::Log(Type::OK, "[Entry] DataModel Address:    0x%llx\n", Cache::DataModel.Address);
		Logger::Log(Type::OK, "[Entry] VisualEngine Address: 0x%llx\n", Cache::VisualEngine.Address);

		Renderer = std::make_unique<Render>(Overlay::GetOverlayWindow());

		std::thread(&Render::RunRender, Renderer.get()).detach();
		std::thread(Cheats::CollectData).detach();
		std::thread(Cheats::VisualsLoop).detach();

		while (!GetAsyncKeyState(VK_END)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		SafeExit(false);
	}
	else {
		Logger::Log(Type::OK, "[Entry] TaskScheduler not found. Did Roblox update?\n");
		Logger::Log(Type::OK, "[Entry] Local Version: %s, Remote Version: %s\n", Cache::LocalVersion, Cache::RemoteVersion);
		SafeExit(true);
	}

	SafeExit(false);
}
