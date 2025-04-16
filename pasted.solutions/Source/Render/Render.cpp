#include <Framework.h>
#include <Render/Render.h>
#include <Render/Menu.h>
#include <Render/Styles.h>

Render::Render(HWND Window) : Window(Window) {
	if (!CreateDeviceD3D(Window)) {
		CleanUpDeviceD3D();
	}
}

Render::~Render() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanUpDeviceD3D();
}

bool Render::CreateDeviceD3D(HWND Window) {
    if ((D3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
        return false;
    }

    ZeroMemory(&D3DParameters, sizeof(D3DParameters));

    D3DParameters.Windowed = TRUE;
    D3DParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    D3DParameters.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    D3DParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    D3DParameters.BackBufferCount = 2;
    D3DParameters.EnableAutoDepthStencil = TRUE;
    D3DParameters.AutoDepthStencilFormat = D3DFMT_D16;
    D3DParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // VSYNC = D3DPRESENT_INTERVAL_ONE

    if (D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DParameters, &D3DDevice) < 0) {
        return false;
    }

    return true;
}

void Render::CleanUpDeviceD3D() {
    if (D3DDevice) {
        D3DDevice->Release();
        D3DDevice = NULL;
    }

    if (D3D) {
        D3D->Release();
        D3D = NULL;
    }
}

void Render::ResetDeviceD3D() {
    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hr = D3DDevice->Reset(&D3DParameters);
    if (hr == D3DERR_INVALIDCALL) {
        IM_ASSERT(0);
    }

    ImGui_ImplDX9_CreateDeviceObjects();
}

void Render::RunRender() noexcept {
    ShowWindow(Window, SW_SHOWDEFAULT);
    UpdateWindow(Window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& IO = ImGui::GetIO(); (void)IO;
    IO.IniFilename = nullptr;

    ImGuiStyle& Style = ImGui::GetStyle();
    ImGui::SetupStyles(Style);
    ImGui::SetupFonts(IO);

    ImGui::StyleColorsDark();

    ImVec4 ClearColor = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(D3DDevice);

    while (true) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();

        POINT Point;

        if (GetCursorPos(&Point)) {
            IO.MousePos.x = Point.x;
            IO.MousePos.y = Point.y;
        }

        IO.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
        IO.MouseDown[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000;
        IO.MouseDown[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000;
        IO.MouseDown[3] = GetAsyncKeyState(VK_XBUTTON1) & 0x8000;
        IO.MouseDown[4] = GetAsyncKeyState(VK_XBUTTON2) & 0x8000;

        RenderMenu(ImGui::GetForegroundDrawList());

        ImGui::EndFrame();

        D3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        D3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR ClearColorDx = D3DCOLOR_RGBA((i32)(ClearColor.x * ClearColor.w * 255.0f), (i32)(ClearColor.y * ClearColor.w * 255.0f), (i32)(ClearColor.z * ClearColor.w * 255.0f), (i32)(ClearColor.w * 255.0f));
        D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, ClearColorDx, 1.0f, 0);

        if (D3DDevice->BeginScene() >= 0) {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            D3DDevice->EndScene();
        }

        HRESULT result = D3DDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && D3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDeviceD3D();
        }
    }
}