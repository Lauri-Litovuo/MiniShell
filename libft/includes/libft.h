/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidaneitenbach <aidaneitenbach@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:52:13 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/19 22:24:06 by aidaneitenb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/*******************************/
/*       libft struct          */
/*******************************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*******************************/
/*     split_quote struct      */
/*******************************/

typedef struct s_split
{
	char	**array;
	int		i;
	int		j;
	int		k;
	int		wc;
}			t_split;

/*******************************/
/*     vec_lib struct      */
/*******************************/
typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}		t_vec;

/*******************************/
/*       libft functions       */
/*******************************/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *s1, char *s2, int len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);	
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsjoin(char const *s1, char const *s2, char sep);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	**ft_split_quote(char *str);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*******************************/
/*       printf functions      */
/*******************************/
int		ft_printf(const char *format, ...);
int		ft_putchar(char c, int *check);
int		ft_putstr(char *str, int *check);
int		ft_putnbr(int num, int *check);
int		ft_puthexbase(unsigned long num, int cap, int *check);
int		ft_putun(unsigned int num, int *check);
int		ft_putptr(void *ptr, int *check);

/*******************************/
/*   get_next_line functions   */
/*******************************/
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *string, char *buffer);
char	*ft_free_gnl(char *string);

/*******************************/
/*   	vec_lib functions 	   */
/*******************************/
int		vec_new(t_vec *dst, size_t init_len, size_t elem_size);
void	vec_free(t_vec *src);
int		vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
int		vec_resize(t_vec *src, size_t target_len);
int		vec_push(t_vec *src, void *elem);
int		vec_pop(void *dst, t_vec *src);
int		vec_copy(t_vec *dst, t_vec *src);
void	*vec_get(t_vec *src, size_t index);
int		vec_insert(t_vec *dst, void *elem, size_t index);
int		vec_remove(t_vec *src, size_t index);
int		vec_append(t_vec *dst, t_vec *src);
int		vec_prepend(t_vec *dst, t_vec *src);
void	vec_iter(t_vec *src, void (*f) (void *));
void	vec_free_str(t_vec *src);
int		vec_remove_str(t_vec *src, size_t index);
int		vec_replace_one(t_vec *dst, void *src, size_t index); //change
int		vec_replace_str(t_vec *dst, void *src, size_t index);
void	vec_sort_alpha(t_vec *src);
int		vec_copy_len(t_vec *dst, t_vec *src);

#endif
