NAME = libft.a

SOURCES =  libft/ft_isdigit.c \
		   libft/ft_split.c \
		   libft/ft_split_quote.c \
		   libft/ft_strmapi.c \
		   libft/ft_striteri.c \
		   libft/ft_itoa.c \
		   libft/ft_strtrim.c \
		   libft/ft_strjoin.c \
		   libft/ft_strsjoin.c \
		   libft/ft_substr.c \
		   libft/ft_putnbr_fd.c \
		   libft/ft_putendl_fd.c \
		   libft/ft_putstr_fd.c \
		   libft/ft_putchar_fd.c \
		   libft/ft_isalpha.c \
		   libft/ft_calloc.c \
		   libft/ft_strdup.c \
		   libft/ft_atoi.c \
		   libft/ft_isalnum.c \
		   libft/ft_isascii.c \
		   libft/ft_isprint.c \
		   libft/ft_memset.c \
		   libft/ft_bzero.c \
		   libft/ft_memcpy.c \
		   libft/ft_memmove.c \
		   libft/ft_toupper.c \
		   libft/ft_tolower.c \
		   libft/ft_strlen.c \
		   libft/ft_strchr.c \
		   libft/ft_strrchr.c \
		   libft/ft_strncmp.c \
		   libft/ft_strncpy.c \
		   libft/ft_memchr.c \
		   libft/ft_memcmp.c \
		   libft/ft_strlcpy.c\
		   libft/ft_strlcat.c \
		   libft/ft_strnstr.c \
		   printf/ft_printf.c \
		   printf/ft_putchar.c \
		   printf/ft_putstr.c \
		   printf/ft_putnbr.c \
		   printf/ft_puthexbase.c \
		   printf/ft_putun.c \
		   printf/ft_putptr.c \
		   gnl/get_next_line.c \
		   gnl/get_next_line_utils.c \
		   vec_lib/vec_append.c \
		   vec_lib/vec_copy.c \
		   vec_lib/vec_free.c \
		   vec_lib/vec_from.c \
		   vec_lib/vec_get.c \
		   vec_lib/vec_insert.c \
		   vec_lib/vec_iter.c \
		   vec_lib/vec_new.c \
		   vec_lib/vec_pop.c \
		   vec_lib/vec_prepend.c \
		   vec_lib/vec_push.c \
		   vec_lib/vec_remove.c \
		   vec_lib/vec_resize.c \
		   vec_lib/vec_free_str.c \
		   vec_lib/vec_replace_str.c \
		   vec_lib/vec_remove_str.c \
		   vec_lib/vec_alpha_sort.c \
		   vec_lib/vec_copy_len.c
		  	 
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

CC = @cc

all: $(NAME)

$(NAME): $(OBJECTS) 
	@ar -cr $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean re all fclean
