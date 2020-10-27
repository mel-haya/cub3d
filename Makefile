# -*- Makefile -*-

NAME = cub3D
FLAGS = -Wall -Werror -Wextra -O3 -g
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SRC1 = $(addprefix libft/,$(SRC))
SRC2 = GNL/get_next_line_utils.c GNL/get_next_line.c
SRC3 = sprite.c math_functions.c file_functions.c check_functions.c file_functions_norm.c string_functions.c events.c screenshot.c rays.c walls.c main.c
O = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(MAKE) -C libft/
	gcc $(SRC3) $(SRC2) -lmlx libft/libft.a -framework appkit -framework opengl $(FLAGS) -o $(NAME)

clean:
	$(MAKE) -C libft/ fclean

fclean: clean
	rm cub3D

re:	fclean all
