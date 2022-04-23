#include "DX12Pipeline.h"
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12Shader.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12ShaderSet.h>
#include <Engine/Graphics/API/Directx12/Pipeline/DX12PipelineUtils.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
#include <Engine/Graphics/API/Directx11/Vertex/DX11VertexUtils.h>
#include <Engine/Graphics/Vertex/VertexUtils.h>
namespace DopeEngine
{
    DX12Pipeline::DX12Pipeline(const PipelineDescription& desc, DX12GraphicsDevice* device) : Pipeline(desc)
    {
        /*
        * Create pipeline
        */
        _create_pipeline(desc, device);
    }
    DX12Pipeline::~DX12Pipeline()
    {

    }
    DXPTR<ID3D12RootSignature> DX12Pipeline::get_dx12_root_signature() const
    {
        return RootSignature;
    }
    DXPTR<ID3D12PipelineState> DX12Pipeline::get_dx12_pso() const
    {
        return Pso;
    }
    D3D12_VIEWPORT DX12Pipeline::get_dx12_viewport() const
    {
        return D3D12_VIEWPORT();
    }
    D3D12_RECT DX12Pipeline::get_dx12_scissors() const
    {
        return D3D12_RECT();
    }
    void DX12Pipeline::_create_pipeline(const PipelineDescription& desc, DX12GraphicsDevice* device)
    {
        /*
        * Create root signature
        */
        D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
        rootSignatureDesc.NumParameters = 0;
        rootSignatureDesc.NumStaticSamplers = 0;
        rootSignatureDesc.pParameters = nullptr;
        rootSignatureDesc.pStaticSamplers = nullptr;

        /*
        * Serialize root signature
        */
        ID3DBlob* signatureBlob;
        ID3DBlob* errorBlob;
        HRESULT rootSignatureSerializationHR = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);

        /*
        * Validate root signature serialization
        */
        ASSERT(SUCCEEDED(rootSignatureSerializationHR), "DX12Pipeline", "Root signature serialization failed with logs: %s", errorBlob->GetBufferPointer());

