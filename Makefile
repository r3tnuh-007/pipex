NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = pipex.h

SRCS = pipex.c\
	   ft_split.c\
	   ft_strjoin.c\
	   ft_strnstr.c\
	   ft_strlen.c\
	   ft_memcmp.c\
	   ft_strdup.c\
	   ft_putstr_fd.c\
	   ft_memcpy.c\
	   ft_free_split.c\
	   handle_error.c\
	   find_path.c\
	   execute_command.c\
	   pipe.c\

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
