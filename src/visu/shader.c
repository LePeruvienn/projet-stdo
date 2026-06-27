#include "visu/shader.h"
#include "visu/camera.h"
#include "visu/color.h"

#include "utils/read_file.h"
#include "utils/logger.h"
#include "utils/debug.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CHECK_SHADER_IS_NULL(s, msg, ret) \
	do { if (s == NULL) {                 \
		LOG_ERROR(msg); return ret;       \
	}} while(0)

#define LOG_SHADER_IS_OK(s, n)                         \
	do { if (s != NULL) LOG_INFO("[%s] : OK", n);      \
	     else           LOG_ERROR("[%s] : FAILED", n); \
	} while (0)

struct shader
{
	// ID du shader OpenGL 
	GLuint program;

	// location caméra
	GLint loc_camera_position;
	GLint loc_camera_zoom;
	GLint loc_camera_aspect;

	// locations model
	GLint loc_model_position;
	GLint loc_model_scale;
	GLint loc_model_color;

	// location grid
	GLint loc_grid_size;
	GLint loc_grid_bg_color;
	GLint loc_grid_line_color;

	// locations circle shader
	GLint loc_circle_color;
	GLint loc_circle_radius;
	GLint loc_circle_border_color;
	GLint loc_circle_border_thickness;

	// locations edge shader
	GLint loc_edge_thickness;
	GLint loc_edge_color;

	// texturec location
	GLint loc_texture;

	// text color location 
	GLint loc_text_color;
};

// Nom des variables uniformes
const char* U_NAME_CAMERA_POSITION = "uCameraPosition";
const char* U_NAME_CAMERA_ZOOM     = "uCameraZoom";
const char* U_NAME_CAMERA_ASPECT   = "uCameraAspect";

const char* U_NAME_MODEL_POSITION  = "uModelPosition";
const char* U_NAME_MODEL_SCALE     = "uModelScale";
const char* U_NAME_MODEL_COLOR     = "uModelColor";

const char* U_NAME_GRID_SIZE       = "uGridSize";
const char* U_NAME_GRID_BG_COLOR   = "uGridBgColor";
const char* U_NAME_GRID_LINE_COLOR = "uGridLineColor";

const char* U_NAME_CIRCLE_COLOR            = "uCircleColor";
const char* U_NAME_CIRCLE_RADIUS           = "uCircleRadius";
const char* U_NAME_CIRCLE_BORDER_COLOR     = "uCircleBorderColor";
const char* U_NAME_CIRCLE_BORDER_THICKNESS = "uCircleBorderThickness";

const char* U_NAME_EDGE_THICKNESS  = "uEdgeThickness";
const char* U_NAME_EDGE_COLOR      = "uEdgeColor";

const char* U_NAME_TEXTURE         = "uTexture";

const char* U_NAME_TEXT_COLOR      = "uTextColor";

// Shaders globaux précharger à l'intialisations
shader global_default_shader = NULL;
shader global_circle_shader = NULL;

int get_shader_status(GLuint shader, GLenum pname, const char* shader_name)
{
	int  success;
	char infoLog[512];

	glGetShaderiv(shader, pname, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		if (shader_name != NULL)
			LOG_ERROR("shader \"%s\" status failed :\n    %s", shader_name, infoLog);
		else
			LOG_ERROR("shader status failed :\n    %s", infoLog);
	}

	return success;
}

int get_program_status(GLuint program, GLenum pname)
{
	int  success;
	char infoLog[512];

	glGetProgramiv(program, pname, &success);

	if(!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		LOG_ERROR("program status failed, %s", infoLog);
	}

	return success;
}

void create_global_shaders()
{
	LOG_INFO("Loading shaders ...\n");

	global_default_shader = create_shader("asset/shader/default.vert",
	                                      "asset/shader/default.frag");

	global_circle_shader = create_shader("asset/shader/default.vert",
	                                     "asset/shader/circle.frag");

	LOG_SHADER_IS_OK(global_default_shader, "global_default_shader");
	LOG_SHADER_IS_OK(global_circle_shader, "global_default_shader");
}

void free_global_shaders()
{
	free_shader(global_default_shader);

	global_default_shader = NULL;
}

int compile_shader(const char* path, GLuint type, GLuint* out)
{
	GLuint shader = glCreateShader(type);

	char* data = read_file_txt(path);

	if (data == NULL)
	{
		LOG_ERROR("Failed read shader source code");
		return 1;
	}

	const char* sources[] = { data };

	glShaderSource(shader, 1, sources, NULL);
	glCompileShader(shader);

	free(data);

	if (!get_shader_status(shader, GL_COMPILE_STATUS, path))
	{
		LOG_ERROR("GL_COMPILE_STATUS failed");
		return 2;
	}

	*out = shader;

	return 0;
}

