// Basic DLL
// that just logs Hello!
// and exits after 5 seconds.

// for allocating console,
// typedefs (e.g. BOOL),
// macros (like APIENTRY),
// and Freeing the library & exiting the thread
// (FreeLibraryAndExitThread)
#include <Windows.h>
// for specifying how many seconds to yield
#include <chrono>
// for the std::this_thread::sleep_for
// to yield the entry thread for 5 seconds
#include <thread>

/// <summary>
/// Logs "Hello!"
/// and exits after 5 seconds.
/// 
/// Called with the hModule
/// once the DLL is loaded.
/// </summary>
/// <param name="hModule">The module
/// representing this DLL.</param>
void entry(HMODULE hModule) {
    // create a console window for us
    AllocConsole();
    // holds the stdout file
    FILE* IO{};
    // sets the console title
    SetConsoleTitle("Hyperion isn't here!");
    // bind IO to CONOUT so we can print things
    // (without this, nothing will be displayed)
    freopen_s(&IO, "CONOUT$", "w", stdout);
    // logs "Hello!" into the console
    printf_s("Hello!\n");
    // logs "Freeing console and exiting in 5 seconds..."
    // into the console
    printf_s("Freeing console and exiting in 5 seconds...\n");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // Closes the console window
    FreeConsole();
    // Frees the library and exit/terminates this thread.
    FreeLibraryAndExitThread(hModule, 0);
}

// Called when a event
// like the DLL being loaded (DLL_PROCESS_ATTACHED) happens
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason)
{
    // are we being loaded/attached?
    if (reason == DLL_PROCESS_ATTACH)
        // run the entry function
        std::thread(entry, hModule).detach();
    // returns 1 (TRUE), indicating success.
    return TRUE;
}

