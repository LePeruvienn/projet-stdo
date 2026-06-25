#include "visu/texture.h"

#include "utils/logger.h"
#include "utils/debug.h"

#include "glad/glad.h"

// L'import de stb_image.h fait crash le linter,
// - Pas un soucis pour le programme juste pour l'IDE.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <stdbool.h>

#define LOG_TEXTURE_IS_OK(s, n)                        \
	do { if (s != NULL) LOG_INFO("[%s] : OK", n);      \
	     else           LOG_ERROR("[%s] : FAILED", n); \
	} while (0)

struct texture
{
	GLuint id;
	GLuint type;

	int width;
	int height;
};

// Shaders crées à l'initialisation
// texture global_default_texture = NULL;

void create_global_textures()
{

}

void free_global_textures()
{

}

texture create_texture(const char* filepath)
{
	texture t = malloc(sizeof(struct texture));

	t->id = 0;
	t->type = GL_TEXTURE_2D;
	t->width = 0;
	t->height = 0;

	GL_CALL(glGenTextures(1, &t->id));
	GL_CALL(glBindTexture(t->type, t->id));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);

	int channels = 0;
	unsigned char* data = stbi_load(filepath, &t->width, &t->height, &channels, STBI_rgb_alpha);

	if (data == NULL)
	{
		LOG_ERROR("Failed to load image.");
		return NULL;
	}

	GL_CALL(glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		t->width,
		t->height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	));

	LOG_INFO("Loaded an image of %dx%d pixels.", t->width, t->height);

	glBindTexture(t->type, 0);

	return t;
}

void free_texture(texture t)
{
	if (t == NULL)
	{
		LOG_ERROR("Tried to free a NULL texture");
		return;
	}

	glDeleteTextures(1, &t->id);
	free(t);
}

void bind_texture(texture t, GLuint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(t->type, t->id);
}

void unbind_texture(texture t)
{
	glBindTexture(t->type, 0);
}