int compile_shader_program(GLuint* shaders, unsigned int size, GLuint* out)
{
	GLuint shader_program = glCreateProgram();

	for (size_t i = 0; i < size; i++)
	{
		glAttachShader(shader_program, shaders[i]);
	}

	glLinkProgram(shader_program);

	if (!get_program_status(shader_program, GL_LINK_STATUS))
	{
		LOG_ERROR("GL_LINK_STATUS failed");
		return 1;
	}

	*out = shader_program;

	return 0;
}

shader create_shader(const char* vert_shader_path, const char* frag_shader_path)
{
	shader s = malloc(sizeof(struct shader));

	GLuint vert_shader;

	if (compile_shader(vert_shader_path, GL_VERTEX_SHADER, &vert_shader) != 0)
	{
		free(s);

		LOG_ERROR("Failed to compile vertex shader.");
		return NULL;
	}

	GLuint frag_shader;

	if (compile_shader(frag_shader_path, GL_FRAGMENT_SHADER, &frag_shader) != 0)
	{
		glDeleteShader(vert_shader);
		free(s);

		LOG_ERROR("Failed to compile fragment shader.");
		return NULL;
	}

	GLuint shaders[2] = {vert_shader, frag_shader};

	if (compile_shader_program(shaders, 2, &s->program) != 0)
	{
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		free(s);

		LOG_ERROR("Failed to compile shader program.");
		return NULL;
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	s->loc_camera_position = glGetUniformLocation(s->program, U_NAME_CAMERA_POSITION);
	s->loc_camera_zoom     = glGetUniformLocation(s->program, U_NAME_CAMERA_ZOOM);
	s->loc_camera_aspect   = glGetUniformLocation(s->program, U_NAME_CAMERA_ASPECT);

	s->loc_model_position  = glGetUniformLocation(s->program, U_NAME_MODEL_POSITION);
	s->loc_model_scale     = glGetUniformLocation(s->program, U_NAME_MODEL_SCALE);
	s->loc_model_color     = glGetUniformLocation(s->program, U_NAME_MODEL_COLOR);

	s->loc_grid_size       = glGetUniformLocation(s->program, U_NAME_GRID_SIZE);
	s->loc_grid_bg_color   = glGetUniformLocation(s->program, U_NAME_GRID_BG_COLOR);
	s->loc_grid_line_color = glGetUniformLocation(s->program, U_NAME_GRID_LINE_COLOR);

	s->loc_circle_color            = glGetUniformLocation(s->program, U_NAME_CIRCLE_COLOR);
	s->loc_circle_radius           = glGetUniformLocation(s->program, U_NAME_CIRCLE_RADIUS);
	s->loc_circle_border_color     = glGetUniformLocation(s->program, U_NAME_CIRCLE_BORDER_COLOR);
	s->loc_circle_border_thickness = glGetUniformLocation(s->program, U_NAME_CIRCLE_BORDER_THICKNESS);

	s->loc_edge_thickness = glGetUniformLocation(s->program, U_NAME_EDGE_THICKNESS);
	s->loc_edge_color     = glGetUniformLocation(s->program, U_NAME_EDGE_COLOR);

	s->loc_texture        = glGetUniformLocation(s->program, U_NAME_TEXTURE);

	s->loc_text_color     = glGetUniformLocation(s->program, U_NAME_TEXT_COLOR);

	return s;
}

void free_shader(shader s)
{
	if (s == NULL)
	{
		LOG_ERROR("Tried to free a NULL shader");
		return;
	}

	glDeleteProgram(s->program);
	free(s);
}

void bind_shader(shader s)
{
	if (s == NULL)
	{
		LOG_ERROR("Tried to bind a NULL shader.");
		return;
	}

	glUseProgram(s->program);
}

void unbind_shader()
{
	glUseProgram(0);
}

void set_shader_camera(shader s, camera c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set camera uniform to a NULL shader.", );

	float x = get_camera_pos_x(c);
	float y = get_camera_pos_y(c);

	float zoom = get_camera_zoom(c);
	float aspect = get_camera_aspect(c);

	static bool print_warnining_not_used = true;

	bool is_loc_camera_pos_used  = s->loc_camera_position != - 1;
	bool is_loc_camera_zoom_used = s->loc_camera_zoom     != - 1;
	bool is_loc_camera_aspect_used = s->loc_camera_aspect != - 1;

	if (print_warnining_not_used  && (!is_loc_camera_pos_used    ||
	                                  !is_loc_camera_zoom_used   ||
	                                  !is_loc_camera_aspect_used ))
	{
		LOG_WARNING("Some camera uniform location are not used (-1).");
		print_warnining_not_used = false;
	}

	if (is_loc_camera_pos_used)
	GL_CALL(glUniform2f(s->loc_camera_position, x, y));


	if (is_loc_camera_zoom_used)
	GL_CALL(glUniform1f(s->loc_camera_zoom, zoom));

	if(is_loc_camera_aspect_used)
	GL_CALL(glUniform1f(s->loc_camera_aspect, aspect));
}

void set_shader_model_pos(shader s, float x, float y)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set model position uniform to a NULL shader.", );
	
	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_model_position == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	GL_CALL(glUniform2f(s->loc_model_position, x, y));
}

