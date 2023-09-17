NAME 	= philo

CFLAGS 	= -g -Wall -Wextra -Werror -I inc

SRC		= main.c utils.c init.c threads.c routines.c

SRCS 	= $(addprefix src/, $(SRC))

OBJ		= $(SRC:.c=.o)

OBJS	= $(addprefix src/, $(OBJ))

all: $(NAME)

%.o: %.c 
	gcc $(CFLAGS) -pthread -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -pthread -o $@

clean:
	rm -rf $(OBJS)
	
fclean:	clean
	rm -f $(NAME)
	
re:	fclean all

.PHONY:	all clean fclean re


