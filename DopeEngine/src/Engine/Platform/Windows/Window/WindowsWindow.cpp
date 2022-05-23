#include "WindowsWindow.h"
#include <Engine/Core/Assert.h>
#include <Engine/Application/Events/Events.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Input/Keys.h>
namespace DopeEngine
{
    //LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	WindowsWindow::WindowsWindow(const HINSTANCE processHandle, const WindowCreateDescription& description) : Window(description)
	{
		_create_win32_window(processHandle);
	}
	WindowsWindow::WindowsWindow(const WindowCreateDescription& description) : Window(description)
	{
		_create_win32_window(NULL);
	}
	WindowsWindow::~WindowsWindow()
	{

	}
    HWND WindowsWindow::get_win32_window_handle() const
    {
        return WindowHandle;
    }
    HDC WindowsWindow::get_win32_device_context() const
    {
        return WindowDeviceContext;
    }
	
	
	void WindowsWindow::_create_win32_window(const HINSTANCE processHandle)
	{
		constexpr wchar_t WINDOW_CLASS_NAME[] = L"Win32Window";

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc = (WNDPROC)Win32WindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(WindowsWindow);
        wc.hInstance = processHandle;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        //wc.hCursor = LoadIcon(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.hIconSm = NULL;


        WORD registerClsState = RegisterClassEx(&wc);
        ASSERT(registerClsState != NULL, "Win32Window", "Window registration failed!");


        HWND windowHandle = CreateWindowEx(
            0, // STYLES
            WINDOW_CLASS_NAME,
            L"Dummy Window Title",
            WS_OVERLAPPEDWINDOW,
            get_position_x(),get_position_y(), get_width(), get_height(),
            NULL,
            NULL,
            processHandle,
            this
        );
        ASSERT(windowHandle != NULL, "Win32Window", "Window creation failed!");

        WindowHandle = windowHandle;
        WindowDeviceContext = GetDC(windowHandle);

	}
    void WindowsWindow::set_title_impl(const String& title)
    {
        SetWindowTextA(WindowHandle, *title);
    }
    void WindowsWindow::poll_messages_impl()
    {
        MSG msg = { 0 };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WindowsWindow::set_visibility_impl(const bool state)
    {
        ShowWindow(WindowHandle, state == true ? SW_SHOW : SW_HIDE);
        UpdateWindow(WindowHandle);
    }
    WindowsWindow* GetWindowData(HWND windowHandle)
    {
        return (WindowsWindow*)GetWindowLongPtr(windowHandle, -21);
    }
    LRESULT CALLBACK WindowsWindow::Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_CREATE:
            {
                WindowsWindow* userWindow = (WindowsWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;

                SetWindowLongPtr(hwnd, -21, (LONG_PTR)userWindow);

                break;
            }
            case WM_SIZE:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));

                break;
            }
            case WM_MOVE:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new WindowPositionChangedEvent(LOWORD(lParam), HIWORD(lParam)));

                break;
            }
            case WM_KEYDOWN:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new KeyboardKeyDownEvent((unsigned int)wParam, false));

                break;
            }
            case WM_KEYUP:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new KeyboardKeyUpEvent((unsigned int)wParam));

                break;
            }
            case WM_CHAR:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new KeyboardCharEvent((unsigned int)wParam));

                break;
            }
            case WM_RBUTTONDOWN:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MouseButtonDownEvent(DOPE_MOUSE_BUTTON_2, false));

                break;
            }
            case WM_RBUTTONUP:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MouseButtonUpEvent(DOPE_MOUSE_BUTTON_2));
                break;
            }
            case WM_LBUTTONDOWN:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MouseButtonDownEvent(DOPE_MOUSE_BUTTON_1, false));

                break;
            }
            case WM_LBUTTONUP:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MouseButtonUpEvent(DOPE_MOUSE_BUTTON_1));

                break;
            }
            case WM_MOUSEMOVE:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MousePositionChangedEvent(LOWORD(lParam), HIWORD(lParam)));

                break;
            }
            case WM_MOUSEWHEEL:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new MouseScrolledEvent(GET_WHEEL_DELTA_WPARAM(wParam) / 120));

                break;
            }

            case WM_CLOSE:
            {
                WindowsWindow* window = GetWindowData(hwnd);

                window->broadcast_window_event(new WindowClosedEvent());

                break;
            }
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}