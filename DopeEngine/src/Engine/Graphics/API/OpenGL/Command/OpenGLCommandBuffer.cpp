#include "OpenGLCommandBuffer.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
#include <Glad/glad.h>
#include <Engine/Graphics/API/OpenGL/RenderPass/OpenGLRenderPassUtils.h>
#include <Engine/Graphics/API/OpenGL/Vertex/OpenGLVertexUtils.h>
#include <Engine/Graphics/Resource/GraphicsResourceTypeUtils.h>
#include <Engine/Graphics/Resource/GraphicsResource.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/API/OpenGL/Texture/OpenGLTextureUtils.h>
#include <Engine/Graphics/Vertex/VertexUtils.h>
namespace DopeEngine
{
	void OpenGLCommandBuffer::set_vertex_buffer_impl(const VertexBuffer* vertexBuffer)
	{
		CurrentVertexBufferHandle = ((const OpenGLVertexBuffer*)vertexBuffer)->get_handle();
	}

	void OpenGLCommandBuffer::set_index_buffer_impl(const IndexBuffer* indexBuffer)
	{
		CurrentIndexBufferHandle = ((const OpenGLIndexBuffer*)indexBuffer)->get_handle();
	}

	void OpenGLCommandBuffer::set_uniform_buffer_impl(const UniformBuffer* buffer)
	{
		const OpenGLUniformBuffer* openglGLBuffer = (const OpenGLUniformBuffer*)buffer;

		const SHADER_UNIFORM_ID blockIndex = glGetUniformBlockIndex(openglGLBuffer->get_handle(), *openglGLBuffer->get_buffer_name());
		glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex,openglGLBuffer->get_handle());
	}

	

	void OpenGLCommandBuffer::set_render_pass_impl(const RenderPass* renderPass)
	{
		const OpenGLRenderPass* glRenderPass = (const OpenGLRenderPass*)renderPass;

		/*
		* Blending----
		*/

		if (renderPass->is_depth_test_enabled())
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		if (renderPass->is_depth_write_enabled())
			glEnable(GL_DEPTH_WRITEMASK);
		else
			glDisable(GL_DEPTH_WRITEMASK);

		glDepthFunc(OpenGLRenderPassUtils::get_depth_function(renderPass->get_depth_function()));

		if (renderPass->get_cull_mode() != FaceCullMode::DontCull)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(OpenGLRenderPassUtils::get_cull_mode(renderPass->get_cull_mode()));
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		glFrontFace(OpenGLRenderPassUtils::get_front_face(renderPass->get_front_face()));

		/*
		* Polygon fill mode
		*/
		//glPolygonMode(OpenGLPipelineUtils::get_front_face(pipeline.get_front_face()), OpenGLPipelineUtils::get_fill_mode(pipeline.get_fill_mode()));

		CurrentPrimitive = OpenGLRenderPassUtils::get_primitive(glRenderPass->get_primitives());

		CurrentProgramHandle = glRenderPass->get_program_handle();

		CurrentVertexLayoutHandle = glRenderPass->get_vertex_layout_handle();
		CurrentVertexLayoutDescription = glRenderPass->get_vertex_layout();

		glUseProgram(CurrentProgramHandle);

		const Framebuffer* targetFramebuffer = glRenderPass->get_target_framebuffer();
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ((const OpenGLFramebuffer*)targetFramebuffer)->get_handle());
		}
	}

	void OpenGLCommandBuffer::set_viewport_desc_impl(const ViewportDesc& desc)
	{
		glViewport(desc.OffsetX, desc.OffsetY, desc.Width, desc.Height);
	}

	void OpenGLCommandBuffer::set_scissors_desc_impl(const ScissorsDesc& desc)
	{

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
			glVertexAttribPointer(i, OpenGLVertexUtils::get_component_count(dataType), OpenGLVertexUtils::get_data_type(dataType), elementDescription.Normalized ? GL_TRUE : GL_FALSE, layoutDescription.get_stride(), (const void*)offset);

			/*
			* Increment offset
			*/
			offset += VertexUtils::get_data_type_size(dataType);
;		}

		/*
		* Issue draw call
		*/
		glDrawElements(CurrentPrimitive, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLCommandBuffer::commit_resource_impl(const unsigned int slot, const GraphicsResource* resource)
	{
		/*
		* Get as opengl resource view
		*/
		const OpenGLResourceView* glView = (const OpenGLResourceView*)resource->get_resource();

		/*
		* Set resource
		*/
		const GraphicsDeviceObject* targetResource = resource->get_resource();
		const Array<GraphicsResourceSlotDesc> resourceSlotDescs = get_bound_render_pass()->get_resource_slots();
		const GraphicsResourceSlotDesc targetResourceSlotDesc = resourceSlotDescs[slot];

		/*
		* Get device object
		*/
		const GraphicsDeviceObjectType resourceDeviceObjectType = targetResource->get_device_object_type();
		GraphicsResourceType resourceType = targetResourceSlotDesc.Type;


		switch (resourceType)
		{
			case GraphicsResourceType::Texture:
			{
				/*
				* Get gl texture
				*/
				const OpenGLTexture* glTexture = ((const OpenGLTexture*)targetResource);

				/*
				* Get texture location
				*/
				const unsigned int uniformLocation = glGetUniformLocation(CurrentProgramHandle, *targetResourceSlotDesc.Name);

				/*
				* Active and bind texture
				*/
				glActiveTexture(GL_TEXTURE0 + get_bound_texture_count());
				glBindTexture(OpenGLTextureUtils::get_texture_type(glTexture->get_type()), glTexture->get_handle());

				/*
				* Set texture uniform
				*/
				glUniform1i(uniformLocation, get_bound_texture_count());

				/*
				* Increment currently bound textures
				*/
				increment_texture_bound_count();
				
				break;
			}
			case GraphicsResourceType::UniformBuffer:
			{
				/*
				* Get uniform buffer handle
				*/
				const UNIFORM_BUFFER_HANDLE handle = ((OpenGLUniformBuffer*)targetResource)->get_handle();

				/*
				* Get uniform buffer program uniform location
				*/
				const UNIFORM_BUFFER_INDEX index = glGetUniformBlockIndex(CurrentProgramHandle, *targetResourceSlotDesc.Name);

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