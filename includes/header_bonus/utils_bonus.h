#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "struct_bonus.h"
# include <stdlib.h>

char	*ft_strdup(char *s);
char	*ft_strndup(char *s, int size);
char	*rmbn_dup(char *line);
void	f_elem(void *elem);
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
void	ft_bzero(void *s, size_t n);
void	f_exit(t_data *data, int code);
int		ft_tab_strlen(char **tab);
void	print_map(t_data *data);
int		abs_value(int value);
char	*ft_itoa(int nb);
int		are_double_close(double nb1, double nb2);
void	f_tab_char(char **tab);
void	f_img(t_img *img);

#endif
