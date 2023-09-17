NAME	= libft.a

SRC		= ft_printf.c ft_parser.c ft_print_char.c ft_print_hex.c ft_print_nbr.c ft_print_percent.c \
		  ft_print_str.c ft_print_u.c ft_print_ptr.c

SRCS 	= $(addprefix src/, $(SRC))

OBJ		= $(SRC:.c=.o) 

OBJS 	= $(addprefix src/, $(OBJ))

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -Iinc

AR		= ar rcs

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re






