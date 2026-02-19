/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2026/02/19 19:28:42 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_pipe(t_file file, char **argv, char **envp, pid_t pid)
{
	if (pid == 1)
	{
		close(file.fd[0]);
		dup2(file.infile, STDIN_FILENO);
		dup2(file.fd[1], STDOUT_FILENO);
		close(file.fd[1]);
		close(file.infile);
		execute_command(argv[2], envp);
	}
	else if (pid == 2)
	{
		close(file.fd[1]);
		dup2(file.fd[0], STDIN_FILENO);
		dup2(file.outfile, STDOUT_FILENO);
		close(file.fd[0]);
		close(file.outfile);
		execute_command(argv[3], envp);
	}
}

static void	handle_exit(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
}

void	pipex(char **argv, char **envp)
{
	t_file	file;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(file.fd) == -1)
		handle_error("pipe error", EXIT_FAILURE);
	file.infile = open(argv[1], O_RDONLY);
	if (file.infile == -1)
		file.infile = 0;
	file.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file.outfile == -1)
		handle_error("outfile error", EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
		handle_pipe(file, argv, envp, 1);
	pid2 = fork();
	if (pid2 == 0)
		handle_pipe(file, argv, envp, 2);
	close(file.fd[0]);
	close(file.fd[1]);
	close(file.infile);
	close(file.outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &file.status, 0);
	handle_exit(file.status);
}
