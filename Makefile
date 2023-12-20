NAME = ft_ls
CC = clang
INC = ft_ls.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

SRCS	=	main.c

OBJS = $(SRCS:.c=.o)

.c.o:
		clang ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

po:		all clean

re:		fclean all

.PHONY:	all clean fclean re