# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 17:20:19 by nlence-l          #+#    #+#              #
#    Updated: 2022/12/13 20:10:47 by nlence-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

CFLAGS 		= -Wall -Wextra -Werror -Iinc

SRC_GNL 	= get_next_line.c get_next_line_utils.c

SRC_PRINTF 	= ft_parser.c ft_print_char.c ft_print_hex.c ft_print_nbr.c \
				ft_print_percent.c ft_print_ptr.c ft_print_str.c ft_print_u.c \
				ft_printf.c

SRC			= $(addprefix gnl/, $(SRC_GNL)) $(addprefix printf/, $(SRC_PRINTF)) \
			ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
			ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
			ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
			ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
			ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c \
			ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiteri.c ft_lstlast.c ft_lstnew.c ft_lstsize.c

SRCS 		= $(addprefix src/, $(SRC))

OBJ			= $(SRC:.c=.o)

OBJS		= $(addprefix src/, $(OBJ))

AR  		= ar rcs

all: $(NAME)

%.o: %.c 
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^
	ranlib $(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	@fclean all

.PHONY:	all clean fclean re
