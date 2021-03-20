#include <unistd.h>

int main(int argc, char **argv)
{
	char *s1 = argv[1];
	char *s2 = argv[2];
	int i;
	int j;

	if (argc == 3)
	{
		i = 0;
		while (s1[i])
		{
			j = 0;
			while (s1[j])
			{
				if (s1[i] == s1[j])
					break;
				j++;
			}
			if (j == i)
			{
				j = 0;
				while (s2[j])
				{
					if (s2[j] == s1[i])
					{
						write(1, &s1[i], 1);
						break;
					}
					j++;
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
