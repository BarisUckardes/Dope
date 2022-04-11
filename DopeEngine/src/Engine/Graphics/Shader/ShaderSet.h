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

		virtual void create_set() = 0;
	private:
		Array<Shader*> Shaders;
	};


}