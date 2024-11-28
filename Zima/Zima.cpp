#include <windows.h>

// Function prototype for the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Entry point for a Windows application
int WINAPI WinMain(
    HINSTANCE hInstance,       // Handle to the current instance
    HINSTANCE hPrevInstance,   // Handle to the previous instance (unused)
    LPSTR     lpCmdLine,       // Command line arguments
    int       nCmdShow)        // Controls how the window is to be shown
{
    // Define a window class name
    const char CLASS_NAME[] = "Sample Window Class";

    // Initialize a WNDCLASS structure
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;      // Pointer to the window procedure
    wc.hInstance = hInstance;       // Handle to the instance
    wc.lpszClassName = CLASS_NAME;      // Window class name

    // Register the window class
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                          // Optional window styles
        CLASS_NAME,                 // Window class
        "Hello, WinAPI!",           // Window title
        WS_OVERLAPPEDWINDOW,        // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Display the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);    // Translate virtual-key messages
        DispatchMessage(&msg);     // Dispatch the message to the window procedure
    }

    return (int)msg.wParam;
}

// Window procedure: handles messages sent to the window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);    // Post a quit message and return
        return 0;

        // You can handle more messages here (e.g., WM_PAINT, WM_SIZE)

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam); // Default handling
    }
}
