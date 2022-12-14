/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:21:34 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/11/16 17:50:47 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>
# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0
# define WHITESPACE_CHARACTERS " \t\n\v\f\r"

// Þis is ān linkt list struct
// Þu kont maken linkt listen med
// Þis struct. Et häft two
// datapointeren, et earst
// is Þe contant fan Þe
// list, et tweiden,
// is ān pointer naor
// Þe fōrgenden struct
// in Þe list.
typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

// Doubly linked list with the purpose
// of acting in a similar fashion to
// C++ vectors.
typedef struct s_vector {
	size_t			index;
	void			*data;
	struct s_vector	*next;
	struct s_vector	*previous;
}	t_vector;

// LINKT LISTEN FUNKTIONEN
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew_front(t_list **lst_ptr, void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew_back(t_list **lst_ptr, void *content);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lst_remove_if(t_list **lst, void *needle,
				int (*cmp_fn)(void *lst_content, void *needle));

// FILE SCRÏBEN FUNKTIONEN
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// STRING FUNKTIONEN
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
char		*ft_strncpy(char *dest, char *src, size_t n);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
bool		ft_streq(const char *s1, const char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strmapi(char const *s, char (*f) (unsigned int, char));
char		*ft_strjoin_and_free_left_right(char *left, char **right_ptr);
char		*ft_strjoin_and_free_left(char *left, char *right);
char		*ft_strjoin_array(char *array[]);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split_set(char const *s, char *set);
char		**ft_split(char const *s, char c);
char		*ft_strndup(const char *s1, size_t len);
char		*ft_str_not_set(char *haystack, char *set);
char		*ft_strset(char *haystack, char *set);
char		*ft_strtrim_whitespace(const char *str);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_revstr(char *str, int size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_putchar(char c);
void		ft_putstr(char *str);
int			ft_charchk(int tc, char *dict);

// TO FUNKTIONEN
int			ft_tolower(int c);
int			ft_toupper(int c);

// DETERMINATÏE FUNKTIONEN
int			ft_islower(int c);
int			ft_isupper(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);

// MEMORY FUNKTIONEN
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_free(void *ptrptr);
size_t		ft_ptr_array_len(void **ptr_array);

// ASCII NÆR INTEGER AF INTEGER NÆR ASCII
char		*ft_itoa(int n);
bool		ft_atoi_safe(const char *str, int *nbr);
int			ft_atoi(const char *str);
void		ft_putnbr(int nb);

// INTEGER FUNKTIONEN
size_t		ft_revnum(size_t nb);
size_t		ft_numlen_t(size_t n);

// GET_NEXT_LINE FUNKTIONEN
char		*gnl_strncpy(char *dest, const char *src, size_t n);
char		*merge(char **buf_1, char **buf_2);
char		*get_next_line(int fd);
char		*gnl_strndup(const char *s1, size_t len);
char		*gnl_strjoin(char const *s1, char const *s2);
char		*get_next_line(int fd);

// PRINTF FUNKTIONEN
int			ft_printf(const char *fmt, ...);
int			handle_variable(const char spec, va_list arglist);
int			ft_puthex(size_t nb, unsigned int mode);
int			ft_putvoid(size_t ptr);
int			ft_unsigned_putnbr(unsigned int nb);
int			ft_putstr_len(char *str);
int			ft_putnbr_len(int nb);
int			ft_putchar_len(char c);
void		ft_putnbr_base(int n, int base);

// VEKTOR FUNKTIONEN
t_vector	*alloc_vector(int n_elements);
int			vec_assign_element(t_vector *head, size_t idx, void *data);
t_vector	*vec_get_element(t_vector *head, size_t idx);
t_vector	*new_vector_element(t_vector *prev, size_t idx);
void		*free_vector(t_vector *vec, void (*dealloc) (void *));

// VEKTOR NAVI FUNKTIONEN
t_vector	*vector_get_last(t_vector *vec);
t_vector	*vector_get_first(t_vector *vec);
int			vector_size(t_vector *vec);

// VEKTOR OPERATION FUNKTIONEN
t_vector	*vector_push_back(t_vector *head, t_vector *new);
void		vector_pop_back(t_vector *head, void (*dealloc) (void *));
t_vector	*vector_push_front(t_vector **head, t_vector *new);
t_vector	*vector_pop_front(t_vector *head, void (*dealloc) (void *));

#endif
