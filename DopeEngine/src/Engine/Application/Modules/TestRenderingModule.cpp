#include "TestRenderingModule.h"
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Graphics/Buffer/VertexBuffer.h>
#include <Engine/Graphics/Buffer/IndexBuffer.h>
#include <Glad/glad.h>
#include <stdexcept>
#include <Engine/Math/Vector3f.h>
namespace DopeEngine
{
	VertexBuffer* vBuffer = nullptr;
	IndexBuffer* iBuffer = nullptr;
	Shader* vShader = nullptr;
	Shader* fShader = nullptr;
	ShaderSet* shaderSet = nullptr;
	Pipeline* pipeline = nullptr;
	Buffer* colorBuffer = nullptr;
	ResourceView* resourceView = nullptr;
	/*const String vs =
		"#version 450 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPosition, 0.0, 1.0);\n"
		"}\n";

	const String fs =
		"#version 450 core\n"
		"out vec4 FragColor;\n"
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
		"FragColor = vec4(color,1.0f);\n"
		"}\n";*/

	const String vs = R""""(

	float4 main(float2 pos : POSITION) : SV_POSITION
	{
		return float4(pos.x,pos.y,0.2f,1.0f);
	}
)"""";

	const String fs = R""""(
	float4 main() : SV_TARGET
	{
		return float4(1.0f,1.0f,1.0f,1.0f);
	}
)"""";
	
	void TestRenderingModule::initialize()
	{
		/*
		* Get graphics device
		*/
		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();

		/*
		* Create vertex buffer
		*/
		Array<Vector2f> vertexes;
		vertexes.add(Vector2f(0.0f,0.5f));
		vertexes.add(Vector2f(0.5f, -0.5f));
		vertexes.add(Vector2f(-0.5f, -0.5f));
		vBuffer = (VertexBuffer*)device->create_buffer(BufferDescription(BufferType::VertexBuffer, "VBuffer", vertexes.get_cursor() * sizeof(Vector2f),sizeof(Vector2f)));
		vBuffer->set_debug_name("My vertex buffer");
		device->update_buffer(vBuffer, (const Byte*)vertexes.get_data());

		/*
		* Create index buffer
		*/
		Array<int> indexes;
		indexes.add(0);
		indexes.add(1);
		indexes.add(2);
		indexes.add(0);
		indexes.add(2);
		indexes.add(1);
		iBuffer = (IndexBuffer*)device->create_buffer(BufferDescription(BufferType::IndexBuffer, "MyColor", indexes.get_cursor() * sizeof(int),sizeof(int)));
		iBuffer->set_debug_name("My index buffer");
		device->update_buffer(iBuffer, (const Byte*)indexes.get_data());

		/*
		* Create vertex layout
		*/
		Array<VertexElementDescription> elements;
		elements.add(VertexElementDescription("POSITION", 2, sizeof(float), false, VertexElementDataType::Float));
		VertexLayoutDescription vertexLayoutDescription = VertexLayoutDescription(elements);

		/*
		* Create shaders
		*/
		vShader = device->create_shader(ShaderDescription(ShaderType::Vertex,vs));
		fShader = device->create_shader(ShaderDescription(ShaderType::Fragment, fs));

		/*
		* Create shader set
		*/
		shaderSet = device->create_shader_set({vShader,fShader});

		/*
		* Create resource layouts
		*/
		ResourceLayoutDescription colorResourceLayoutDesc(
			{
			ResourceLayoutElementDescription("MyColor",ResourceType::UniformBuffer,ShaderType::Fragment),
			ResourceLayoutElementDescription("MyColor2",ResourceType::UniformBuffer,ShaderType::Fragment)
			});

		/*
		* Create pipeline
		*/
		PipelineDescription pipelineDescription;
		pipelineDescription.BlendingState = BlendState::SingleOverride;
		pipelineDescription.CullFace = FaceCullMode::DontCull;
		pipelineDescription.DepthClip = false;
		pipelineDescription.DepthComparision = DepthComparisionKind::Always;
		pipelineDescription.DepthTest = false;
		pipelineDescription.DepthWrite = false;
		pipelineDescription.FillMode = PolygonFillMode::Fill;
		pipelineDescription.FrontFace = FrontFaceMode::CounterClockwise;
		pipelineDescription.LayoutDescription = vertexLayoutDescription;
		pipelineDescription.Primitives = PrimitiveTopology::Triangles;
		pipelineDescription.ScissorTest = false;
		pipelineDescription.ShaderSet = shaderSet;
		pipelineDescription.ResourceLayouts = { 0 };
		pipelineDescription.OutputDesc = device->get_swapchain_framebuffer()->get_output_desc();
		pipeline = device->create_pipeline(pipelineDescription);
	}

	void TestRenderingModule::update()
	{
		//LOG("Render", "Vertex Array: %d, Vertex Buffer: %d, Index Buffer: %d,Program: %d,Draw elements count: %d", varr, vb, ib, prg, 6);

		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();
		CommandBuffer* buffer = device->create_command_buffer();
		buffer->lock();
		buffer->set_pipeline(*pipeline);
		buffer->set_framebuffer(*device->get_swapchain_framebuffer());
		buffer->clear_color({ 0u,0u,1u,1u });

		buffer->set_vertex_buffer(*vBuffer);
		buffer->set_index_buffer(*iBuffer);
		//buffer->set_resource_view(0, resourceView);
		buffer->indexed_draw_call(6);
		buffer->unlock();
		device->delete_device_object(buffer);
	}
	void TestRenderingModule::finalize()
	{

	}
	void TestRenderingModule::on_receive_application_event(ApplicationEvent* event)
	{

	}
}