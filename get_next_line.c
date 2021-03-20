#include "get_next_line.h"

int ft_strlen(char *n)
{
	int i = 0;

	while (n[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *s3;
	int i;
	int j;


	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

int get_next_line(char **line)
{
	char buf[2];
	char *tmp;
	int ret;

	*line = (char *)malloc(1);
	**line = '\0';
	while ((ret = read(0, &buf, 1)) > 0)
	{
		buf[1] = '\0';
		if (*buf == '\n')
			return (1);
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (ret);
}
