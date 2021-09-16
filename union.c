#include <unistd.h>

int main(int ac, char **av)
{
	int i;
	int	z[255];

	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
			if(z[(int)av[1][i]] == 0)
			{
				write (1, &av[1][i], 1);
				z[(int)av[1][i]] = 1;
			}
			i++;
		}
		i = 0;
		while (av[2][i])
		{
			if (z[(int)av[2][i]] == 0)
			{
				write(1, &av[2][i], 1);
				z[(int)av[2][i]] = 1;
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}