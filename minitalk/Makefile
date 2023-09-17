NAME = minitalk
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinc

all: $(NAME)

$(NAME):
	$(MAKE) -s -C ./libft
	$(CC) $(CFLAGS) src/client.c -o client -L./libft -lft
	$(CC) $(CFLAGS) src/server.c -o server -L./libft -lft

clean:
	$(MAKE) -s clean -C ./libft

fclean:
	rm -f client server
	$(MAKE) -s fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re


