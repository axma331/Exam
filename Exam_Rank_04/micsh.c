#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(const char *str) {
	int i = 0;
	while(str[i])
		i++;
	return i;
}

void ft_error(char *str, int cd) {
    if (!str && cd < 0)
        write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
    else {
        if (cd)
            write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
        else
            write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
}

void exit_fatal(void) {
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit(1);
}

void ft_cd(char **line) {
	int i = 0;
	while(line[i])
		i++;
	if (i != 2)
	{
		ft_error(NULL, -1);
		return;
	}
	if (chdir(line[1]))
		ft_error(line[1], 1);
}

int main(int ac, char **av, char **env) {
	int i = 1;		//номер аргумента
	int len, m, is_pipe;	//длина line; вспомог счетчик; flag for |
	char **line = NULL;		//аргументы без ; и | (т.е. это одна команда и его аргументы)
	int fd[2], s_fd[2];
	int opened = 0;
	int status = 0;	//for waitpid()
	int flag = 0;	//for cd
	pid_t pid;

	while (ac > 1 && i < ac) {
		if ((!strcmp(av[i], ";") || !strcmp(av[i], "|")) && i++)		//если тек аргумент ; или | пропускаем этот аргумент
			continue;
		len = 0;
		while (av[i + len] && strcmp(av[i + len], ";") != 0 && strcmp(av[i + len], "|") != 0)	//кол-во аргументов до ; или | или до завершения аргументов
			len++;
		if (!(line = (char **)malloc(sizeof(char *) * (len + 1))))
			exit_fatal();
		line[len] = NULL;
		m = 0;
		while (m < len) {		//запись команды и его аргументов в line
			line[m++] = av[i];
			if(!strcmp(av[i++], "cd"))
				flag = 1;
		}
		if (av[i] && !strcmp(av[i], "|"))
			is_pipe = 1;
		else
			is_pipe = 0;
		if ((av[i] && !strcmp(av[i], "cd")) || flag)
			ft_cd(line);
		if (opened){
			s_fd[0] = dup(0);   	// создаем копию stdin s_fd[0] = stdin
			dup2(fd[0], 0);     // stdin = fd[0] (stdin стал копией f[0])
			close(fd[0]);
		}
		if (is_pipe){
			if (pipe(fd))
				exit_fatal();
			s_fd[1] = dup(1);		// создаем копию stdout s_fd[1] = stdout
			dup2(fd[1], 1);		// stdout = fd[1] (stdout стал копией fd[1])
			close(fd[1]);
		}
		pid = fork();
		if (pid < 0)
			exit_fatal();
		else if (!pid) {
			if(!flag)
				if (execve(line[0], line, env))
					ft_error(line[0], 0);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
		if (opened){
			dup2(s_fd[0], 0);
			close(s_fd[0]);
			opened = 0;
		}
		if (is_pipe){
			dup2(s_fd[1], 1);
			close(s_fd[1]);
			opened = 1;
		}
		flag = 0;
		free(line);
	}
	return 0;
}
