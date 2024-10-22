/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:49:51 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/22 10:30:54 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>

//----------------------GNL STUFF---------------//
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024
//----------------------------------------------//

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nitems, size_t size);
void		*ft_memchr(const void *str, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *s1, const void *s2, size_t n);
void		*ft_memset(void *str, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_strncpy(char *dst, const char *src, int n);

int			ft_atoi(const char *str);
int			ft_str_isalpha(char *str);
int			ft_isalnum(int c);
int			ft_isalnum_under(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
size_t		ft_strlen(char const *str);
size_t		ft_arrlen(char **arr);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_find_c(char c, char const *set);
int			ft_strclen(char *str, char c);
int			ft_isspace(char c);
int			ft_count_char(char *str, char sep, int n);
int			ft_isdigitloop(char *str);

char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *s);
char		*ft_strnstr(const char *origin, const char *find, size_t n);
char		*ft_strrchr(const char *str, int c);
char		*ft_itoa(int n);
char		**ft_split(char const *str, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_str1dup(char *s, int len);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strjoin_free(char *s1, char *s2, int to_free);

void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));

int			ft_lstsize(t_list *lst);

long long	ft_atoll(const char *str);

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//---------------------------------GNL---------------------//

char		*ft_strndup(char *s, int len);
char		*free_data(char *stash, char *buffer);
char		*read_from_file(int fd, char *stash);
char		*leftovers(char *stash);
char		*get_next_line(int fd);

int			ft_strclen(char *str, char c);
char		*gnl_ft_strchr(char *str, char c);
char		*gnl_ft_strjoin(char *s1, char *s2);

//-----------------------------FT PRINTF-------------------//

int			ft_printf(const char *str, ...);
int			ft_putchar(char c);
int			ft_putnbrhex(unsigned int nbr, const char c);
int			ft_putptr(void *nbr);
int			ft_uitoa(unsigned int nbr);
void		ft_putstr(char *str);
int			ft_printstr(char *str);
int			ft_printnbr(int n);
int			ft_printpercent(void);

//-----------------------------FT PRINTF_FD-------------------//

int			ft_printf_fd(int fd, const char *str, ...);
int			ft_printchar_fd(char c, int fd);
int			ft_putnbrhex_fd(unsigned int nbr, const char c, int fd);
int			ft_putptr_fd(void *nbr, int fd);
int			ft_uitoa_fd(unsigned int nbr, int fd);
int			ft_printstr_fd(char *str, int fd);
int			ft_printnbr_fd(int n, int fd);
int			ft_printpercent_fd(int fd);

#endif