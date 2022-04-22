#include "DX12Pipeline.h"
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12Shader.h>
#include <Engine/Graphics/API/Directx12/Shader/DX12ShaderSet.h>
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
        HRESULT createRootSignatureHR = device->get_dx12_device()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&RootSignature));

        /*
        * Validate create root signature
        */
        ASSERT(SUCCEEDED(createRootSignatureHR), "DX12Pipeline", "Root signature creation failed!");

        /*
        * Create input signature
        */
        Array<D3D12_INPUT_ELEMENT_DESC> inputElements;

        /*
        * Create dx12 graphics pipeline state
        */
        const Array<Shader*> shaderSetShaders = desc.ShaderSet->get_shaders_fast();
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = { };
        psoDesc.InputLayout.pInputElementDescs = inputElements.get_data();
        psoDesc.InputLayout.NumElements = inputElements.get_cursor();
        psoDesc.pRootSignature = RootSignature;
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
        * TODO: Complete pipeline
        */
        psoDesc.RasterizerState = {};
        psoDesc.BlendState = {};
        psoDesc.DepthStencilState.DepthEnable = desc.DepthTest;
        psoDesc.DepthStencilState.StencilEnable = false;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;

        /*
        * Create pso object
        */
        HRESULT createPSOHR = device->get_dx12_device()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&PSO));

        /*
        * Validate pso
        */
        ASSERT(SUCCEEDED(createPSOHR), "DX12Pipeline", "PSO creation failed");
    }
}