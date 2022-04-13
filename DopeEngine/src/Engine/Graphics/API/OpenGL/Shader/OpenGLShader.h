#pragma once
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	class OpenGLGraphicsDevice;
	class DOPE_ENGINE_API OpenGLShader final : public Shader
	{
	public:
		OpenGLShader(const ShaderDescription& description,DEVICE device);
		virtual ~OpenGLShader() override;

		/// <summary>
		/// Returns the handle of this OpenGL shader
		/// </summary>
		/// <returns></returns>
		SHADER_HANDLE get_handle() const;

		// Inherited via Shader
		virtual void compile() final override;

	private:
		void invalidate();
	private:
		SHADER_HANDLE Handle;
		DEVICE Device;
	};


}