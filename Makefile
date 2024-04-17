# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 10:22:20 by llitovuo          #+#    #+#              #
#    Updated: 2024/04/17 11:16:35 by aneitenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a
RLHEAD = /Users/${USER}/.brew/Cellar/readline/8.2.10/
RLLIB = /Users/${USER}/.brew/Cellar/readline/8.2.10/include/lib

S = srcs/
O = objs/
I = incl/
L = libft/

all: $(NAME)

bonus: $(BNAME)

libft: $(LIBFT)

.PHONY: all clean fclean re

CC = cc
CFLAGS += -Wall -Wextra -Werror -I$I -I$L -I$(RLHEAD) -L$(RLLIB)
LDFLAGS += 

######################
##		MANDATORY 	##
######################

SRC = \
		$S
		
OBJ = $(SRC:$S%=$O%.o)

$O:
	@mkdir -p $@
	@echo "Making obj dir and files.."

$(OBJ): | $O

$O%.o: $S% $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\033[32;1mCompilation successful!\033[0m"

######################
##		DEBUG		##
######################

DEBUG_NAME = debug.out

debug: $(DEBUG_NAME)

DEBUG_FLAGS = -g -fsanitize=address,undefined,integer

$(DEBUG_NAME): $(OBJ) $(LIBFT)
	@$(CC) $(DEBUG_FLAGS) $(CFLAGS) $^ -o $@
	@echo "Debug ready for use."

cleandebug: fclean
	@rm -f $(DEBUG_NAME)
	@echo "debug.out removed"

######################
##		LIBFT		##
######################

$(LIBFT): $L
	@make -C $L

cleanobj:
	@rm -f $(wildcard $(OBJ))

cleanobjdir: cleanobj
	@rm -rf $O

cleanlibft:
	@make fclean -C $L

clean: cleanobjdir cleanlibft
	@echo "\033[32;1mCleaned files\033[0m"

fclean: clean
	@rm -f $(NAME) $(BNAME)
	@echo "\033[32;1mRemoved program!\033[0m"

re: fclean all