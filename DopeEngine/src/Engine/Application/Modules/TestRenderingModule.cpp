#include "TestRenderingModule.h"
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/Shader/ShaderDescription.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/Buffer/IndexBuffer.h>
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Glad/glad.h>
#include <stdexcept>
#include <Engine/Math/Vector3f.h>
#include <Engine/Utils/TextureLoader/TextureLoader.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Resource/ResourceViewDescription.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	VertexBuffer* vBuffer = nullptr;
	IndexBuffer* iBuffer = nullptr;
	Shader* vShader = nullptr;
	Shader* fShader = nullptr;
	ShaderSet* shaderSet = nullptr;
	RenderPass* renderPass = nullptr;
	Buffer* colorBuffer = nullptr;
	ResourceView* colorResourceView = nullptr;
	Texture* texture = nullptr;
	ResourceView* textureView = nullptr;
	CommandBuffer* cmdBuffer = nullptr;
	/*const String vs =
		"#version 450 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"layout(location = 1) in vec2 aUv;"
		"out vec2 fUv;"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPosition, 0.0, 1.0);\n"
		"fUv = aUv;"
		"}\n";

	const String fs =
		"#version 450 core\n"
		"out vec4 FragColor;\n"
		"in vec2 fUv;"
		"uniform sampler2D MyTexture;"
		"layout(std140) uniform MyColor"
		"{"
		 "vec3 color;"
		"};"
		"layout(std140) uniform MyColor2"
		"{"
		"vec3 color2;"
		"};"
		"void main()\n"
		"{\n"
		"FragColor = texture(MyTexture,fUv);\n"
		"}\n";*/

	const String vs = R"(

	float4 main(float2 pos : POSITION) : SV_POSITION
	{
		return float4(pos.x,pos.y,0.2f,1.0f);
	}

)";

	const String fs = R"(

	Texture2D MyTexture;
	cbuffer VS_CONSTANT_BUFFER : register(b0)
	{
		float3 Color;
	};

	float4 main() : SV_TARGET
	{
		return float4(1.0f,0,0,1.0f);
	}
)";

	void TestRenderingModule::initialize()
	{
		
		/*
		* Get graphics device
		*/
		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();
		GraphicsDeviceProperties props = device->get_properties();
		LOG("TestRenderingModule", "Vendor: %s, Model: %s", *props.get_vendor(), *props.get_model());

		/*
		* Create vertex buffer
		*/
		Array<Vector2f> vertexes;
		vertexes.add(Vector2f(0.0f,0.0f));
		vertexes.add(Vector2f(0.0f, 0.0f));
		vertexes.add(Vector2f(1.0f, 0));
		vertexes.add(Vector2f(1.0f, 0.0f));
		vertexes.add(Vector2f(0.5f, 1.0f));
		vertexes.add(Vector2f(0.5f, 1.0f));
		vBuffer = (VertexBuffer*)device->create_buffer(BufferDescription("VBuffer", BufferType::VertexBuffer, vertexes.get_cursor() * sizeof(Vector2f),sizeof(Vector2f)));
		vBuffer->set_debug_name("My vertex buffer");
		device->update_buffer(vBuffer, (const Byte*)vertexes.get_data());

		/*
		* Create index buffer
		*/
		Array<int> indexes;
		indexes.add(0);
		indexes.add(2);
		indexes.add(1);
		iBuffer = (IndexBuffer*)device->create_buffer(BufferDescription("MyColor", BufferType::IndexBuffer, indexes.get_cursor() * sizeof(int),sizeof(int)));
		iBuffer->set_debug_name("My index buffer");
		device->update_buffer(iBuffer, (const Byte*)indexes.get_data());

		/*
		* Create vertex layout
		*/
		Array<VertexElementDescription> elements;
		elements.add(VertexElementDescription("POSITION", VertexElementDataType::Float2, false));
		elements.add(VertexElementDescription("UV", VertexElementDataType::Float2, false));
		VertexLayoutDescription vertexLayoutDescription = VertexLayoutDescription(elements);

		/*
		* Create shaders
		*/
		vShader = device->create_shader(ShaderDescription(ShaderType::Vertex,vs));
		fShader = device->create_shader(ShaderDescription(ShaderType::Fragment, fs));


		/*
		* Create color buffer
		*/
		/*colorBuffer = device->create_buffer(BufferDescription("MyColor", BufferType::UniformBuffer, sizeof(Vector3f), 4));
		const Vector3f color{ 1.0f,0.3f,0.80f };
		device->update_buffer(colorBuffer, (const Byte*)&color);*/

		/*
		* Create texture
		*/
		/*TextureLoadResult textureLoadResult = TextureLoader::load_texture_from_path("C:\\Users\\PC\\Desktop\\skybox\\smiley.png");
		ASSERT(textureLoadResult.Data != nullptr, "TestRenderingModule", "Texture failed to load from path, error message: %s", *textureLoadResult.FailureMessage);
		texture = device->create_texture(
			TextureDescription
			{
				textureLoadResult.Width, textureLoadResult.Height,0,0,TextureUsage::ReadOnly,TextureFormat::RGBA8f,TextureType::Texture2D,textureLoadResult.Data
			});
		device->update_texture(texture, textureLoadResult.Data);*/

		/*
		* Create color buffer resource layouts
		*/
		/*ResourceDescription colorResourceLayoutDesc{ "MyColor",ResourceType::UniformBuffer,ShaderType::Fragment };
		ResourceViewDescription colorResourceViewDesc{ colorBuffer };
		ResourceLayout* colorBufferLayout = device->create_resource_layout(ResourceDescription("MyColor", ResourceType::UniformBuffer, ShaderType::Fragment));
		colorResourceView = device->create_resource_view(ResourceViewDescription(colorBuffer));*/

		/*
		* Create texture resource slot and view
		*/
	/*	ResourceSlotDesc textureResourceSlotDesc("MyTexture", ResourceType::Texture, ShaderType::Fragment);
		textureView = device->create_resource_view(ResourceViewDescription((DeviceObject*)texture));*/

		/*
		* Create pipeline
		*/
		RenderPassDesc renderPassDesc;
		renderPassDesc.BlendingState = BlendState::SingleOverride;
		renderPassDesc.CullFace = FaceCullMode::Back;
		renderPassDesc.DepthClip = false;
		renderPassDesc.DepthComparision = DepthComparisionKind::Always;
		renderPassDesc.DepthTest = false;
		renderPassDesc.DepthWrite = false;
		renderPassDesc.FillMode = PolygonFillMode::Fill;
		renderPassDesc.FrontFace = FrontFaceMode::CounterClockwise;
		renderPassDesc.LayoutDescription = vertexLayoutDescription;
		renderPassDesc.Primitives = PrimitiveTopology::Triangles;
		renderPassDesc.ScissorTest = false;

		ViewportDesc viewportDesc = {};
		viewportDesc.OffsetX = 0;
		viewportDesc.OffsetY = 0;
		viewportDesc.Width = device->get_swapchain_framebuffer()->get_width();
		viewportDesc.Height = device->get_swapchain_framebuffer()->get_height();
		viewportDesc.MinDepth = 0.0f;
		viewportDesc.MaxDepth = 1.0f;
		renderPassDesc.ViewportDesc = viewportDesc;

		ScissorsDesc scissorsDesc = {};
		scissorsDesc.OffsetX = 0;
		scissorsDesc.OffsetY = 0;
		scissorsDesc.Width = device->get_swapchain_framebuffer()->get_width();
		scissorsDesc.Height = device->get_swapchain_framebuffer()->get_height();
		renderPassDesc.ScissorsDesc = scissorsDesc;
		
		renderPassDesc.ShaderSet = { vShader,fShader };
		renderPassDesc.ResourceSlots = {};
		renderPassDesc.TargetFramebuffer = device->get_swapchain_framebuffer();
		renderPass = device->create_render_pass(renderPassDesc);

		/*
		* Create cmd buffer
		*/
		cmdBuffer = device->create_command_buffer();
	}

	void TestRenderingModule::update()
	{
		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();
		cmdBuffer->lock();
		cmdBuffer->start_render_pass(renderPass);
		cmdBuffer->clear_color({ 0u,0u,1u,1u });
		//cmdBuffer->set_vertex_buffer(vBuffer);
		//cmdBuffer->set_index_buffer(iBuffer);
		//buffer->set_resource_view(0, colorResourceView);
		//buffer->set_resource_view(0, textureView);
		//buffer->indexed_draw_call(3);
		cmdBuffer->unlock();
		device->submit_command_buffer(cmdBuffer);
		device->swap_swapchain_buffers(device->get_swapchain_framebuffer());
		device->wait_for_finish();
		//device->delete_device_object(cmdBuffer);
	}
	void TestRenderingModule::finalize()
	{

	}
	void TestRenderingModule::on_receive_application_event(ApplicationEvent* event)
	{

	}
}