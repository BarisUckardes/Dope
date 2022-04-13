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
#include <Engine/Graphics/Vertex/VertexLayout.h>
#include <Glad/glad.h>
namespace DopeEngine
{
	VertexBuffer* vBuffer = nullptr;
	IndexBuffer* iBuffer = nullptr;
	VertexLayout* layout = nullptr;
	Shader* vShader = nullptr;
	Shader* fShader = nullptr;
	ShaderSet* shaderSet = nullptr;

	const String vs =
		"#version 450 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPosition.x, aPosition.y, 0.0, 1.0);\n"
		"}\n";

	const String fs =
		"#version 450 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(0.0f,1.0f,0.0f,0.0f);\n"
		"}\n";
	

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
		vertexes.add(Vector2f(1.0f,-1.0f));
		vertexes.add(Vector2f(-1.0f, -1.0f));
		vertexes.add(Vector2f(0, 1.0f));
		vBuffer = (VertexBuffer*)device->create_buffer(BufferDescription(BufferType::VertexBuffer, "VBuffer", vertexes.get_cursor() * sizeof(Vector2f)));
		vBuffer->update((Byte*)vertexes.get_data());

		/*
		* Create index buffer
		*/
		Array<int> indexes;
		indexes.add(0);
		indexes.add(1);
		indexes.add(2);
		iBuffer = (IndexBuffer*)device->create_buffer(BufferDescription(BufferType::IndexBuffer, "IBuffer", vertexes.get_cursor() * sizeof(int)));
		iBuffer->update((Byte*)indexes.get_data());

		/*
		* Create vertex layout
		*/
		Array<VertexElementDescription> elements;
		elements.add(VertexElementDescription("aPosition", 2, sizeof(float), false, VertexElementDataType::Float));
		VertexLayoutDescription vertexLayoutDescription = VertexLayoutDescription(elements);
		layout = device->create_vertex_layout(vertexLayoutDescription);

		/*
		* Create shaders
		*/
		vShader = device->create_shader(ShaderDescription(ShaderType::Vertex,vs));
		fShader = device->create_shader(ShaderDescription(ShaderType::Fragment, fs));

		shaderSet = device->create_shader_set({vShader,fShader});
	}
	void TestRenderingModule::update()
	{
		GraphicsDevice* device = get_owner_session()->get_window()->get_graphics_device();
		CommandBuffer* buffer = device->create_command_buffer();
		buffer->lock();
		buffer->clear_color({ 1u,0u,0u,1u });
		buffer->set_vertex_layout(*layout);
		buffer->set_vertex_buffer(*vBuffer);
		buffer->set_index_buffer(*iBuffer);
		buffer->set_shader_set(*shaderSet);

		buffer->indexed_draw_call(3);
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