void set_shader_model_scale(shader s, float sx, float sy)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set model scale uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_model_scale == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	GL_CALL(glUniform2f(s->loc_model_scale, sx, sy));
}

void set_shader_texture_unit(shader s, GLint unit)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set texture cube uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_texture == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	GL_CALL(glUniform1i(s->loc_texture, unit));
}

void set_shader_model_color(shader s, unsigned char r,
                                      unsigned char g,
                                      unsigned char b)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set model color uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_model_color == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	float rf = (float) r / 255.f;
	float gf = (float) g / 255.f;
	float bf = (float) b / 255.f;

	GL_CALL(glUniform3f(s->loc_model_color, rf, gf, bf));
}

void set_shader_grid_size(shader s, float size)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set model color uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_grid_size == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	GL_CALL(glUniform1f(s->loc_grid_size, size));
}

void set_shader_grid_bg_color(shader s, color c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set model color uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_grid_bg_color == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_grid_bg_color,
		nc->r, nc->g, nc->b, nc->a)
	);
}

void set_shader_grid_line_color(shader s, color c)
{
	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_grid_line_color == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_grid_line_color,
		nc->r, nc->g, nc->b, nc->a)
	);
}


void set_shader_circle_color(shader s, color c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set texture cube uniform to a NULL shader.", );

	static bool print_warnining_not_used = true;
	if (print_warnining_not_used  && s->loc_circle_color == - 1)
	{
		LOG_WARNING("Uniform is not used in current shader (-1).");
		print_warnining_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_circle_color,
		nc->r, nc->g, nc->b, nc->a)
	);
}

void set_shader_circle_radius(shader s, float r)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle radius on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_circle_radius == -1)
	{
		LOG_WARNING("Uniform 'circle radius' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	GL_CALL(glUniform1f(s->loc_circle_radius, r));
}

void set_shader_circle_border_color(shader s, color c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle border color on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_circle_border_color == -1)
	{
		LOG_WARNING("Uniform 'circle border color' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_circle_border_color,
		nc->r, nc->g, nc->b, nc->a
	));
}

void set_shader_circle_border_thinkness(shader s, float t)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle border thickness on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_circle_border_thickness == -1)
	{
		LOG_WARNING("Uniform 'circle border thickness' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	GL_CALL(glUniform1f(s->loc_circle_border_thickness, t));
}

void set_shader_edge_color(shader s, color c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle border thickness on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_edge_color == -1)
	{
		LOG_WARNING("Uniform 'circle border thickness' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_edge_color,
		nc->r, nc->g, nc->b, nc->a
	));
}

void set_shader_edge_thickness(shader s, float t)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle border thickness on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_edge_thickness == -1)
	{
		LOG_WARNING("Uniform 'circle border thickness' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	GL_CALL(glUniform1f(s->loc_edge_thickness, t));
}

void set_shader_text_color(shader s, color c)
{
	CHECK_SHADER_IS_NULL(s, "Tried to set circle border thickness on a NULL shader.", );

	static bool print_warning_not_used = true;
	if (print_warning_not_used && s->loc_text_color == -1)
	{
		LOG_WARNING("Uniform 'text color' is not used in current shader (-1).");
		print_warning_not_used = false;
		return;
	}

	color_norm* nc = &c.norm;

	GL_CALL(glUniform4f(
		s->loc_text_color,
		nc->r, nc->g, nc->b, nc->a
	));
}