        /*
        * Create root signature
        */
        HRESULT createRootSignatureHR = device->get_dx12_device()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(RootSignature.GetAddressOf()));

        /*
        * Validate create root signature
        */
        ASSERT(SUCCEEDED(createRootSignatureHR), "DX12Pipeline", "Root signature creation failed!");

        /*
        * Create input signature
        */
        const VertexLayoutDescription vertexLayoutDescription = desc.LayoutDescription;
        const Array<VertexElementDescription> vertexElementDescs = vertexLayoutDescription.get_elements_slow();
        Array<D3D12_INPUT_ELEMENT_DESC> inputElements;
        unsigned int offset = 0;
        for (unsigned int i = 0; i < vertexElementDescs.get_cursor(); i++)
        {
            /*
            * Get element description
            */
            const VertexElementDescription& elementDesc = vertexElementDescs[i];

            /*
             * Create input element desc
             */
            D3D12_INPUT_ELEMENT_DESC inputElementDesc = { *elementDesc.Name, i, DX11VertexUtils::get_format(elementDesc.DataType), 0, offset, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

            /*
            * Register input element
            */
            inputElements.add(inputElementDesc);

            /*
            * Increment offset
            */
            offset += VertexUtils::get_data_type_size(elementDesc.DataType);
        }

        /*
        * Create dx12 graphics pipeline state
        */
        const Array<Shader*> shaderSetShaders = desc.ShaderSet->get_shaders_fast();
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { };
        psoDesc.InputLayout.pInputElementDescs = inputElements.get_data();
        psoDesc.InputLayout.NumElements = inputElements.get_cursor();
        psoDesc.pRootSignature = RootSignature.Get();
        for (unsigned int i = 0; i < shaderSetShaders.get_cursor(); i++)
        {
            /*
            * Get shader
            */
            const Shader* shader = shaderSetShaders[i];
            const DX12Shader* dx12Shader = (const DX12Shader*)shader;

            /*
            * Get shader type
            */
            const ShaderType shaderType = shader->get_type();

            /*
            * Catch shader type
            */
            ID3DBlob* blob = dx12Shader->get_dx12_shader_blob();
            switch (shaderType)
            {
                case DopeEngine::ShaderType::Vertex:
                    psoDesc.VS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.VS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderType::Fragment:
                    psoDesc.PS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.PS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderType::Geometry:
                    psoDesc.GS.pShaderBytecode = (const void*)blob->GetBufferPointer();
                    psoDesc.GS.BytecodeLength = blob->GetBufferSize();
                    break;
                case DopeEngine::ShaderType::TesellationEval:
                    break;
                case DopeEngine::ShaderType::TesellationControl:
                    break;
                case DopeEngine::ShaderType::Compute:
                    break;
                case DopeEngine::ShaderType::Undefined:
                    break;
                default:
                    break;
            }
        }

        /*
        * Create rasterizer state
        */
        D3D12_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.AntialiasedLineEnable = false;
        rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        rasterizerDesc.CullMode = DX12PipelineUtils::get_dx12_cull_mode(desc.CullFace);
        rasterizerDesc.DepthBias = 0;
        rasterizerDesc.DepthBiasClamp = 0;
        rasterizerDesc.DepthClipEnable = desc.DepthClip;
        rasterizerDesc.FillMode = DX12PipelineUtils::get_dx12_fill_mode(desc.FillMode);
        rasterizerDesc.ForcedSampleCount = 0;
        rasterizerDesc.FrontCounterClockwise = desc.FrontFace == FrontFaceMode::CounterClockwise ? true : false;
        rasterizerDesc.MultisampleEnable = false;
        rasterizerDesc.SlopeScaledDepthBias = 0;
        psoDesc.RasterizerState = rasterizerDesc;

        /*
        * Create blend state
        */
        D3D12_BLEND_DESC blendDesc = {}; // TODO: implement this
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        psoDesc.BlendState = blendDesc;


        /*
        * Create depth stencil state
        */
        psoDesc.DepthStencilState.DepthEnable = desc.DepthTest;
        psoDesc.DepthStencilState.StencilEnable = false;
        psoDesc.SampleMask = UINT_MAX;

        /*
        * Create output state
        */
        psoDesc.PrimitiveTopologyType = DX12PipelineUtils::get_dx12_primitives(desc.Primitives);

        Array<DXGI_FORMAT> rtvFormats;
        for (unsigned int i = 0; i < desc.OutputDesc.OutputFormats.get_cursor(); i++)
        {
            rtvFormats.add(DX11TextureUtils::get_format(desc.OutputDesc.OutputFormats[i]));
        }
        for (unsigned int i = 0; i < rtvFormats.get_cursor(); i++)
        {
            psoDesc.RTVFormats[i] = rtvFormats[i];
        }

        psoDesc.NumRenderTargets = rtvFormats.get_cursor();
        psoDesc.SampleDesc.Count = 1;

        /*
        * Create pso object
        */
        HRESULT createPSOHR = device->get_dx12_device()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&Pso));

        /*
        * Validate pso
        */
        ASSERT(SUCCEEDED(createPSOHR), "DX12Pipeline", "PSO creation failed");

        /*
        * Create viewport
        */
        Viewport.Width = desc.OutputDesc.Width;
        Viewport.Height = desc.OutputDesc.Height;
        Viewport.TopLeftX = desc.OutputDesc.OffsetX;
        Viewport.TopLeftY = desc.OutputDesc.OffsetY;
        Viewport.MinDepth = 0.0f;
        Viewport.MaxDepth = 1.0f;

        /*
        * Create scissors
        */
        ScissorRect.left = 0;
        ScissorRect.right = 0;
        ScissorRect.bottom = 0;
        ScissorRect.top = 0;
    }
}