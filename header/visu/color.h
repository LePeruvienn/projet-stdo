#ifndef COLOR_H
#define COLOR_H

typedef struct color color;

typedef struct color_rgba color_rgba;
typedef struct color_norm color_norm;

struct color_rgba
{
	unsigned char r, g, b, a;
};

struct color_norm
{
	float r, g, b, a;
};


struct color
{
	// NE PAS MODIFIER CES VALEURS SANS LES SETTERS !!
	color_rgba rgba;
	color_norm norm;
};

color create_color_rgba(color_rgba rgba);
color create_color_norm(color_norm norm);

void color_set_rgba(color* c, color_rgba rbga);
void color_set_norm(color* c, color_norm norm);


#endif // COLOR_H
