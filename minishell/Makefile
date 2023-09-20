# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 16:18:51 by jschmitt          #+#    #+#              #
#    Updated: 2023/09/19 18:40:27 by jschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./src/main.c \
		./src/exec/pipeline.c \
		./src/exec/pipeline2.c \
		./src/exec/pipeline3.c \
		./src/exec/pipeline4.c \
		./src/exec/executor.c \
		./src/exec/executor2.c \
		./src/exec/signal.c \
 		./src/exec/exec_builtins.c \
		./src/exec/redir.c \
		./src/exec/redir_utils.c \
		./src/exec/heredoc.c \
		./src/exec/heredoc_utils.c \
		./src/exec/heredoc_expand.c \
		./src/exec/heredoc_filling.c \
		./src/exec/free.c \
		./src/exec/free_utils.c \
		./src/parsing/lexer.c \
		./src/parsing/lexer_utils.c \
		./src/parsing/lexer_utils2.c \
		./src/parsing/lexer_utils3.c \
		./src/parsing/lexer_utils4.c \
		./src/parsing/parser.c\
		./src/parsing/parser_utils.c\
		./src/parsing/parser_utils2.c\
		./src/parsing/parser_utils3.c\
		./src/parsing/parser_utils4.c\
 		./src/parsing/expander.c \
 		./src/parsing/expander_utils.c \
 		./src/parsing/expander_utils2.c \
 		./src/parsing/expander_utils3.c \
 		./src/parsing/expander_utils4.c \
 		./src/parsing/handle_quotes.c \
 		./src/builtins/echo.c \
		./src/builtins/pwd.c \
		./src/builtins/cd.c \
		./src/builtins/env.c \
		./src/builtins/setenv.c \
		./src/builtins/export.c \
		./src/builtins/export_no_arg.c \
		./src/builtins/unset.c \
		./src/builtins/exit.c \
		./src/builtins/errors.c \
		./src/builtins/msg_error.c \
		./src/builtins/ft_atol.c \
		./src/builtins/ft_strcmp.c \
	
OBJ = $(SRC:.c=.o)

LIBFT = ./libft

INC = -I. -I$(LIBFT) -I /Users/$$USER/.brew/opt/readline/include

CC = gcc $(FLAGS) $(INC)

FLAGS = -Wall -Wextra -Werror -g

all: libft $(NAME)

libft:
	make -C $(LIBFT)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

$(NAME): $(SRC) $(OBJ)
	make -C $(LIBFT)
	$(CC) $(OBJ) $(LIBFT)/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -o $(NAME) 
