#include "ShaderSet.h"

namespace DopeEngine
{
    ShaderSet::ShaderSet(const Array<Shader*>& shaders)
    {
        /*
        * Initialize
        */
        Shaders = shaders;
    }
    const Array<Shader*>& ShaderSet::get_shaders_fast() const
    {
        return Shaders;
    }
    Array<Shader*> ShaderSet::get_shaders_slow() const
    {
        return Shaders;
    }
}