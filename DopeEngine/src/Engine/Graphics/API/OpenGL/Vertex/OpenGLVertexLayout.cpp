#include "OpenGLVertexLayout.h"
#include <Engine/Graphics/API/OpenGL/Vertex/OpenGLVertexUtils.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLVertexLayout::OpenGLVertexLayout(const VertexLayoutDescription& description, DEVICE device) : VertexLayout(description)
	{
		/*
		* Initialize
		*/
		Handle = GL_NONE;
		Device = device;

		/*
		* Create
		*/
		create();

	}
	OpenGLVertexLayout::~OpenGLVertexLayout()
	{
		invalidate();
	}
	void OpenGLVertexLayout::create_layout()
	{
		create();
	}
	void OpenGLVertexLayout::create()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create
		*/
		glCreateVertexArrays(1, &Handle);

		/*
		* Generate layout
		*/
		glBindVertexArray(Handle);
		const VertexLayoutDescription& layoutDescription = get_description_fast();
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
		glBindVertexArray(0);
	}
	void OpenGLVertexLayout::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle != GL_NONE)
		{
			glDeleteVertexArrays(1, &Handle);
			Handle = GL_NONE;
		}
	}
}