/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:00:50 by ale-guel          #+#    #+#             */
/*   Updated: 2025/01/31 08:53:45 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>

typedef struct s_gnl
{
	struct s_gnl	*prev;
	char			*content;
	struct s_gnl	*next;
}		t_gnl;

//base
int		get_next_line(int fd, char **r_line);
char	*read_line(char *buffer, int fd);
void	decal_buffer(char *buffer);
int		have_n(char *str);

//utils
size_t	gnl_strlen(char *str);
char	*gnl_copy(char *buffer);
t_gnl	*add_elem_lst(t_gnl *lst, char *elem, int end);
t_gnl	*get_elem_lst(t_gnl *lst, int end);
char	*empty_lst(t_gnl *lst, int print, size_t nb_read, size_t size);

#endif