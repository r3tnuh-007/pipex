/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2026/02/21 18:53:02 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i ++;
	return (i);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)	argc;

	t_file	file_t;
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
	int cmd_count = count_cmd(cmd);
	int file[cmd_count][2];
	pid_t	pid[cmd_count];
	for (int j = 0; j < cmd_count; j++)
	{
		if (pipe(file[j]) == -1)
			handle_error("pipe error", EXIT_FAILURE);
	}
	while (cmd[i])
	{
		printf("cmd: %s\n", cmd[i]);
		i ++;
	}
	i = 0;
	while (cmd[i] != NULL)
	{
			pid[i] = fork();
			if (pid[i] == -1)
				handle_error("fork error", EXIT_FAILURE);
			if (pid[i] == 0)
			{
				if (cmd[i + 1] == NULL)
				{
					if (i == 0)
						dup2(saved_stdin, STDIN_FILENO);
					else
					{
						dup2(file[i - 1][0], STDIN_FILENO);
						dup2(saved_stdout, STDOUT_FILENO);
					}
					execute_command(cmd[i], envp);
				}
				else if (i == 0)
				{
					dup2(saved_stdin, STDIN_FILENO);
					dup2(file[i][1], STDOUT_FILENO);
					execute_command(cmd[i], envp);
				}
				else
				{
					dup2(file[i - 1][0], STDIN_FILENO);
					dup2(file[i][1], STDOUT_FILENO);
					execute_command(cmd[i], envp);
				}
				//printf("cmd: %s\n", cmd[i]);
			}
			else
			{
				if (i > 0)
					close(file[i - 1][0]);
				if (cmd[i + 1] != NULL)
					close(file[i][1]);
			}

		i ++;
	}
	for (int j = 0; j < cmd_count; j++)
	{
		close(file[j][0]);
		close(file[j][1]);
	}
	//printf("esperando os filhos terminarem...\n");
	waitpid(pid[i - 1], &file_t.status, 0);
	printf("status: %d\n", file_t.status);
	handle_exit(file_t.status);
	//close(file.fd[0]);
	//close(file.fd[1]);
	ft_free_split(cmd);
	//pipex(argv, envp);
	return (0);
}
