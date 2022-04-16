#include "OpenGLCommandBuffer.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
#include <Glad/glad.h>
#include <Engine/Graphics/API/OpenGL/Pipeline/OpenGLPipelineUtils.h>
#include <Engine/Graphics/API/OpenGL/Vertex/OpenGLVertexUtils.h>
#include <Engine/Graphics/Resource/ResourceTypeUtils.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/API/OpenGL/Texture/OpenGLTextureUtils.h>
namespace DopeEngine
{
	void OpenGLCommandBuffer::set_vertex_buffer_impl(const VertexBuffer& vertexBuffer)
	{
		CurrentVertexBufferHandle = ((const OpenGLVertexBuffer&)vertexBuffer).get_handle();
	}

	void OpenGLCommandBuffer::set_index_buffer_impl(const IndexBuffer& indexBuffer)
	{
		CurrentIndexBufferHandle = ((const OpenGLIndexBuffer&)indexBuffer).get_handle();
	}

	void OpenGLCommandBuffer::set_uniform_buffer_impl(const UniformBuffer& buffer)
	{
		/*
		* Get opengl unibuffer
		*/
		const OpenGLUniformBuffer& openglGLBuffer = (const OpenGLUniformBuffer&)buffer;

		/*
		* Get index
		*/
		const SHADER_UNIFORM_ID blockIndex = glGetUniformBlockIndex(openglGLBuffer.get_handle(), *openglGLBuffer.get_buffer_name());

		/*
		* Set buffer
		*/
		glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex,openglGLBuffer.get_handle());
	}

	void OpenGLCommandBuffer::set_framebuffer_impl(const Framebuffer& framebuffer)
	{
		/*
		* Check if its a swapchain
		*/
		if (framebuffer.is_swapchain_framebuffer())
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ((const OpenGLFramebuffer&)framebuffer).get_handle());
		}
	}

	void OpenGLCommandBuffer::set_pipeline_impl(const Pipeline& pipeline)
	{
		/*
		* Blending
		*/

		/*
		* Depth
		*/
		if (pipeline.is_depth_test_enabled())
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		if (pipeline.is_depth_write_enabled())
			glEnable(GL_DEPTH_WRITEMASK);
		else
			glDisable(GL_DEPTH_WRITEMASK);

		glDepthFunc(OpenGLPipelineUtils::get_depth_function(pipeline.get_depth_function()));

		/*
		* Face culling
		*/
		if (pipeline.get_cull_mode() != FaceCullMode::DontCull)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		glFrontFace(OpenGLPipelineUtils::get_front_face(pipeline.get_front_face()));
		glCullFace(OpenGLPipelineUtils::get_cull_mode(pipeline.get_cull_mode()));

		/*
		* Polygon fill mode
		*/
		glPolygonMode(OpenGLPipelineUtils::get_front_face(pipeline.get_front_face()), OpenGLPipelineUtils::get_fill_mode(pipeline.get_fill_mode()));

		/*
		* Set primitive
		*/
		CurrentPrimitive = OpenGLPipelineUtils::get_primitive(pipeline.get_primitives());

		/*
		* Set current program
		*/
		CurrentProgramHandle = ((const OpenGLShaderSet*)pipeline.get_shader_set())->get_handle();

		/*
		* Set vertex layout
		*/
		CurrentVertexLayoutHandle = ((const OpenGLPipeline*)&pipeline)->get_vertex_layout_handle();
		CurrentVertexLayoutDescription = pipeline.get_vertex_layout();

		/*
		* Set viewport
		*/
		const OutputDescription outputDesc = pipeline.get_output_desc();
		glViewport(outputDesc.OffsetX, outputDesc.OffsetY, outputDesc.Width, outputDesc.Height);

		/*
		* Start using current program
		*/
		glUseProgram(CurrentProgramHandle);

	}

	void OpenGLCommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		glClearColor(color.Red, color.Green, color.Blue, color.Alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLCommandBuffer::clear_depth_impl(const float depth)
	{
		glClearDepth(depth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLCommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		/*
		* Bind vertex array
		*/
		glBindVertexArray(CurrentVertexLayoutHandle);

		/*
		* Bind given vertex and index buffers
		*/
		glBindBuffer(GL_ARRAY_BUFFER, CurrentVertexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CurrentIndexBufferHandle);

		/*
		* Set current layout state
		*/
		const VertexLayoutDescription layoutDescription = CurrentVertexLayoutDescription;
		const Array<VertexElementDescription>& elementDescriptions = layoutDescription.get_elements_fast();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elementDescriptions.get_cursor(); i++)
		{
			/*
			* Get element description
			*/
			const VertexElementDescription& elementDescription = elementDescriptions[i];

			/*
			* Catch data type
			*/
			const VertexElementDataType dataType = elementDescription.DataType;
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, elementDescription.ComponentCount, OpenGLVertexUtils::get_data_type(dataType), elementDescription.Normalized ? GL_TRUE : GL_FALSE, layoutDescription.get_stride(), (const void*)offset);

			/*
			* Increment offset
			*/
			offset += elementDescription.ComponentCount * elementDescription.ElementSizeInBytes;
		}

		/*
		* Issue draw call
		*/
		glDrawElements(CurrentPrimitive, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLCommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{
		/*
		* Get as opengl resource view
		*/
		const OpenGLResourceView* glView = (const OpenGLResourceView*)view;

		/*
		* Set resource
		*/
		const Array<DeviceObject*> resources = view->get_resources_fast();
		const Array<ResourceLayout*>& resourceLayouts = get_bound_pipeline()->get_resource_layouts_fast();
		const ResourceLayout* targetLayout = resourceLayouts[slot];
		const ResourceLayoutDescription targetDescription = targetLayout->get_description();
		for (unsigned int i = 0; i < resources.get_cursor(); i++)
		{
			/*
			* Get device object
			*/
			const DeviceObject* deviceObject = resources[i];
			const DeviceObjectType resourceDeviceObjectType = deviceObject->get_device_object_type();
			const ResourceLayoutElementDescription elementDescription = targetDescription.Elements[i];
			ResourceType resourceType = elementDescription.Type;


			switch (resourceType)
			{
				case DopeEngine::ResourceType::Texture:
				{
					/*
					* Get gl texture
					*/
					const OpenGLTexture* glTexture = ((const OpenGLTexture*)deviceObject);

					/*
					* Get texture location
					*/
					const unsigned int uniformLocation = glGetUniformLocation(CurrentProgramHandle, *targetDescription.Elements[i].Name);

					/*
					* Active and bind texture
					*/
					glActiveTexture(GL_TEXTURE0 + get_bound_texture_count());
					glBindTexture(OpenGLTextureUtils::get_texture_type(glTexture->get_type()), glTexture->get_handle());

					/*
					* Set texture uniform
					*/
					glUniform1i(uniformLocation, get_bound_texture_count());
					break;
				}
				case DopeEngine::ResourceType::UniformBuffer:
				{
					/*
					* Get uniform buffer handle
					*/
					const UNIFORM_BUFFER_HANDLE handle = ((OpenGLUniformBuffer*)deviceObject)->get_handle();

					/*
					* Get uniform buffer program uniform location
					*/
					const UNIFORM_BUFFER_INDEX index = glGetUniformBlockIndex(CurrentProgramHandle, *targetDescription.Elements[i].Name);

					/*
					* Bind uniform block location to binding location
					*/
					glUniformBlockBinding(CurrentProgramHandle, index, get_bound_uniformbuffer_count());

					/*
					* Set buffer
					*/
					glBindBufferBase(GL_UNIFORM_BUFFER, index, handle);

					/*
					* Increment global state
					*/
					increment_uniformbuffer_bound_count();
					break;
				}
				default:
					break;
			}
			
		}
	}

	void OpenGLCommandBuffer::lock_impl()
	{

	}

	void OpenGLCommandBuffer::unlock_impl()
	{

	}
	void OpenGLCommandBuffer::clear_cached_state_impl()
	{
		CurrentPrimitive = GL_NONE;
		CurrentProgramHandle = GL_NONE;
		CurrentVertexLayoutHandle = GL_NONE;
		CurrentVertexBufferHandle = GL_NONE;
		CurrentIndexBufferHandle = GL_NONE;
	}
}