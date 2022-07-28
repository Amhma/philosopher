NAME	= philo
CC		= gcc
CFLAGS	= -g3 -Wall -Werror -Wextra -pthread
SRC		=  philo.c philo_2.c write.c utils.c parse.c action.c action_2.c action_3.c
OBJ		= $(SRC:.c=.o)
INC		= -I.
RM		= rm -f

all		: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBFT)

.c.o	:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY	: all clean fclean re

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re		: fclean
	make all
