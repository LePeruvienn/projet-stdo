#include "visu/mesh.h"
#include "visu/vertex.h"
#include "visu/vertex_layout.h"
#include "utils/logger.h"
#include "utils/debug.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#define QUAD_VERTICES_AMOUNT 4
#define QUAD_INDICES_AMOUNT 6

struct mesh
{
	void* vertices; // Peut contenir différent type de vertex
	size_t vertices_size;
	unsigned int vertices_amount;

	unsigned int* indices;
	unsigned int indices_amount;

	vertex_layout layout; // doit être corda avec les type de vertex dans le buffer
};

static mesh create_mesh()
{
	mesh m = malloc(sizeof(struct mesh));

	m->vertices = NULL;
	m->vertices_size = 0;
	m->vertices_amount = 0;

	m->indices = NULL;
	m->indices_amount = 0;

	m->layout = NULL;

	return m;
}

/**
* \brief Créer les données de vertex d'un carré
* \return mesh vertex du carré
*/
mesh create_quad()
{
	mesh m = create_mesh();

	m->vertices_amount = QUAD_VERTICES_AMOUNT;
	m->indices_amount = QUAD_INDICES_AMOUNT;

	m->vertices_size = sizeof(vertex) * m->vertices_amount;

	vertex* vertices = malloc(m->vertices_size);
	unsigned int* indices = malloc(sizeof(unsigned int) * QUAD_INDICES_AMOUNT);

	vertices[0] = (vertex) { - 1.f,   1.f };
	vertices[1] = (vertex) {   1.f,   1.f };
	vertices[2] = (vertex) {   1.f, - 1.f };
	vertices[3] = (vertex) { - 1.f, - 1.f };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	m->vertices = vertices;
	m->indices = indices;
	m->layout = create_vertex_layout();

	return m;
}

/**
* \brief Créer les données de vertex d'un cercle
* \return mesh vertex du cercle
*/
mesh create_circle_fan(unsigned int segments)
{
	mesh m = create_mesh();

	m->vertices_amount = segments + 1;
	m->indices_amount = segments * 3;

	m->vertices_size = sizeof(vertex) * m->vertices_amount;

	vertex* vertices = malloc(m->vertices_size);
	unsigned int* indices = malloc(sizeof(unsigned int) * m->indices_amount);

	// centre du cercle
	vertices[0] = (vertex) { 0.0f, 0.0f };

	for (unsigned int i = 0; i < segments; ++i)
	{
		float angle = (2.0f * (float)M_PI * (float)i) / (float)segments;
		float x = cosf(angle);
		float y = sinf(angle);

		vertices[i + 1] = (vertex) {x, y};
	}

	// triangle fan
	for (unsigned int i = 0; i < segments; ++i)
	{
		unsigned int next = (i + 1) % segments;

		indices[i * 3 + 0] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = next + 1;
	}

	m->vertices = vertices;
	m->indices = indices;
	m->layout = create_vertex_layout();

	return m;
}

mesh create_line(vertex* vertices, unsigned int size)
{
	mesh m = malloc(sizeof(struct mesh));

	m->vertices = NULL;
	m->vertices_size = sizeof(vertex) * size;
	m->vertices_amount = size;

	m->indices = NULL;
	m->indices_amount = size;

	m->vertices = malloc(m->vertices_size);
	m->indices = malloc(sizeof(unsigned int) * m->indices_amount);

	memcpy(m->vertices, vertices, m->vertices_size);

	for (unsigned int i = 0; i < size; i++)
	{
		m->indices[i] = i;
	}

	m->layout = create_vertex_layout();

	return m;
}

void load_mesh_data(mesh m)
{
	LOG_INFO("Loaded a mesh to GPU of %u vertices and %u indices", m->vertices_amount, m->indices_amount);

	GL_CALL(glBufferData(GL_ARRAY_BUFFER,
	             m->vertices_size,
	             m->vertices,
	             GL_STATIC_DRAW));

	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             sizeof(unsigned int) * m->indices_amount,
	             m->indices,
	             GL_STATIC_DRAW));
}

void free_mesh(mesh m)
{
	free_vertex_layout(m->layout);
	free(m->vertices);
	free(m->indices);
	free(m);
}

unsigned int get_mesh_indices_amount(mesh m)
{
	return m->indices_amount;
}

vertex_layout get_mesh_vertex_layout(mesh m)
{
	return m->layout;
}
