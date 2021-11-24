#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(const char *str) {
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

void error_cd_bad_args(void) {
	write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
}

void error_cd_cannot_change(char *str) {
	write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void error_cannot_exec(char *str) {
	write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void exit_fatal(void) {
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(1);
}

void ft_cd(char **line) {
	int i = 0;
	while(line[i])
		i++;
	if (i != 2) {
		error_cd_bad_args();
		return ;
	}
	if (chdir(line[1]))
		error_cd_cannot_change(line[1]);
}

int main(int ac, char **av, char **env) {
	int i = 1;
	int len, j;
	int fd[2], fds[2];
	int f_cd = 0;
	int f_pipe = 0;
	int opened = 0;
	int status = 0;
	pid_t pid;
	char **line = NULL;		//аргументы без ; и | (т.е. это одна команда и его аргументы)

	while (ac > 1 && i < ac) {
		if ((!strcmp(av[i], ";") || !strcmp(av[i], "|")) && i++)	//если тек аргумент ; или | пропускаем этот аргумент
			continue ;
		len = 0;
		while (av[i + len] && strcmp(av[i + len], ";") && strcmp(av[i + len], "|"))	//кол-во аргументов до ; или | или до завершения аргументов
			len++;
		if (!(line = (char **)malloc(sizeof(char *) * (len + 1))))
			exit_fatal();
		line[len] = NULL;
		j = 0;
		while (j < len) {	//запись команды и его аргументов в line
			line[j] = av[i];
			if(!strcmp(av[i], "cd"))
				f_cd = 1;
			j++;
			i++;
		}
		if (av[i] && !strcmp(av[i], "|"))
			f_pipe = 1;
		else
			f_pipe = 0;
		if ((av[i] && !strcmp(av[i], "cd")) || f_cd)
			ft_cd(line);
		if (opened) {
			fds[0] = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (f_pipe) {
			if (pipe(fd))
				exit_fatal();
			fds[1] = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		pid = fork();
		if (pid < 0)
			exit_fatal();
		else if (!pid){
			if(!f_cd)
				if (execve(line[0], line, env))
					error_cannot_exec(line[0]);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
		if (opened) {
			dup2(fds[0], 0);
			close(fds[0]);
			opened = 0;
		}
		if (f_pipe){
			dup2(fds[1], 1);
			close(fds[1]);
			opened = 1;
		}
		f_cd = 0;
		free(line);
	}
	return (0);
}
