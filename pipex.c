/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2026/02/19 21:07:14 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)	argc;
	t_file	file;
	pid_t	pid;
	char	**cmd;
	int		i;
	int		saved_stdin;
	int		saved_stdout;
	/*if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}*/
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	i = 0;
	cmd = ft_split(argv[1], '|');
	if (pipe(file.fd) == -1)
		handle_error("pipe error", EXIT_FAILURE);

	while (cmd[i])
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd[i + 1] == NULL)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				execute_command(cmd[i], envp);
			}
			else if (i == 0)
			{
				dup2(saved_stdin, STDIN_FILENO);
				dup2(file.fd[1], STDOUT_FILENO);
				close(file.fd[0]);
				close(file.fd[1]);
				execute_command(cmd[i], envp);
			}
			else
			{
				dup2(file.fd[0], STDIN_FILENO);
				dup2(file.fd[1], STDOUT_FILENO);
				close(file.fd[0]);
				close(file.fd[1]);
				execute_command(cmd[i], envp);
			}
		}
		//printf("cmd: %s\n", cmd[i]);
		waitpid(pid, &file.status, 0);
		i ++;
	}
	handle_exit(file.status);
	close(file.fd[0]);
	close(file.fd[1]);
	ft_free_split(cmd);
	//pipex(argv, envp);
	return (0);
}
