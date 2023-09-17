/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:19:57 by nlence-l          #+#    #+#             */
/*   Updated: 2022/12/15 19:43:32 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>

# define BUFFER_SIZE 5

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* ---------------	LISTS		--------------- */

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ---------------	CHARS		--------------- */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* ---------------	STRINGS		--------------- */
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* ---------------   FILE DESCRIPTORS   --------------- */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* ---------------	MEMORY		--------------- */
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* ---------------	NUMBERS		--------------- */
int		ft_atoi(char *str);
char	*ft_itoa(int n);

/* ---------------	GNL	        	 --------------- */

char	*get_next_line(int fd);
char	*ft_read(int fd, char *s1);
char	*ft_get_line(char *s1);
char	*ft_parse(char *s1);

/* ---------------	PRINTF		--------------- */

int		ft_printf(const char *format, ...);
int		ft_parser(va_list args, char c);
int		ft_print_char(const char c);
int		ft_print_hex(unsigned int n, const char c);
int		ft_get_hex(unsigned int n, const char c);
int		ft_hex_len(unsigned	int n);
int		ft_print_nbr(int n);
int		ft_nbrlen(int n);
int		ft_print_percent(void);
int		ft_print_str(char *str);
int		ft_print_u(unsigned int n);
int		ft_print_ptr(unsigned long long n);
void	ft_get_ptr(unsigned long long n);
int		ft_ptr_len(unsigned long long n);
int		ft_ulen(unsigned int n);

#endif
