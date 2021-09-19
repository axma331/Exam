#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_zone {
	int		width;
	int		height;
	char	background;
}				t_zone;

typedef struct	s_shape {
	char	type;
	float	x;
	float	y;
	char	color;
	float	radius;
}				t_shape;

int	ft_strlen(char const *s) {
	int	i = 0;

	while (s[i])
		i++;
	return (i);
}

char	*get_zone(FILE *file, t_zone *zone) {
	char	*tmp;

	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return (NULL);
	if (zone->width <= 0 || 300 < zone->width || zone->height <= 0 || 300 < zone->height)
		return (NULL);
	if (!(tmp = (char*)malloc(sizeof(*tmp) * (zone->width * zone->height))))
		return (NULL);
	for (int i = 0; i < zone->width * zone->height; i++)
		tmp[i] = zone->background;
	return (tmp);
}

int	in_circle(float x, float y, t_shape *shape) {
	float	distance;

	distance = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
	if (distance <= shape->radius) {
		if ((shape->radius - distance) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_shape(t_zone *zone, char *drawing, t_shape *shape) {
	int	x, y, ret;

	for (y = 0; y < zone->height; y++)
		for (x = 0; x < zone->width; x++) {
			ret = in_circle((float)x, (float)y, shape);
			if ((shape->type == 'c' && ret == 2) || (shape->type == 'C' && ret))
				drawing[(y * zone->width) + x] = shape->color;
		}
}

int	draw_shapes(FILE *file, t_zone *zone, char *drawing) {
	t_shape	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5) {
		if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
			return (0);
		draw_shape(zone, drawing, &tmp);
	}
	if (ret != -1)
		return (0);
	return (1);
}

void	draw_drawing(t_zone *zone, char *drawing) {
	for (int i = 0; i < zone->height; i++) {
		write(1, drawing + (i * zone->width), zone->width);
		write(1, "\n", 1);
	}
}

int	str_error(char const *s) {
	write(1, s, ft_strlen(s));
	return (1);
}

int	clear_all(FILE *file, char *drawing, char const *s) {
	if (file)
		fclose(file);
	if (drawing)
		free(drawing);
	if (s)
		str_error(s);
	return (1);
}

int main(int argc, char **argv) {
	FILE	*file;
	t_zone	zone;
	char	*drawing;

	zone.width = 0;
	zone.height = 0;
	zone.background = 0;
	drawing = NULL;
	if (argc != 2)
		return (str_error("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n"));
	if (!(drawing = get_zone(file, &zone)))
		return (clear_all(file, NULL, "Error: Operation file corrupted\n"));
	if (!(draw_shapes(file, &zone, drawing)))
		return (clear_all(file, drawing, "Error: Operation file corrupted\n"));
	draw_drawing(&zone, drawing);
	clear_all(file, drawing, NULL);
	return (0);
}
