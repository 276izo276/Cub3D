#ifndef UTILS_H
# define UTILS_H

# include "struct.h"
# include <stdlib.h>

char	*ft_strndup(char *s, int size);
char	*rmbn_dup(char *line);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
int		ft_tab_strlen(char **tab);
int		abs_value(int value);
void	f_exit(t_data *data, int code);
void	ft_bzero(void *s, size_t n);
void	print_map(t_data *data);
void	f_elem(void *elem);

#endif
