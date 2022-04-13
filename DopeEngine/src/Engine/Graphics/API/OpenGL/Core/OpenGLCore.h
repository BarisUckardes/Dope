#pragma once

class OpenGLGraphicsDevice;
typedef unsigned int SHADER_HANDLE;
typedef unsigned int SHADER_TYPE;
typedef unsigned int PROGRAM_HANDLE;
typedef unsigned int TEXTURE_HANDLE;
typedef unsigned int TEXTURE_FORMAT;
typedef unsigned int TEXTURE_INTERNAL_FORMAT;
typedef unsigned int TEXTURE_DATA_TYPE;
typedef unsigned int FRAMEBUFFER_HANDLE;
typedef unsigned int FRAMEBUFFER_ATTACHMENT;
typedef unsigned int VERTEX_BUFFER_HANDLE;
typedef unsigned int INDEX_BUFFER_HANDLE;
typedef unsigned int UNIFORM_BUFFER_HANDLE;
typedef unsigned int VERTEX_LAYOUT_HANDLE;
typedef unsigned int VERTEX_DATA_TYPE;
typedef unsigned int DEPTH_FUNCTION;
typedef unsigned int SHADER_UNIFORM_ID;
typedef unsigned int FRONT_FACE;
typedef unsigned int CULL_MODE;
typedef unsigned int FILL_MODE;
typedef unsigned int PRIMITIVE;
typedef OpenGLGraphicsDevice* DEVICE;

void _CheckGLError(const char* file, int line);

#define CheckGLError() _CheckGLError(__FILE__, __LINE__)

