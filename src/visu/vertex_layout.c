#include "visu/vertex_layout.h"
#include "visu/vertex.h"

#include "utils/debug.h"
#include "utils/logger.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stddef.h>

struct vertex_layout
{
	GLsizei stride;
	vertex_attr attributes[MAX_VERTEX_ATTRIBUTE_AMOUNT];
	unsigned int attribute_amount;
};

vertex_layout create_custom_layout(vertex_attr* attributes,
                                   unsigned int attribute_amount,
                                   GLsizei stride)
{
	if (attribute_amount > MAX_VERTEX_ATTRIBUTE_AMOUNT)
	{
		LOG_ERROR("To many vertex layout attributes for custom layout.");
		return NULL;
	}

	vertex_layout layout = malloc(sizeof(struct vertex_layout));

	layout->attribute_amount = attribute_amount;
	layout->stride = stride;

	for (unsigned int i = 0; i < attribute_amount; ++i)
	{
		layout->attributes[i] = attributes[i];
	}

	return layout;
}

vertex_layout create_vertex_layout()
{
	vertex_layout layout = malloc(sizeof(struct vertex_layout));

	layout->stride = sizeof(vertex);
	layout->attribute_amount = 1;

	vertex_attr* attr = layout->attributes;

	attr[0].id = VERTEX_ATTR_POSITION;
	attr[0].size = 2;
	attr[0].type = GL_FLOAT;
	attr[0].normalized = GL_FALSE;
	attr[0].offset = offsetof(vertex, x);
	attr[0].divisor = 0;

	return layout;
}

void free_vertex_layout(vertex_layout layout)
{
	free(layout);
}

void setup_vao_attributes(vertex_layout layout)
{
	for (unsigned int i = 0; i < layout->attribute_amount; ++i)
	{
		vertex_attr* attr = &layout->attributes[i];

		// entiers : GL_INT, GL_UNSIGNED_INT, GL_SHORT, etc.
		if (attr->type == GL_INT || attr->type == GL_UNSIGNED_INT ||
			attr->type == GL_BYTE || attr->type == GL_UNSIGNED_BYTE ||
			attr->type == GL_SHORT || attr->type == GL_UNSIGNED_SHORT)
		{
			GL_CALL(glVertexAttribIPointer(
				attr->id,
				attr->size,
				attr->type,
				layout->stride,
				(void*) attr->offset
			));
		}
		else
		{
			GL_CALL(glVertexAttribPointer(
				attr->id,
				attr->size,
				attr->type,
				attr->normalized,
				layout->stride,
				(void*) attr->offset
			));
		}

		glEnableVertexAttribArray(attr->id);
		if (attr->divisor != 0)
		{
			glVertexAttribDivisor(attr->id, attr->divisor);
		}
	}
}
