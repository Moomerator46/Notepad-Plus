#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "window.h"
#include "editor.h"

// Entry point for Notepad Pro
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Boot log
    std::cout << "🔷 Notepad Pro boot sequence initiated...\n";

    // Register window class
    if (!RegisterMainWindowClass(hInstance)) {
        MessageBox(nullptr, "Failed to register window class.", "Error", MB_ICONERROR);
        return -1;
    }

    // Create main application window
    HWND hwnd = CreateMainWindow(hInstance);
    if (!hwnd) {
        MessageBox(nullptr, "Failed to create main window.", "Error", MB_ICONERROR);
        return -1;
    }

    // Show window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Initialize editor module
    InitEditor(hwnd);
    LoadDefaultFile(); // optional: preload file like README.md or lore.rosc

    // Begin message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    std::cout << "🔷 Shutdown sequence complete.\n";
    return static_cast<int>(msg.wParam);
}
