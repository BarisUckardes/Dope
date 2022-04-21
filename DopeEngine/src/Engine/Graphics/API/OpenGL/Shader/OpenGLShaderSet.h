#pragma once
#include <Engine/Graphics/Shader/ShaderSet.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class Shader;

	/// <summary>
	/// OpenGL implementation of a shader set
	/// </summary>
	class DOPE_ENGINE_API OpenGLShaderSet final : public ShaderSet
	{
	public:
		OpenGLShaderSet(const Array<Shader*>& shaders,DEVICE device);
		virtual ~OpenGLShaderSet() final override;

		/// <summary>
		/// Returns the handle of the shader set as OpenGL shader program
		/// </summary>
		/// <returns></returns>
		 PROGRAM_HANDLE get_handle() const;

		virtual void create_set() final override;

	private:
		void invalidate();
	private:
		PROGRAM_HANDLE Handle;
		DEVICE Device;
	};
}