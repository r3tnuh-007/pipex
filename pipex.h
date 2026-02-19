/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2026/02/19 20:56:27 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_file
{
	int	fd[2];
	int	infile;
	int	outfile;
	int	status;
}	t_file;

// Funções principais do pipex
void	execute_command(char *cmd, char **envp);
char	*find_path(char *cmd, char **envp);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_free_split(char **strs);
void	handle_exit(int status);
void	handle_error(char *msg, int status);
void	ft_putstr_fd(char *s, int fd);
void	pipex(char **argv, char **envp);
void	ft_free_split(char **strs);
size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
