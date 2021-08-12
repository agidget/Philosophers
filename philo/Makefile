  
NAME	= philo
CC		= gcc
HEADER	= philo.h
SRCS	= *.c
RM		= rm -rf
CFLAGS	= -Wall -Werror -Wextra
OBJS	= *.o

all:	${NAME}

$(NAME): $(SRCS) $(HEADER)
		$(CC) $(CFLAGS) -c $(SRCS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${NAME}
re:		fclean all
.PHONY:	all clean fclean re