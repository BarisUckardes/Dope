#include "Spatial.h"

namespace DopeEngine
{
	Vector3f Spatial::get_position() const
	{
		return Position;
	}
	Vector3f Spatial::get_rotation() const
	{
		return Rotation;
	}
	Vector3f Spatial::get_scale() const
	{
		return Scale;
	}
	void Spatial::set_position(const Vector3f& position)
	{
		Position = position;
	}
	void Spatial::set_rotation(const Vector3f& rotation)
	{
		Rotation = rotation;
	}
	void Spatial::set_scale(const Vector3f& scale)
	{
		Scale = scale;
	}
	bool Spatial::should_tick() const
	{
		return false;
	}
	void Spatial::initialize()
	{

	}
	void Spatial::update()
	{

	}
	void Spatial::finalize()
	{

	}
}