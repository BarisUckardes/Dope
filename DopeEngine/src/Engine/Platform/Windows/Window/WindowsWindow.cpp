#include "WindowsWindow.h"
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
    LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
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
    void WindowsWindow::set_visibility_impl(const bool state)
	{
		ShowWindow(WindowHandle, state == true ? SW_SHOW : SW_HIDE);
	}
	void WindowsWindow::set_title_impl(const String& title)
	{
		SetWindowTextA(WindowHandle, *title);
	}
	void WindowsWindow::swap_buffers_impl()
	{
		SwapBuffers(WindowDeviceContext);
	}
	void WindowsWindow::poll_messages_impl()
	{
		/*
		* Iterate current pending messages and dispatch them
		*/
		MSG msg = { 0 };
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void WindowsWindow::_create_win32_window(const HINSTANCE processHandle)
	{
        LOG("WindowsWindow", "Hello");
		constexpr wchar_t WINDOW_CLASS_NAME[] = L"Win32Window";

		/*
		* Create window class
		*/
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc = (WNDPROC)Win32WindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(WindowsWindow);
        wc.hInstance = processHandle;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hCursor = LoadIcon(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.hIconSm = NULL;

        /*
        * Register window class
        */
        WORD registerClsState = RegisterClassEx(&wc);

        /*
        * Validate registertration
        */
        ASSERT(registerClsState != NULL, "Win32Window", "Window registration failed!");

        /*
        * Create window
        */
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

        /*
        * Validate window creation
        */
        ASSERT(windowHandle != NULL, "Win32Window", "Window creation failed!");

        /*
        * Initialize
        */
        WindowHandle = windowHandle;
        WindowDeviceContext = GetDC(windowHandle);

	}
    WindowsWindow* GetWindowData(HWND windowHandle)
    {
        return (WindowsWindow*)GetWindowLongPtr(windowHandle, -21);
    }
    LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_CREATE:
            {
                /*
                * Set window data
                */
                WindowsWindow* userWindow = (WindowsWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
                SetWindowLongPtr(hwnd, -21, (LONG_PTR)userWindow);

                break;
            }
            case WM_SIZE:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set new size properties
                */
                //  window->Width = LOWORD(lParam);
                 // window->Height = HIWORD(lParam);
                break;
            }
            case WM_KEYDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set key
                */
                // window->Keys[(unsigned char)wParam] = U_TRUE;
               //  LOG("Win32", "Key down: %d", (unsigned int)wParam);
                break;
            }
            case WM_KEYUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set key
                */
                // window->Keys[(unsigned char)wParam] = GL_FALSE;
                break;
            }
            case WM_RBUTTONDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set button
                */
                // window->Buttons[1] = U_TRUE;

                break;
            }
            case WM_RBUTTONUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set button
                */
                //window->Buttons[1] = U_FALSE;
                break;
            }
            case WM_LBUTTONDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set button
                */
                //window->Buttons[0] = U_TRUE;
                break;
            }
            case WM_LBUTTONUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set button
                */
                //window->Buttons[0] = U_FALSE;
                break;
            }
            case WM_MOUSEMOVE:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                unsigned int x = LOWORD(lParam);
                unsigned int y = HIWORD(lParam);


                //window->DeltaX = (float)x - (float)window->X;
                //window->DeltaY = (float)y - (float)window->Y;
               // window->X = x;
               // window->Y = y;
                break;
            }
            case WM_MOUSEWHEEL:
            {
                /*
                 * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                short wheelAmount = GET_WHEEL_DELTA_WPARAM(wParam) / 120;

                //  window->Wheel = wheelAmount;
                break;
            }

            case WM_CLOSE:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Set close request
                */
                // window->CloseRequest = U_TRUE;
                break;
            }
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}