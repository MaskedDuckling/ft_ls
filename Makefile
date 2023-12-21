NAME = ft_ls
CC = clang
INC = main.h
CFLAGS = -fsanitize=address
# -Wall -Werror -Wextra 

SRCS	=	main.c beautiful.c libft.c

OBJS = $(SRCS:.c=.o)

.c.o:
		clang ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

po:		all clean

re:		fclean all

.PHONY:	all clean fclean re