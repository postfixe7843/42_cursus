# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 15:23:00 by nlence-l          #+#    #+#              #
#    Updated: 2023/06/25 17:52:46 by nlence-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= so_long

CFLAGS 	= -Wall -Wextra -Werror -Iinc

SRC		= so_long.c map.c map2.c move.c read.c check.c check2.c check_path.c \
			check_path2.c

SRCS 	= $(addprefix src/, $(SRC))

OBJ		= $(SRC:.c=.o)

OBJS	= $(addprefix src/, $(OBJ))

all: $(NAME)

%.o: %.c 
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	gcc $(OBJS) -L./libft -lft -lmlx -framework OpenGL -framework AppKit -o $@

clean:
	@$(MAKE) -C libft clean
	rm -rf $(OBJS)
	
fclean:	clean
	@$(MAKE) -C libft fclean
	rm -f $(NAME)
	
re:	fclean all

.PHONY:	all clean fclean re
