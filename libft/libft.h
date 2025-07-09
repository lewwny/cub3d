/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lengarci <lengarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:35:09 by lenygarcia        #+#    #+#             */
/*   Updated: 2025/07/09 14:32:52 by lengarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFFER_SIZE 20000

typedef struct s_gb
{
	void			*content;
	int				index;
	struct s_gb		*next;
}	t_gb;

long	ft_atoi(char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isdigit(int c);
int		ft_isspace(char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isprint(int c);
int		ft_lstsize(t_gb *lst);
int		ft_putstri(int fd, char const *s);
int		ft_putchari(int fd, char c);
int		ft_putnbri(int fd, int n);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_putnbrui(int fd, size_t n);
int		ft_putnbrhexmin(int fd, int n);
int		ft_putnbrhexmaj(int fd, int n);
int		ft_putptr(int fd, void	*ptr);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strarrlen(char **arr);

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_striteri(char *s, void (*f)(size_t, char *));
void	ft_lstadd_front(t_gb **lst, t_gb *new);
void	ft_lstadd_back(t_gb **lst, t_gb *new);
void	ft_lstdelone(t_gb *lst);
void	ft_lstclear(t_gb **lst);
void	ft_bzero(void *s, size_t n);
void	free_all(t_gb **garbage);
void	_free(void *ptr, t_gb **garbage);
void	malloc_error(t_gb **garbage);

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*_malloc(size_t size, t_gb **garbage);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s1, t_gb **garbage);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(size_t, char));
char	*ft_substr(char const *s, size_t start, size_t len, t_gb **garbage);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);

t_gb	*ft_lstnew(void *content);
t_gb	*ft_lstlast(t_gb *lst);

#endif
