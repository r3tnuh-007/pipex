#include "pipex.h"

void	handle_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*dir;
	char	*full_path;
	char	**paths;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (!envp[i])
		return (NULL);

	path = envp[i] + 5;
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
{
        dir = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(dir, cmd);
        free(dir);
        if (access(full_path, X_OK) == 0)
        {
            ft_free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_split(paths);
    return (NULL);
}

void    execute_command(char *cmd, char **envp)
{
    char    **args;
    char    *path;

    args = ft_split(cmd, ' ');
    if (!args)
        handle_error("split error");

    path = find_path(args[0], envp);
    if (!path)
    {
        ft_free_split(args);
        handle_error("command not found");
    }

    if (execve(path, args, envp) == -1)
    {
        free(path);
        ft_free_split(args);
        handle_error("execve error");
    }
}

void    pipex(char **argv, char **envp)
{
    int     fd[2];
    int     infile;
    int     outfile;
    pid_t   pid1;
    pid_t   pid2;

    if (pipe(fd) == -1)
        handle_error("pipe error");

    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
        handle_error("infile error");

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
        handle_error("outfile error");

    pid1 = fork();
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(infile);
        execute_command(argv[2], envp);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(fd[0]);
        close(outfile);
        execute_command(argv[3], envp);
    }

    close(fd[0]);
    close(fd[1]);
    close(infile);
    close(outfile);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char *argv[], char *envp[])
{
    if (argc != 5)
    {
        ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
        return (1);
    }
    pipex(argv, envp);
    return (0);
}
