#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}

	char as[128];
	char *s1 = argv[1];
	char *s2 = argv[2];
	int i = 0;

	while (i < 128)
		as[i++] = 0;
	i = 0;
	while (s1[i])
	{
		if (as[(int)s1[i]] == 1)
			continue ;
		as[(int)s1[i]] = 1;
		write(1, &s1[i], 1);
	}
	i = 0;
	while (s2[i])
	{
		if (as[(int)s2[i++]] == 1)
			continue ;
		as[(int)s2[i]] = 1;
		write(1, &s2[i], 1);
	}
	write(1, "\n", 1);
	return (0);
}
