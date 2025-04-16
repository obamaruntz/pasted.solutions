#pragma once
#include <memory>
#include <chrono>
#include <thread>
#include <Mapper/Mapper.h>
#include <Driver/Communication.h>
#include <Render/Render.h>
#include <Overlay/Overlay.h>

inline std::unique_ptr<Mapper> DriverMapper;
inline std::unique_ptr<Communication> Driver;
inline std::unique_ptr<Render> Renderer;

inline void SafeExit(bool ShouldWait) {
	if (ShouldWait) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	ShowWindow(Overlay::GetOverlayWindow(), SW_HIDE);

	DriverMapper.release();
	Driver.release();
	Renderer.release();

	exit(0);
}