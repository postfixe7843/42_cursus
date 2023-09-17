NAME	= push_swap
SRCS = algorithms.c algorithms2.c checkers.c main.c push_swap_functions.c \
		push_swap_functions2.c push_swap_functions3.c stack_functionns.c \
		utils.c utils2.c utils3.c checkers2.c
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(addprefix ./src/,$(SRCS)) -o push_swap

clean:
	@rm -f push_swap

fclean: clean
	
re: 	fclean all

.PHONY:	all clean fclean re
