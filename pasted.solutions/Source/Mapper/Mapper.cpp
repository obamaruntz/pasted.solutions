#include <windows.h>
#include <Mapper/Mapper.h>
#include <Mapper/kdmapper/kdmapper.hpp>
#include <Framework.h>

static LONG WINAPI DefaultCrashHandler(EXCEPTION_POINTERS* ExceptionInfo) {
    /*if (manager::mapper->iqvw64e_device_handle)
        intel_driver::Unload(manager::mapper->iqvw64e_device_handle);*/

    //FIXME UNLOAD HANDLE

    return EXCEPTION_EXECUTE_HANDLER;
}

static bool WtfIsThisCallback(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr) {
    UNREFERENCED_PARAMETER(param1);
    UNREFERENCED_PARAMETER(param2);
    UNREFERENCED_PARAMETER(allocationPtr);
    UNREFERENCED_PARAMETER(allocationSize);
    UNREFERENCED_PARAMETER(mdlptr);
    return true;
}

Mapper::Mapper() : iqvw64e(nullptr) {}

Mapper::~Mapper() = default;

bool Mapper::MapDriver(u8* /*Ts Pointer Decay Pmo.*/ image) {
    SetUnhandledExceptionFilter(DefaultCrashHandler);

    bool Free = false, MdlMode = false, IndPagesMode = false, PassAllocPtr = false;

    iqvw64e = intel_driver::Load();

    if (iqvw64e == INVALID_HANDLE_VALUE)
        return false;

    kdmapper::AllocationMode Mode = kdmapper::AllocationMode::AllocatePool;

    if (MdlMode && IndPagesMode) {
        intel_driver::Unload(iqvw64e);
        return false;
    }
    else if (MdlMode) {
        Mode = kdmapper::AllocationMode::AllocateMdl;
    }
    else if (IndPagesMode) {
        Mode = kdmapper::AllocationMode::AllocateIndependentPages;
    }

    NTSTATUS exit_code = 0;
    if (!kdmapper::MapDriver(iqvw64e, image, 0, 0, Free, true, Mode, PassAllocPtr, WtfIsThisCallback, &exit_code)) {
        intel_driver::Unload(iqvw64e);
        return false;
    }

    if (!intel_driver::Unload(iqvw64e)) {
        // FIXME: PRINT
    }

	return true;
}