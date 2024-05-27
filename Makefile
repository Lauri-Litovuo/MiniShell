# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 10:22:20 by llitovuo          #+#    #+#              #
#    Updated: 2024/05/27 11:11:08 by llitovuo         ###   ########.fr        #
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
			srcs/parsing/redirect_utils.c \
			srcs/parsing/redirect_utils2.c \
			srcs/parsing/split_utils.c \
			srcs/parsing/vec_join.c \
			srcs/parsing/vec_utils.c \
     		srcs/errors/errors.c \
			srcs/execute/add_builtin.c \
			srcs/utils/expand_variables.c \
			srcs/utils/expand_variables_utils.c \
			srcs/execute/execute.c \
			srcs/execute/setup_exe.c \
			srcs/execute/open_files.c \
			srcs/execute/get_exec_path.c \
			srcs/execute/heredoc.c \
			srcs/errors/debug.c \
			srcs/errors/ft_fprintf.c \
			# srcs/builtins/builtin_functions.c \
			# srcs/builtins/builtins.c \
			# srcs/builtins/ft_export.c \
			# srcs/builtins/ft_export_utils.c \
			# srcs/builtins/builtin_utils.c \
			# srcs/builtins/ft_echo.c \
			# srcs/builtins/ft_cd.c \
			# srcs/builtins/cd_utils.c \
			# srcs/builtins/cd_utils2.c \

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