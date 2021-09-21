#include "micro_paint.h"

int ft_error(char *s) {
	int i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (1);
}

int	check_pos(float x, float y, float id_x, float id_y, float width, float height) {
	if (id_x + width < x || x < id_x
		|| id_y + height < y || y < id_y)
		return (0);
	else if ((id_x + width) - x < 1.0 || x - id_x < 1.0
		|| (id_y + height) - y < 1.0 || y - id_y < 1.0)
		return (1);
	return (2);
}

int	main(int ac, char **av) {
	FILE	*file;
	char	*canvas;
	int		read, pos;
	int		x, y;

	int		b_width, b_height;
	char	background;

	char	id, color;
	float	id_x, id_y, width, height;

	if (ac != 2)
		return (ft_error(ERR1));
	if (!(file = fopen(av[1], "r"))
		|| (fscanf(file, "%d %d %c\n", &b_width, &b_height, &background) != 3)
		|| (!(0 < b_width && b_width <= 300 && 0 < b_height && b_height <= 300))
		|| (!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return (ft_error(ERR2));
	memset(canvas, background, b_width * b_height);
	while ((read = fscanf(file, "%c %f %f %f %f %c\n", &id, &id_x, &id_y, &width, &height, &color)) == 6) {
		if (!(0 < width && 0 < height) || !(id == 'R' || id == 'r'))
			break ;
		for (y = 0; y < b_height; y++)
			for (x = 0; x < b_width; x++) {
				pos = check_pos((float)x, (float)y, id_x, id_y, width, height);
				if (pos == 1 || (pos == 2 && id == 'R'))
					canvas[y * b_width + x] = color;
			}
	}
	if (read != -1)	{
		free(canvas);
		return (ft_error(ERR2));
	}
	for (y = 0; y < b_height; y++) {
		write(1, canvas + y * b_width, b_width);
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(file);
	return (0);
}
