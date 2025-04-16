#include <thread>
#include <chrono>

#include <Cheats/DataCollector.h>
#include <SDK/Data/Cache.h>

// https://thumbnails.roblox.com/v1/users/avatar-headshot?userIds=<$userid>&size=150x150&format=Png

void UpdatePlayers() {
	RBX::Instance PlayersService = Cache::DataModel.FindFirstChild("Players");

	while (true) {
		for (RBX::Instance& Child : PlayersService.GetChildren()) {
			Cache::PlayerList.push_back(RBX::Player(Child.Address));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		Cache::PlayerList.clear();
	}
}

void Cheats::CollectData() {
	std::thread(UpdatePlayers).detach();
}