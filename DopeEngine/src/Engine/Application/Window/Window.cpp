#include "Window.h"
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
#include <Engine/Application/Events/Events.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>
namespace DopeEngine
{
    Window* Window::create_window(const WindowCreateDescription& desc, void* windowData)
    {
#ifdef DOPE_OS_WINDOWS
        return new WindowsWindow(desc);
#endif
        return nullptr;
    }
    void Window::bind_window_and_device(Window* window, GraphicsDevice* childGraphicsDevice)
    {
        window->ChildGraphicsDevice = childGraphicsDevice;
    }
    GraphicsDevice* Window::get_child_graphics_device() const
    {
        return ChildGraphicsDevice;
    }

    String Window::get_title() const
    {
        return Title;
    }

    unsigned int Window::get_width() const
    {
        return Width;
    }

    unsigned int Window::get_height() const
    {
        return Height;
    }

    unsigned int Window::get_position_x() const
    {
        return PositionX;
    }

    unsigned int Window::get_position_y() const
    {
        return PositionY;
    }

    bool Window::is_visible() const
    {
        return Visibility;
    }

    bool Window::has_close_request() const
    {
        return CloseRequest;
    }

    void Window::set_title(const String& title)
    {
        set_title_impl(title);
        Title = title;
    }

    void Window::poll_messages()
    {
        poll_messages_impl();
    }

    void Window::present()
    {
        ChildGraphicsDevice->swap_swapchain_buffers(ChildGraphicsDevice->get_swapchain_framebuffer());
    }

    void Window::register_event_feed_listener(const Delegate<void, ApplicationEvent*>& functionDelegate)
    {
        EventFeedListeners.add(functionDelegate);
    }

    void Window::remove_event_feed_listener(const Delegate<void, ApplicationEvent*>& functionDelegate)
    {
        EventFeedListeners.remove(functionDelegate);
    }

    Window::Window(const WindowCreateDescription& desc)
    {
        Title = desc.Title;
        Width = desc.Width;
        Height = desc.Height;
        PositionX = desc.PositionX;
        PositionY = desc.PositionY;
        Visibility = false;
        CloseRequest = false;
    }

    void Window::set_child_graphics_device(GraphicsDevice* device)
    {
        /*
        * Validate if this device can display
        */

        /*
        * Set device
        */
        ChildGraphicsDevice = device;

        /*
        * Set resize event
        */
    }

    void Window::set_width(const unsigned int width)
    {
        Width = width;
    }

    void Window::set_height(const unsigned int height)
    {
        Height = height;
    }

    void Window::set_position_x(const unsigned int x)
    {
        PositionX = x;
    }

    void Window::set_position_y(const unsigned int y)
    {
        PositionY = y;
    }

    void Window::set_visibility(const bool state)
    {
        set_visibility_impl(state);
        Visibility = state;
    }

    void Window::set_close_request()
    {
        CloseRequest = true;
    }

    void Window::broadcast_window_event(ApplicationEvent* event)
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
                if (ChildGraphicsDevice != nullptr)
                    ChildGraphicsDevice->get_swapchain_framebuffer()->on_window_resize((WindowResizedEvent*)event);
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

        for (unsigned int i = 0; i < EventFeedListeners.get_cursor(); i++)
        {
            EventFeedListeners[i].invoke(event);
        }
    }

}