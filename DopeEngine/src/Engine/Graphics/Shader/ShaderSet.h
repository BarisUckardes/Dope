#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>

namespace DopeEngine
{
	class Shader;

	/// <summary>
	/// Graphics api agnostic shader-set(program) abstraction class
	/// </summary>
	class DOPE_ENGINE_API ShaderSet : public DeviceObject
	{
	public:
		ShaderSet(const Array<Shader*>& shaders);
		virtual ~ShaderSet() = default;

		/// <summary>
		/// Returns a reference to the shader list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Shader*>& get_shaders_fast() const;

		/// <summary>
		/// Returns a copy of the shader list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Shader*> get_shaders_slow() const;

		/*/// <summary>
		/// Returns the vertex shader(if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Shader* get_vertex_shader() const;

		/// <summary>
		/// Returns the fragment shader(if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Shader* get_fragment_shader() const;*/
		virtual void create_set() = 0;
	private:
		Array<Shader*> Shaders;
		Shader* VertexShader;
		Shader* FragmentShader;
	};


}