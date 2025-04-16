#pragma once
#include <Windows.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx9.h>
#include <ImGui/imgui_impl_win32.h>

#include <d3d9.h>

class Render {
public:
	Render(HWND Window);
	~Render();

	LPDIRECT3DDEVICE9 D3DDevice = nullptr;
	LPDIRECT3D9 D3D = nullptr;
	D3DPRESENT_PARAMETERS D3DParameters = {};

	void RunRender() noexcept;
private:
	HWND Window = nullptr;

	bool CreateDeviceD3D(HWND Window);
	void CleanUpDeviceD3D();
	void ResetDeviceD3D();
};

namespace Fonts {
	inline ImFont* PoppinsRegular13 = nullptr;
	inline ImFont* PoppinsSemibold24 = nullptr;
	inline ImFont* K2DBold32 = nullptr;
	inline ImFont* K2DRegular32 = nullptr;
}