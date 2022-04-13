#include "WindowsWindow.h"
#include <Engine/Core/Assert.h>
#include <Engine/Application/Events/Events.h>
namespace DopeEngine
{
    //LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	WindowsWindow::WindowsWindow(const HINSTANCE processHandle, const WindowCreateDescription& description)
	{
        /*
         * Initialize
         */
        Title = description.Title;
        Width = description.Width;
        Height = description.Height;
        PositionX = description.PositionX;
        PositionY = description.PositionY;
        CloseRequest = false;

        /*
        * Create win32
        */
		_create_win32_window(processHandle);
	}
	WindowsWindow::WindowsWindow(const WindowCreateDescription& description)
	{
        /*
        * Initialize
        */
        Title = description.Title;
        Width = description.Width;
        Height = description.Height;
        PositionX = description.PositionX;
        PositionY = description.PositionY;
        CloseRequest = false;

        /*
        * Create win32
        */
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
	void WindowsWindow::set_title(const String& title)
	{
        /*
         * Set win32 window title
         */
        SetWindowTextA(WindowHandle, *title);

        /*
        * Set the title
        */
        Title = title;
		
	}
	void WindowsWindow::swap_buffers()
	{
		SwapBuffers(WindowDeviceContext);
	}
	void WindowsWindow::poll_messages()
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
    GraphicsDevice* WindowsWindow::get_graphics_device() const
    {
        return GDevice;
    }
    bool WindowsWindow::has_close_request() const
    {
        return CloseRequest;
    }
    void WindowsWindow::assing_graphics_device(GraphicsDevice* device)
    {
        GDevice = device;
    }
    void WindowsWindow::set_application_event_feed(const Delegate<void, ApplicationEvent*>& functionDelegate)
    {
        ApplicationEventFeedDelegate = functionDelegate;
    }
    void WindowsWindow::set_close_request()
    {
        CloseRequest = true;
    }
  
    void WindowsWindow::broadcast_application_event(ApplicationEvent* event)
    {
        /*
        * Catch events
        */
        const ApplicationEventType type = event->get_type();

        switch (type)
        {
        case DopeEngine::ApplicationEventType::Undefined:
            break;
        case DopeEngine::ApplicationEventType::KeyboardKeyDown:
            break;
        case DopeEngine::ApplicationEventType::KeyboardKeyUp:
            break;
        case DopeEngine::ApplicationEventType::KeyboardChar:
            break;
        case DopeEngine::ApplicationEventType::WindowResized:
            break;
        case DopeEngine::ApplicationEventType::WindowClosed:
            CloseRequest = true;
            break;
        case DopeEngine::ApplicationEventType::WindowPositionChanged:
            break;
        case DopeEngine::ApplicationEventType::MouseButtonDown:
            break;
        case DopeEngine::ApplicationEventType::MouseButtonUp:
            break;
        case DopeEngine::ApplicationEventType::MouseScrolled:
            break;
        case DopeEngine::ApplicationEventType::MousePositionChanged:
            break;
        case DopeEngine::ApplicationEventType::WindowFileDrop:
            break;
        default:
            break;

        }

        /*
        * Forward event to application feed
        */
        ApplicationEventFeedDelegate.invoke(event);

        /*
        * Dummy debug
        */
        //LOG("Window", "Event broacasting -> %s", *event->get_as_string());
    }
    unsigned int WindowsWindow::get_width() const
    {
        return Width;
    }
    unsigned int WindowsWindow::get_height() const
    {
        return Height;
    }
    unsigned int WindowsWindow::get_position_x() const
    {
        return PositionX;
    }
    unsigned int WindowsWindow::get_position_y() const
    {
        return PositionY;
    }
    String WindowsWindow::get_title() const
    {
        return Title;
    }
    bool WindowsWindow::is_visible() const
    {
        return Visibility;
    }
   
 
    void WindowsWindow::set_window_visibility(bool state)
    {
        /*
        * 
        * Set win32 window visiblity
        */
        ShowWindow(WindowHandle, state == true ? SW_SHOW : SW_HIDE);
        UpdateWindow(WindowHandle);

        /*
        * Set visibility
        */
        Visibility = state;
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
                * Broadcast event
                */
                window->broadcast_application_event(new WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
                break;
            }
            case WM_MOVE:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new WindowPositionChangedEvent(LOWORD(lParam), HIWORD(lParam)));
                break;
            }
            case WM_KEYDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new KeyboardKeyDownEvent((unsigned int)wParam, false));
                break;
            }
            case WM_KEYUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new KeyboardKeyUpEvent((unsigned int)wParam));
                break;
            }
            case WM_RBUTTONDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new MouseButtonDownEvent(0, false));
                break;
            }
            case WM_RBUTTONUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Boardcast event
                */
                window->broadcast_application_event(new MouseButtonUpEvent(0));
                break;
            }
            case WM_LBUTTONDOWN:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                 /*
                * Broadcast event
                */
                window->broadcast_application_event(new MouseButtonDownEvent(1, false));
                break;
            }
            case WM_LBUTTONUP:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                 /*
                * Boardcast event
                */
                window->broadcast_application_event(new MouseButtonUpEvent(1));
                break;
            }
            case WM_MOUSEMOVE:
            {
                /*
                * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new MousePositionChangedEvent(LOWORD(lParam), HIWORD(lParam)));
                break;
            }
            case WM_MOUSEWHEEL:
            {
                /*
                 * Get window data
                */
                WindowsWindow* window = GetWindowData(hwnd);

                /*
                * Broadcast event
                */
                window->broadcast_application_event(new MouseScrolledEvent(GET_WHEEL_DELTA_WPARAM(wParam) / 120));
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
                window->broadcast_application_event(new WindowClosedEvent());
                break;
            }
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}