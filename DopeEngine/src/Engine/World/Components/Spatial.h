#pragma once
#include <Engine/World/Component.h>
#include <Engine/Math/Vector3f.h>

namespace DopeEngine
{
	/// <summary>
	/// A component which holds the spatial data for the entity
	/// </summary>
	class DOPE_ENGINE_API Spatial : public Component
	{
		GENERATE_COMPONENT(Spatial);
	public:
		Spatial() : Position(),Rotation(),Scale() {}
		~Spatial() = default;

		/// <summary>
		/// Returns the position
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_position() const;

		/// <summary>
		/// Returns the rotation
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_rotation() const;

		/// <summary>
		/// Returns the scale
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3f get_scale() const;

		/// <summary>
		/// Sets the position
		/// </summary>
		/// <param name="position"></param>
		FORCEINLINE void set_position(const Vector3f& position);

		/// <summary>
		/// Sets the rotation
		/// </summary>
		/// <param name="rotation"></param>
		FORCEINLINE void set_rotation(const Vector3f& rotation);

		/// <summary>
		/// Sets the scale
		/// </summary>
		/// <param name="scale"></param>
		FORCEINLINE void set_scale(const Vector3f& scale);

		// Inherited via Component
		virtual bool should_tick() const override final; 
		virtual void initialize() override final;
		virtual void update() override final;
		virtual void finalize() override final;
	private:
		Vector3f Position;
		Vector3f Rotation;
		Vector3f Scale;

		
	};


}