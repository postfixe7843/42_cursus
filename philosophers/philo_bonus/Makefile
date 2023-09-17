NAME 	= bonus

CFLAGS 	= -g -Wall -Wextra -Werror -I inc

SRC		= main_bonus.c utils_bonus.c init_bonus.c

SRCS 	= $(addprefix src/, $(SRC))

OBJ		= $(SRC:.c=.o)

OBJS	= $(addprefix src/, $(OBJ))

all: $(NAME)

%.o: %.c 
	gcc $(CFLAGS) -pthread -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -pthread -o philo_bonus

clean:
	rm -rf $(OBJS)
	
fclean:	clean
	rm -f philo_bonus
	
re:	fclean all

.PHONY:	all clean fclean re


