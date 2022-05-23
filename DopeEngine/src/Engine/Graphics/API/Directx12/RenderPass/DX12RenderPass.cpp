#include "DX12RenderPass.h"
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12Shader.h>
#include <Engine/Graphics/API/Directx12/RenderPass/DX12RenderPassUtils.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
#include <Engine/Graphics/API/Directx11/Vertex/DX11VertexUtils.h>
#include <Engine/Graphics/API/Directx12/Resource/DX12ResourceLayoutUtils.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12ShaderUtils.h>
#include <Engine/Graphics/Vertex/VertexUtils.h>
namespace DopeEngine
{
    DX12RenderPass::DX12RenderPass(const RenderPassDesc& desc, DX12GraphicsDevice* device) : RenderPass(desc)
    {
        create(desc, device);
    }
    DX12RenderPass::~DX12RenderPass()
    {

    }
    DXPTR<ID3D12RootSignature> DX12RenderPass::get_dx12_root_signature() const
    {
        return RootSignature;
    }
    DXPTR<ID3D12PipelineState> DX12RenderPass::get_dx12_pso() const
    {
        return Pso;
    }
    void DX12RenderPass::create(const RenderPassDesc& desc, DX12GraphicsDevice* device)
    {
        D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
        rootSignatureDesc.NumParameters = 0;
        rootSignatureDesc.NumStaticSamplers = 0;

        Array<D3D12_ROOT_PARAMETER> rootParameters;
        Array<D3D12_STATIC_SAMPLER_DESC> samplerDescs;
        for (unsigned int i = 0; i < desc.ResourceSlots.get_cursor();i++)
        {
            const GraphicsResourceSlotDesc resourceSlotDesc = desc.ResourceSlots[i];

            const GraphicsResourceType resourceType = resourceSlotDesc.Type;
            const ShaderStage shaderStage = resourceSlotDesc.ShaderStage;
            D3D12_ROOT_PARAMETER rootParameter = {};
            switch (resourceType)
            {
                case GraphicsResourceType::UniformBuffer:
                    break;
                case GraphicsResourceType::Texture:
                    break;
                case GraphicsResourceType::Undefined:
                    break;
                default:
                    break;
            }
            rootParameter.ParameterType = DX12ResourceLayoutUtils::get_dx12_root_parameter_type(resourceType);
            rootParameter.ShaderVisibility = DX12ShaderUtils::get_dx12_shader_visibility(shaderStage);
            rootParameter.Descriptor = {};
        }
        rootSignatureDesc.pParameters = rootParameters.get_data(); // TODO: implement parameters
        rootSignatureDesc.pStaticSamplers = samplerDescs.get_data(); // TODO: implement samplers

        ID3DBlob* signatureBlob;
        ID3DBlob* errorBlob;

        HRESULT rootSignatureSerializationHR = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
        ASSERT(SUCCEEDED(rootSignatureSerializationHR), "DX12RenderPass", "Root signature serialization failed with logs: %s", errorBlob->GetBufferPointer());


        HRESULT createRootSignatureHR = device->get_dx12_device()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(RootSignature.GetAddressOf()));
        ASSERT(SUCCEEDED(createRootSignatureHR), "DX12RenderPass", "Root signature creation failed!");

