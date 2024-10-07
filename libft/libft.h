/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:29:42 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/10/02 19:29:50 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

typedef struct s_va
{
	int	end;
	int	start;
	int	i;
	int	nb_words;
}		t_va;

int		count_ch(char *str, char c);
bool	is_space(char c);
bool	check_ch(char c, char *delim);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isalpha(int c);
int		find_char(char *str, char c);
int		count_arrays(char **str);
int		ft_isprint(int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_isascii(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size_dest);
char	*ft_strnstr(const char *str, const char *find, size_t n);
int		ft_atoi(const char *str);
int		atoi_(char *str);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
char	*ft_strdup(const char *s1);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	free_arrays(char **str);
char	**new_split(char *str);
int		hexa_to_int(char *str);

//get_nex_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*read_management(int fd, char **temp, char *buffer);
char	*get_next_line(int fd);
int		strlen_(char *str);
char	*strjoin(char *str, char *str1);
char	*update(char *str);
char	*last_word(char *str);
int		check_line(char *str);

#endif