/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:45:01 by ale-guel          #+#    #+#             */
/*   Updated: 2025/04/16 10:28:00 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_charlst	t_charlst;

struct s_charlst
{
	t_charlst	*prev;
	char		*buffer;
	int			size;
	t_charlst	*next;
};

/*****************************************************************************/
/*                                CHAR LST                                   */
/*****************************************************************************/

t_charlst	*get_first_elem_charlst(t_charlst *lst);
t_charlst	*get_last_elem_charlst(t_charlst *lst);
t_charlst	*move_to_end_charlst(t_charlst *elem, t_charlst *lst);
t_charlst	*f_all_charlst(t_charlst *lst);
t_charlst	*init_charlst(void);
t_charlst	*add_char_charlst(t_charlst *lst, char c);
t_charlst	*add_string_charlst(t_charlst *lst, char *str);
int			empty_buffer(t_charlst *lst, size_t size, int fd);

t_charlst	*ft_decimal(int val, t_charlst *lst, int j, int i);
t_charlst	*ft_minhex(unsigned int val, t_charlst *lst);
t_charlst	*ft_majhex(unsigned int val, t_charlst *lst);
t_charlst	*ft_pointer(void *point, t_charlst *lst, int i);
t_charlst	*printf_putchar_fd(char c, t_charlst *lst);
t_charlst	*ft_putstr(char *str, t_charlst *lst);
t_charlst	*ft_unsigned(unsigned int val, t_charlst *lst);
size_t		printf_strlen(char *str);
char		*ft_decimal_to_base(size_t decimal, char *base);
int			ft_printf_fd(int fd, const char *str, ...);
t_charlst	*call_func(char c, va_list args, t_charlst *lst);	

#endif
