#include <Cheats/Visual/Visuals.h>
#include <SDK/Data/Cache.h>
#include <SDK/DataModel/Player.h>

#include <Logging/Logger.h>
#include <thread>

void StaticBoxes() {
	// test
	
}

void Cheats::VisualsLoop() {
	std::thread(StaticBoxes).detach();
}