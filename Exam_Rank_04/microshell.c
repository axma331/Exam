#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(const char *str)
{
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

void error_cd_bad_args(void)
{
	write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
}

void error_cd_cannot_change(char *str)
{
	write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void error_cannot_exec(char *str)
{
	write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void exit_fatal(void)
{
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(1);
}

void ft_cd(char **line)
{
	int i = 0;
	while(line[i]) i++;
	if (i != 2)
	{
		error_cd_bad_args();
		return;
	}
	if (chdir(line[1]))
		error_cd_cannot_change(line[1]);
}

int main(int argc, char **argv, char **env)
{
	int i = 1;		//номер аргумента
	int len = 0;	//длина line
	char **line = NULL;		//аргументы без ; и | (т.е. это одна команда и его аргументы)
	int m = 0;		//вспомог счетчик
	int is_pipe = 0;	//flag for |
	int fd[2];
	int save0 = 0;
	int save1 = 0;
	int opened = 0;
	pid_t pid;
	int status = 0;	//for waitpid()
	int flag = 0;	//for cd

	if (argc > 1)
	{
		while (i < argc)
		{
			//если тек аргумент ; или | пропускаем этот аргумент
			if (strcmp(argv[i], ";") == 0 || strcmp(argv[i], "|") == 0){
				i++;
				continue;
			}

			len = 0;
			//кол-во аргументов до ; или | или до завершения аргументов
			while (argv[i + len] && strcmp(argv[i + len], ";") != 0 && strcmp(argv[i + len], "|") != 0)
				len++;
			if (!(line = (char **)malloc(sizeof(char *) * (len + 1))))
				exit_fatal();
			line[len] = NULL;

			m = 0;
			//запись команды и его аргументов в line
			while (m < len){
				line[m] = argv[i];
				if(strcmp(argv[i], "cd") == 0)
					flag = 1;
				m++;
				i++;
			}

			if (argv[i] && strcmp(argv[i], "|") == 0)
				is_pipe = 1;
			else
				is_pipe = 0;

			if ((argv[i] && strcmp(argv[i], "cd") == 0) || (flag == 1))
				ft_cd(line);

			if (opened){
				save0 = dup(0);   	// создаем копию stdin save0 = stdin
				dup2(fd[0], 0);     // stdin = fd[0] (stdin стал копией f[0])
				close(fd[0]);
			}
			if (is_pipe){
				if (pipe(fd))
					exit_fatal();
				save1 = dup(1);		// создаем копию stdout save1 = stdout
				dup2(fd[1], 1);		// stdout = fd[1] (stdout стал копией f[1])
				close(fd[1]);
			}

			pid = fork();
			if (pid < 0)
				exit_fatal();
			else if (pid == 0){
				if(flag == 0){
					if (execve(line[0], line, env))
						error_cannot_exec(line[0]);	
				}
				exit(0);
			}
			else
				waitpid(pid, &status, 0);

			if (opened){
				dup2(save0, 0);
				close(save0);
				opened = 0;
			}
			if (is_pipe){
				dup2(save1, 1);
				close(save1);
				opened = 1;
			}
			flag = 0;
			free(line);
		}
	}
	return (0);
}
