#include "DX11TextureUtils.h"
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	D3D11_USAGE DX11TextureUtils::get_usage(const TextureUsage usage)
	{
		switch (usage)
		{
			case DopeEngine::TextureUsage::ReadOnly:
				return D3D11_USAGE_IMMUTABLE;
				break;
			case DopeEngine::TextureUsage::ReadWrite:
				return D3D11_USAGE_DEFAULT;
				break;
			case DopeEngine::TextureUsage::FramebufferAttachment:
				return D3D11_USAGE_DEFAULT;
				break;
			default:
				ASSERT(false, "DX11TextureUtils", "Invalid TextureUsage, cant create dx11 usage");
				break;
		}
	}
	unsigned int DX11TextureUtils::get_bind_flags(const TextureUsage usage)
	{
		switch (usage)
		{
		case DopeEngine::TextureUsage::ReadOnly:
			return D3D11_BIND_SHADER_RESOURCE;
			break;
		case DopeEngine::TextureUsage::ReadWrite:
			return D3D11_BIND_SHADER_RESOURCE;
			break;
		case DopeEngine::TextureUsage::FramebufferAttachment:
			return D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			break;
		default:
			ASSERT(false, "DX11TextureUtils", "Invalid TextureUsage, cant create dx11 bind flags");
			break;
		}
	}
	DXGI_FORMAT DX11TextureUtils::get_format(const TextureFormat format)
	{
		switch (format)
		{
			case DopeEngine::TextureFormat::Red:
				return DXGI_FORMAT_R8_UNORM;
				break;
			case DopeEngine::TextureFormat::RGB8f:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case DopeEngine::TextureFormat::RGB16f:
				return DXGI_FORMAT_R16G16B16A16_FLOAT;
				break;
			case DopeEngine::TextureFormat::RGB32f:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case DopeEngine::TextureFormat::RGBA8f:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case DopeEngine::TextureFormat::RGBA16f:
				return DXGI_FORMAT_R16G16B16A16_FLOAT;
				break;
			case DopeEngine::TextureFormat::RGBA32F:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			default:
				ASSERT(false, "DX11TextureUtils", "Invalid TextureFormat, cannot get DXGI_FORMAT");
				break;
		}
	}
}