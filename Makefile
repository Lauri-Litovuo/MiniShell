# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 10:22:20 by llitovuo          #+#    #+#              #
#    Updated: 2024/04/24 10:32:52 by llitovuo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft

LIBFT = ./libft/libft.a

RLHEAD = /Users/${USER}/.brew/Cellar/readline/8.2.10/include
RLLIB = /Users/${USER}/.brew/Cellar/readline/8.2.10/lib

SOURCES = \
			srcs/main.c \
			srcs/parsing.c \
			srcs/builtins/builtin_functions.c \
			srcs/builtins/builtins.c \
			srcs/builtins/ft_export.c \
			srcs/builtins/builtin_utils.c \
			srcs/builtins/ft_echo.c \
			
OBJECTS = $(SOURCES:.c=.o)

CFLAGS =  -g -Wall -Wextra -Werror -I$(RLHEAD)
RLFLAGS = -lreadline -L$(RLLIB) 
CC = cc

all: $(LIBFT) $(NAME) 

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(RLFLAGS)
	@echo "\033[32;1mCompilation successful!\033[0m"

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJECTS)
	@echo "\033[32;1mCleaned files\033[0m"
	
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "\033[32;1mRemoved program!\033[0m"

re: fclean all

.PHONY: all clean fclean re