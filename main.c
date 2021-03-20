#include "get_next_line.h"

int main()
{
	char *line;
	int r;

	line = NULL;
	while ((r = get_next_line(&line) > 0))
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	return (0);
}
