# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 10:22:20 by llitovuo          #+#    #+#              #
#    Updated: 2024/05/11 18:54:38 by aneitenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft

LIBFT = ./libft/libft.a

RLHEAD = /Users/${USER}/.brew/Cellar/readline/8.2.10/include
RLLIB = /Users/${USER}/.brew/Cellar/readline/8.2.10/lib

SOURCES = \
			srcs/main.c \
      		srcs/parsing/parse.c \
			srcs/parsing/scan_utils.c \
			srcs/parsing/scan_utils2.c \
			srcs/parsing/split.c \
			srcs/parsing/split_quotes.c \
			srcs/parsing/split_redirects.c \
			srcs/parsing/split_utils.c \
			srcs/builtins/builtin_functions.c \
			srcs/builtins/builtins.c \
			srcs/builtins/ft_export.c \
			srcs/builtins/ft_export_utils.c \
			srcs/builtins/builtin_utils.c \
			srcs/builtins/ft_echo.c \
			srcs/builtins/ft_cd.c \
			srcs/builtins/cd_utils.c \
			srcs/builtins/cd_utils2.c \
      		srcs/errors.c
			
OBJECTS = $(SOURCES:.c=.o)

CFLAGS =  -Wall -Wextra -Werror -I$(RLHEAD) #-g  -fsanitize=address
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