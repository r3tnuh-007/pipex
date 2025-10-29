#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

// Funções principais
void	execute_command(char *cmd, char **envp);
char	*find_path(char *cmd, char **envp);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_free_split(char **strs);
void	handle_error(char *msg);
void	ft_putstr_fd(char *s, int fd);
void	pipex(char **argv, char **envp);
void	ft_free_split(char **strs);
size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
