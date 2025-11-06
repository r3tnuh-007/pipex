/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2025/11/06 05:07:57 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	if (cmd == NULL || *cmd == '\0')
		handle_error("command is NULL", 127);
	args = ft_split(cmd, ' ');
	if (!args)
		handle_error("split error", EXIT_FAILURE);
	path = find_path(args[0], envp);
	if (!path)
	{
		ft_free_split(args);
		handle_error("command not found", 127);
	}
	if (execve(path, args, envp) == -1)
	{
		free(path);
		ft_free_split(args);
		handle_error("execve error", EXIT_FAILURE);
	}
}
