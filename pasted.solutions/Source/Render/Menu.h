#pragma once
#include <Global.h>
#include <ImGui/imgui.h>
#include <Render/Render.h>
#include <SDK/Data/Cache.h>

static const int WIDTH = 650;
static const int HEIGHT = 600;

enum STATE {
	Visuals,
	Aimbot,
	Misc,
	Config
};

inline void RenderMenu(ImDrawList* Draw) {
	using namespace ImGui;

	static STATE State = STATE::Visuals;

	SetNextWindowSize(ImVec2(WIDTH, HEIGHT), ImGuiCond_Always);
	SetNextWindowPos(ImVec2((Cache::ScreenX - WIDTH) * 0.5f, (Cache::ScreenY - HEIGHT) * 0.5f), ImGuiCond_Once);
	Begin("## Pasted.Solutions", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	PushFont(Fonts::K2DBold32);
	Text("PASTED.SOLUTIONS");
	PopFont();

	End();
}