#include "DX11GUIRenderer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <IMGUI/imgui_impl_dx11.h>
namespace DopeEngine
{
    DX11GUIRenderer::DX11GUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device) : GUIRenderer(backendFlags,configFlags)
    {
        /*
        * Get dx11 device
        */
        const DX11GraphicsDevice* dx11Device = (const DX11GraphicsDevice*)device;

        /*
        * Init
        */
        ImGui_ImplDX11_Init(dx11Device->get_dx11_device().Get(), dx11Device->get_dx11_immediate_context().Get());
    }

    GraphicsAPIType DX11GUIRenderer::get_api_type() const
    {
        return GraphicsAPIType::Directx11;
    }

    void DX11GUIRenderer::begin_rendering_impl()
    {
        ImGui_ImplDX11_NewFrame();
    }

    void DX11GUIRenderer::render_impl(CommandBuffer* cmdBuffer)
    {
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

}