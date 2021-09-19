#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_zone {
	int		width;
	int		height;
	char	background;
} 				t_zone;

typedef struct	s_shape {
	char	type;
	float	x;
	float	y;
	char	color;
	float	width;
	float	height;
}				t_shape;

int	ft_strlen(char const *s) {
	int	i = 0;

	while (s && s[i])
		i++;
	return (i);
}

int	str_error(char const *s, int ret) {
	write(1, s, ft_strlen(s));
	return (ret);
}

int	clear_all(FILE *file, char *drawing) {
	fclose(file);
	if (drawing)
		free(drawing);
	return (1);
}

int	check_zone(t_zone *zone) {
	return (0 < zone->width && zone->width <= 300
			&& 0 < zone->height && zone->height <= 300);
}

int	check_shape(t_shape *shape) {
	return (0.00000000 < shape->width && 0.00000000 < shape->height
			&& (shape->type == 'r' || shape->type == 'R'));
}

int	get_zone(FILE *file, t_zone *zone) {
	int ret;

	if ((ret = fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background)) != 3)
		return (0);
	if (!check_zone(zone) || ret == -1)
		return (0);
	return (1);
}

char	*paint_background(t_zone *zone) {
	char	*drawing;

	if (!(drawing = (char*)malloc(sizeof(*drawing) * (zone->width * zone->height))))
		return (NULL);
	for (int i = 0; i < zone->width * zone->height; i++)
		drawing[i] = zone->background;
	return (drawing);
}

int	in_rectangle(float x, float y, t_shape *shape) {
	if (((x < shape->x || (shape->x + shape->width < x))
		|| (y < shape->y)) || (shape->y + shape->height < y))
		return (0);
	if (((x - shape->x < 1.00000000) || ((shape->x + shape->width) - x < 1.00000000)) ||
	((y - shape->y < 1.00000000 || ((shape->y + shape->height) - y < 1.00000000))))
		return (2);
	return (1);
}

void	draw_shape(char **drawing, t_shape *shape, t_zone *zone)
{
	int	i, j, ret;

	for (i = 0; i < zone->height; i++)
		for (j = 0; j < zone->width; j++) {
			ret = in_rectangle(j, i, shape);
			if ((shape->type == 'r' && ret == 2) || (shape->type == 'R' && ret))
				(*drawing)[(i * zone->width) + j] = shape->color;
		}
}

int	draw_shapes(FILE *file, char **drawing, t_zone *zone) {
	t_shape	tmp;
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6) {
		if (!check_shape(&tmp))
			return (0);
		draw_shape(drawing, &tmp, zone);
	}
	if (ret != -1)
		return (0);
	return (1);
}

void	draw_drawing(char *drawing, t_zone *zone) {
	for (int i = 0; i < zone->height; i++) {
		write(1, drawing + (i * zone->width), zone->width);
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv) {
	t_zone	zone;
	FILE	*file;
	char	*drawing;

	zone.width = 0;
	zone.height = 0;
	zone.background = 0;
	if (argc != 2)
		return (str_error("Error: argument\n", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n", 1));
	if (!get_zone(file, &zone))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n", 1));
	if (!(drawing = paint_background(&zone)))
		return (clear_all(file, NULL) && str_error("Error: malloc failed :)\n", 1));
	if (!draw_shapes(file, &drawing, &zone))
		return (clear_all(file, drawing) && str_error("Error: Operation file corrupted\n", 1));
	draw_drawing(drawing, &zone);
	clear_all(file, drawing);
	return (0);
}
