#include <Overlay/Overlay.h>
#include <Logging/Logger.h>
#include <SDK/Data/Cache.h>
#include <dwmapi.h>

HWND Overlay::GetOverlayWindow() {
	HWND Overlay = FindWindowA("MedalOverlayClass", "MedalOverlay");

	if (!Overlay) {
		Logger::Log(Type::FAIL, "Failed to get Medal's overlay window, make sure it is running.");
		return Overlay;
	}

	MARGINS Margins = { -1 };

	if (DwmExtendFrameIntoClientArea(Overlay, &Margins) != S_OK) {
		Logger::Log(Type::FAIL, "Failed to initialize Medal's overlay window, try restarting.");
		return Overlay;
	}

	SetWindowPos(Overlay, 0, 0, 0, Cache::ScreenX, Cache::ScreenY, SWP_HIDEWINDOW);
	UpdateWindow(Overlay);

	return Overlay;
}
