// v.1
#include <stdio.h>
#include <unistd.h> //pipe fork
#include <sys/types.h> //fork
#include <sys/wait.h> //wait
#include <string.h> //strcmp
#include <stdlib.h> //exit
int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}
void print_str_arr(char **arr)
{
	while (*arr)
	{
		printf("|%s", *arr);
		arr++;
	}	
	printf("\n");
}
void connect_to_pps(int prev[], int next[])
{
	if (prev[0] != -1)
	{
		dup2(prev[0], 0);
		close(prev[0]);
		close(prev[1]);
	}
	if (next[1] != -1)
	{
		dup2(next[1], 1);
		close(next[1]);
		close(next[0]);
	}
}
int get_next_cmd(char ***cmd, char *end_tok, int start_pos, char **av)
{
    int i = 0;
    av+= start_pos;
    while(av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
        i++;
    *end_tok = av[i] ? *av[i] : '\0';
	av[i] = 0;
	*cmd = av;
	return i;
}
int ft_cd(char **cmd)
{
	int ac = 0;
	int r;
	while (cmd[ac])
		ac++;
	if (ac != 2)
	{
		write(2, "error: cd: bad arguments\n", 25);
		return (1);
	}
	if ((r = chdir(cmd[1])) < 0)
	{
		write(2, "error: cd: cannot change directory to ", 38);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, "\n", 1);
		return (r);
	}
	return (r);
}
int g_exit_code = 0;
int main(int ac, char **av, char **env)
{
	(void)ac;
	char **cmd;
	char end_tok = ';';
	int cmd_pos = 1;
	int prev_pipe[2];
	int next_pipe[2];
	int res;
	
	next_pipe[0] = -1;
	next_pipe[1] = -1;
	while (end_tok != '\0' || (end_tok == ';' && av[cmd_pos] != 0))
	{
		cmd_pos = cmd_pos + get_next_cmd(&cmd, &end_tok,cmd_pos, av) + 1;
		if (!cmd[0])
			continue ;
		prev_pipe[0] = next_pipe[0];	
		prev_pipe[1] = next_pipe[1];	
		if (end_tok == '|')
			pipe(next_pipe);
		else
		{
			next_pipe[0] = -1;
			next_pipe[1] = -1;
		}
		close(prev_pipe[1]);
		if (!(strcmp(cmd[0], "cd")))
			g_exit_code = ft_cd(cmd);
		else
		{
			if (fork() == 0)
			{
				connect_to_pps(prev_pipe, next_pipe);
				res = execve(cmd[0],cmd, env);
				write(2, "error: cannot execute ", 22);
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, "\n", 1);
				exit(res);
			}
			
			waitpid(-1, &res, 0);		
			if (WIFEXITED(res))
				g_exit_code = WEXITSTATUS(res);	
		}
		close(prev_pipe[0]);
	}
	return (g_exit_code);
}


// v.2
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int len(const char *str)
{
    int i = -1;
    while (str[++i]);
    return (i);
}
void end(char **av, int *i)
{
    for (; av[*i] && strcmp(av[*i], ";") && strcmp(av[*i], "|"); (*i)++);
}
void err(char *err, char *arg, int fail)
{
    write(2, err, len(err)) && arg && write(2, arg, len(arg));
    write(2, "\n", 1) && fail ? exit(1) : 0;
}
void cd(char **av, int *i)
{
    int n = *i;
    end(av, i);
    if (n + 2 != *i)
        err("error: cd: bad arguments", 0,0);
    else if (chdir(av[n + 1]) == -1)
        err("error: cd: cannot change directory to ", av[n + 1], 0);
}
int exec(char **av, char **env, int *i, int *prev)
{
    int io[2] = {0,1};
    int fdp[2] = {0,1};
    int n = *i;
    end(av, i);
    int isp = (av[*i] && !strcmp(av[*i], "|"));
    int isEnd = (!av[*i] || !strcmp(av[*i], ";"));
    if (isp && pipe(fdp) == -1)
        err("error: fatal", 0 , 1);
    av[*i] = 0x0;
    io[0] = *prev;
    io[1] = fdp[1];
    *prev = fdp[0];
    int pid = fork();
    if (!pid)
    {
        if ((io[0] && dup2(io[0], 0) == -1)
        || (io[1] != 1 && dup2(io[1], 1) == -1)
        ||(io[0] && close(io[0]) == -1)
        ||(io[1] != 1 && close(io[1]) == -1)
        || (isp && close(fdp[0]) == -1))
            err("error: fatal", 0 , 1);
        if (execve(av[n], av + n, env) == -1)
            err("error: cannot execute ", av[n], 1);
    }
    else if (pid == -1)
        err("error: fatal", 0 , 1);
    if ((io[0] && close(io[0]) == -1)
        ||(io[1] != 1 && close(io[1]) == -1))
        err("error: fatal", 0 , 1);
    return isEnd;
}
int main(int ac, char **av, char **env)
{
    int cmd = 0;
    int prev = 0;
    for (int i = 1; i < ac; ++i)
    {
        if (!strcmp(av[i], ";"))
            continue ;
        if (!strcmp(av[i], "cd"))
            cd(av, &i);
        else
        {
            int res = exec(av, env, &i, &prev);
            cmd++;
            if (res)
            {
                for (int j = 0; j < cmd; ++j) {
                    if (waitpid(-1, 0, 0) == -1)
                        err("error: fatal", 0 , 1);
                }
                cmd = 0;
            }
        }
    }
    for (int j = 0; j < cmd; ++j)
        if (waitpid(-1, 0, 0) == -1)
            err("error: fatal", 0 , 1);
    return 0;
}