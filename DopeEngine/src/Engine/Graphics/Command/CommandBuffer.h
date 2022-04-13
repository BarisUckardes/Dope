#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Graphics/Device/DeviceObject.h>
namespace DopeEngine
{
	class Buffer;
	class VertexBuffer;
	class IndexBuffer;
	class UniformBuffer;
	class Texture;
	class Framebuffer;
	class Pipeline;
	class Shader;
	class ShaderSet;
	class VertexLayout;
	class DeviceObject;
	struct ColorRgbaByte;

	/// <summary>
	/// Graphics api agnostic commandbuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API CommandBuffer : public DeviceObject
	{
	public:
		/// <summary>
		/// Locks the commandbuffer sumbit
		/// </summary>
		void lock();

		/// <summary>
		/// Unlocks the command submit
		/// </summary>
		void unlock();

		/// <summary>
		/// Sets the target vertex buffer
		/// </summary>
		/// <param name="vertexBuffer"></param>
		virtual void set_vertex_buffer(const VertexBuffer& vertexBuffer) = 0;

		/// <summary>
		/// Sets the target index buffer
		/// </summary>
		/// <param name="indexBuffer"></param>
		virtual void set_index_buffer(const IndexBuffer& indexBuffer) = 0;

		/// <summary>
		/// Sets a uniform buffer
		/// </summary>
		/// <param name="buffer"></param>
		virtual void set_uniform_buffer(const UniformBuffer& buffer) = 0;

		/// <summary>
		/// Sets the target framebuffer
		/// </summary>
		/// <param name="framebuffer"></param>
		virtual void set_framebuffer(const Framebuffer& framebuffer) = 0;

		/// <summary>
		/// Sets the target pipeline
		/// </summary>
		/// <param name="pipeline"></param>
		virtual void set_pipeline(const Pipeline& pipeline) = 0;

		/// <summary>
		/// Sets the target shader set
		/// </summary>
		/// <param name="shaderSet"></param>
		virtual void set_shader_set(const ShaderSet& shaderSet) = 0;

		/// <summary>
		/// Sets the target vertex layout
		/// </summary>
		/// <param name="layout"></param>
		virtual void set_vertex_layout(const VertexLayout& layout) = 0;

		/// <summary>
		/// Clears the color
		/// </summary>
		/// <param name="color"></param>
		virtual void clear_color(const ColorRgbaByte& color) = 0;

		/// <summary>
		/// Clears the depth
		/// </summary>
		/// <param name="depth"></param>
		virtual void clear_depth(const float depth) = 0;

		/// <summary>
		/// Draw call
		/// </summary>
		virtual void indexed_draw_call(const unsigned int count) = 0;


	protected:
		CommandBuffer() : CurrentBoundTextures(0) {}
		virtual ~CommandBuffer() = 0 {}

		virtual void lock_impl() = 0;
		virtual void unlock_impl() = 0;
	private:
		void clear_cached_state();
		unsigned int CurrentBoundTextures;
	};


}