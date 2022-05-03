#pragma once
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
#include <Engine/Core/Symbols.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKQueueFamilyProperties
	{
	public:
		VKQueueFamilyProperties(const VkQueueFlags flag,const unsigned int count,const unsigned int familyIndex) :
			Flag(flag),Count(count),FamilyIndex(familyIndex)
		{}
		VKQueueFamilyProperties() : Flag(0),Count(0),FamilyIndex(999) {}
		~VKQueueFamilyProperties() = default;

		FORCEINLINE VkQueueFlags get_flag() const;
		FORCEINLINE unsigned int get_count() const;
		FORCEINLINE unsigned int get_family_index() const;
	private:
		VkQueueFlags Flag;
		unsigned int Count;
		unsigned int FamilyIndex;
	};

	static bool operator==(const VKQueueFamilyProperties& a, const VKQueueFamilyProperties& b)
	{
		return a.get_flag() == b.get_flag();
	}
	static bool operator!=(const VKQueueFamilyProperties& a, const VKQueueFamilyProperties& b)
	{
		return a.get_flag() != b.get_flag();
	}
}