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

NAME 		=	libft.a

CFLAGS 		=	-Wall -Wextra -Werror -Iinc

SRC			=	ft_isalnum.c \
				ft_isprint.c \
				ft_memcmp.c  \
				ft_putchar_fd.c \
				ft_split.c \
				ft_strlcat.c \
				ft_strncmp.c \
				ft_substr.c \
				ft_atoi.c ft_isalpha.c \
				ft_itoa.c \
				ft_memcpy.c  \
				ft_putendl_fd.c \
				ft_strchr.c  \
				ft_strlcpy.c \
				ft_strnstr.c \
				ft_tolower.c \
				ft_bzero.c  \
				ft_isascii.c \
				ft_memmove.c \
				ft_putnbr_fd.c \
				ft_strdup.c \
				ft_strlen.c \
				ft_strrchr.c \
				ft_toupper.c \
				ft_calloc.c \
				ft_isdigit.c \
				ft_memchr.c \
				ft_memset.c \
				ft_putstr_fd.c \
				ft_strjoin.c \
				ft_strmapi.c \
				ft_strtrim.c\
				ft_striteri.c \
			
SRC_BONUS	=	ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiteri_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstmap_bonus.c \

SRCS 		= $(addprefix src/, $(SRC))

SRCS_BONUS	= $(addprefix src/, $(SRC_BONUS))

OBJ			= $(SRC:.c=.o)

OBJ_BONUS	= $(SRC_BONUS:.c=.o)

OBJS		= $(addprefix src/, $(OBJ))

OBJS_BONUS	= $(addprefix src/, $(OBJ_BONUS))

AR  		= ar rcs

all: $(NAME)

%.o: %.c 
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^
	ranlib $(NAME)

bonus: $(OBJS_BONUS)
	$(AR) libft.a $^
	ranlib $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