        const VertexLayoutDescription vertexLayoutDescription = desc.LayoutDescription;
        const Array<VertexElementDescription>& vertexElementDescs = vertexLayoutDescription.get_elements_fast();
        Array<D3D12_INPUT_ELEMENT_DESC> inputElements;
        unsigned int offset = 0;
        for (unsigned int i = 0; i < vertexElementDescs.get_cursor(); i++)
        {
            const VertexElementDescription& elementDesc = vertexElementDescs[i];

            D3D12_INPUT_ELEMENT_DESC inputElementDesc = { *elementDesc.Name, i, DX11VertexUtils::get_format(elementDesc.DataType), 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

            inputElements.add(inputElementDesc);

            offset += VertexUtils::get_data_type_size(elementDesc.DataType);
        }

        const Array<Shader*> shaderSetShaders = desc.ShaderSet;
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { };
        psoDesc.InputLayout.pInputElementDescs = inputElements.get_data();
        psoDesc.InputLayout.NumElements = inputElements.get_cursor();
        psoDesc.pRootSignature = RootSignature.Get();
        for (unsigned int i = 0; i < shaderSetShaders.get_cursor(); i++)
        {
            const Shader* shader = shaderSetShaders[i];
            const DX12Shader* dx12Shader = (const DX12Shader*)shader;

            const ShaderStage ShaderStage = shader->get_type();

            ID3DBlob* blob = dx12Shader->get_dx12_shader_blob();
            switch (ShaderStage)
            {
                case DopeEngine::ShaderStage::Vertex:
                    psoDesc.VS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.VS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderStage::Fragment:
                    psoDesc.PS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.PS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderStage::Geometry:
                    psoDesc.GS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.GS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderStage::TesellationEval:
                    break;
                case DopeEngine::ShaderStage::TesellationControl:
                    break;
                case DopeEngine::ShaderStage::Compute:
                    break;
                case DopeEngine::ShaderStage::Undefined:
                    break;
                default:
                    break;
            }
        }

        D3D12_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.AntialiasedLineEnable = false;
        rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        rasterizerDesc.DepthBias = 0;
        rasterizerDesc.DepthBiasClamp = 0;
        rasterizerDesc.DepthClipEnable = desc.DepthClip;
        rasterizerDesc.FillMode = DX12RenderPassUtils::get_dx12_fill_mode(desc.FillMode);
        rasterizerDesc.CullMode = DX12RenderPassUtils::get_dx12_cull_mode(desc.CullFace);
        rasterizerDesc.ForcedSampleCount = 0;
        rasterizerDesc.FrontCounterClockwise = desc.FrontFace == FrontFaceMode::CounterClockwise ? true : false;
        rasterizerDesc.MultisampleEnable = false;
        rasterizerDesc.SlopeScaledDepthBias = 0;
        psoDesc.RasterizerState = rasterizerDesc;

        Array<TextureFormat> targetFramebufferFormats;
        unsigned int framebufferWidth = 0;
        unsigned int framebufferHeight = 0;
        if (desc.TargetFramebuffer->is_swapchain_framebuffer())
        {
            const SwapchainFramebuffer* swapchainFramebuffer = (const SwapchainFramebuffer*)desc.TargetFramebuffer;
            targetFramebufferFormats.add(swapchainFramebuffer->get_swapchain_buffer_format());
            framebufferWidth = swapchainFramebuffer->get_width();
            framebufferHeight = swapchainFramebuffer->get_height();
        }

        D3D12_BLEND_DESC blendDesc = {}; // TODO: implement this
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        constexpr D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
        {
            FALSE,FALSE,
            D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
            D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
            D3D12_LOGIC_OP_NOOP,
            D3D12_COLOR_WRITE_ENABLE_ALL,
        };
        
        for (unsigned int i = 0; i < targetFramebufferFormats.get_cursor(); i++)
        {
            blendDesc.RenderTarget[i] = defaultRenderTargetBlendDesc;
        }

        psoDesc.BlendState = blendDesc;
        psoDesc.DepthStencilState.DepthEnable = false;
        psoDesc.DepthStencilState.StencilEnable = false;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = DX12RenderPassUtils::get_dx12_primitive_type(desc.Primitives);
        Array<DXGI_FORMAT> rtvFormats;
        for (unsigned int i = 0; i < targetFramebufferFormats.get_cursor(); i++)
        {
            rtvFormats.add(DX11TextureUtils::get_format(targetFramebufferFormats[i]));
        }
        for (unsigned int i = 0; i < rtvFormats.get_cursor(); i++)
        {
            psoDesc.RTVFormats[i] = rtvFormats[i];
        }
        psoDesc.NumRenderTargets = rtvFormats.get_cursor();
        psoDesc.SampleDesc.Count = 1;
  
        HRESULT createPSOHR = device->get_dx12_device()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&Pso));
        ASSERT(SUCCEEDED(createPSOHR), "DX12RenderPass", "PSO creation failed");
    }
}