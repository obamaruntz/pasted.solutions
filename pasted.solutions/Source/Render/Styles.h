#include <ImGui/imgui.h>
#include <Render/Render.h>
#include <Assets/PoppinsRegular.h>
#include <Assets/PoppinsSemibold.h>
#include <Assets/K2DRegular.h>
#include <Assets/K2DBold.h>

namespace ImGui {
	inline void SetupStyles(ImGuiStyle& Style) {
		Style.WindowBorderSize = 0.f;
	}

	inline void SetupFonts(ImGuiIO& IO) {
		// Default: Poppins Regular 17.f
		IO.Fonts->AddFontFromMemoryTTF(PoppinsRegular, sizeof(PoppinsRegular), 17.f);

		Fonts::PoppinsRegular13  = IO.Fonts->AddFontFromMemoryTTF(PoppinsRegular, sizeof(PoppinsRegular), 13.f);
		Fonts::PoppinsSemibold24 = IO.Fonts->AddFontFromMemoryTTF(PoppinsSemibold, sizeof(PoppinsSemibold), 24.f);
		Fonts::K2DBold32         = IO.Fonts->AddFontFromMemoryTTF(K2DBold, sizeof(K2DBold), 32.f);
		Fonts::K2DRegular32      = IO.Fonts->AddFontFromMemoryTTF(K2DRegular, sizeof(K2DRegular), 32.f);
	}
}