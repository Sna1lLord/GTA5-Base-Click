#include "main.hpp"

#include "../utility/logger/logger.hpp"
#include "../utility/signatures/signatures.hpp"
#include "../utility/rage/invoker/queue.hpp"
#include "../utility/config/config.hpp"
#include "script/manager.hpp"
#include "script/script.hpp"
#include "hooks/hooks.hpp"
#include "gui/gui.hpp"
#include "features/features.hpp"

static HANDLE coreThread;
static DWORD lpThreadId = 0;

void FeaturesScript() {
    while (true) {
        if (*Signatures::Instance()->definitions.gameState == 0) {
            Features::Instance()->Tick();
            Queue::Instance()->Tick();
        }

        Script::Current()->ScriptYield();
    }
}

DWORD WINAPI Core(LPVOID lpParam) {
    Logger::Instance()->Initialize();
    Logger::Instance()->Log("Hello World! \n");

    ScriptManager::Instance()->Add(std::make_unique<Script>(&FeaturesScript), "Features");

    Signatures::Instance()->Initialize();
    Features::Instance()->Initialize();
    Hooks::Instance()->Initialize();

    while (running) {
        if (GetAsyncKeyState(VK_END) & 1)
            running = false;

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    Hooks::Instance()->Uninitialize();
    Gui::Instance()->Uninitialize();
    Signatures::Instance()->Uninitialize();
    Features::Instance()->Uninitialize();
    Config::Instance()->Uninitialize();
    ScriptManager::Instance()->Uninitialize();
    Queue::Instance()->Uninitialize();

    Logger::Instance()->Log("Goodbye! \n");
    Logger::Instance()->Uninitialize();

    CloseHandle(coreThread);
    FreeLibraryAndExitThread((HMODULE)lpParam, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    UNREFERENCED_PARAMETER(lpvReserved);

    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

        coreThread = CreateThread(
            nullptr, 
            0, 
            Core, 
            hinstDLL, 
            0, 
            &lpThreadId
        );
    }

    return TRUE;
}