NAME = cub3d

SRC =	main.c event_handl.c graphics_init.c parser/parser.c parser/pars_dims.c parser/pars_utils.c parser/file.c\
		validation/map.c validation/map_valid.c validation/map_utils.c\
		utils/delete_memory.c\
		gnl/get_next_line.c gnl/get_next_line_utils.c

SRC_LIB	=	libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c\
			libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isspace.c libft/ft_itoa.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strmapi.c libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strrev.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_strlen.c
OBJ		=	$(SRC:.c=.o)
LIBDIR	=	./libft
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-g -Wall -Wextra -Werror
LFLAGS	=	-L $(LIBDIR) -lft -lmlx -framework OpenGL -framework AppKit
HEADER	=	cub3d.h gnl/get_next_line.h

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(LIB)	:
			make -s -C $(LIBDIR)

$(NAME)	:	$(OBJ)  Makefile
			$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)

%.o		:	%.c $(HEADER) $(LIB)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)
			make clean -C $(LIBDIR)

fclean	:	clean
			make fclean -C $(LIBDIR)
			rm -f $(NAME)

re		:	fclean all