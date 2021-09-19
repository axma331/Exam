#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERR1 "Error: argument\n"
#define ERR2 "Error: Operation file corrupted\n"

int ft_error(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (1);
}

int	check_pos(float x, float y, float id_x, float id_y, float width, float height)
{
	if (x < id_x || x > id_x + width || y < id_y || y > id_y + height)
		return (0);
	else if (x - id_x < 1.0 || (id_x + width) - x < 1.0 ||
			y - id_y < 1.0|| (id_y + height) - y < 1.0)
		return (1);
	return (2);
}

int	main(int ac, char **av)
{
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
	if (!(file = fopen(av[1], "r")) ||
			(fscanf(file, "%d %d %c\n", &b_width, &b_height, &background) != 3) ||
		(!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300)) || 
		(!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return (ft_error(ERR2));
	memset(canvas, background, b_width * b_height);
	while ((read = fscanf(file, "%c %f %f %f %f %c\n", &id, &id_x, &id_y, &width, &height, &color)) == 6)
	{
		if (!(width > 0 && height > 0) || !(id == 'R' || id == 'r'))
			break ;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, id_x, id_y, width, height);
				if (pos == 1 || (pos == 2 && id == 'R'))
					canvas[y * b_width + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(canvas);
		return (ft_error(ERR2));
	}
	y = -1;
	while (++y < b_height)
	{
		write(1, canvas + y * b_width, b_width);
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(file);
	return (0);
}
