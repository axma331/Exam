#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

int	check_pos(float x, float y, float id_x, float id_y, float radius)
{
	float distance = sqrtf(powf(x - id_x, 2.) + powf(y - id_y, 2.));
	if (distance <= radius)
	{
		if ((radius - distance) < 1.00000000)
			return (0);
		return (1);
	}
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
	float	id_x, id_y, radius;

	if (ac != 2)
		return (ft_error(ERR1));
	if (!(file = fopen(av[1], "r")) ||
		(fscanf(file, "%d %d %c\n", &b_width, &b_height, &background) != 3) ||
		(!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300)) ||
		(!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return (ft_error(ERR2));
	memset(canvas, background, b_width * b_height);
	while ((read = fscanf(file, "%c %f %f %f %c\n", &id, &id_x, &id_y, &radius, &color)) == 5)
	{
		if (!(radius > 0) || !(id == 'C' || id == 'c'))
			break ;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, id_x, id_y, radius);
				if (pos == 0 || (pos == 1 && id == 'C'))
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
