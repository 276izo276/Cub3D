/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:56:33 by ale-guel          #+#    #+#             */
/*   Updated: 2025/09/04 17:15:23 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LST_H
# define T_LST_H

typedef struct s_lst	t_lst;

struct s_lst
{
	t_lst	*prev;
	void	*dt;
	void	(*f)(void *);
	t_lst	*next;
};

/*****************************************************************************/
/**                               T_LST_1.c                                 **/
/*****************************************************************************/

t_lst	*add_end_lst(void *elem, t_lst *lst, void (*f)(void *));
t_lst	*add_start_lst(void *elem, t_lst *lst, void (*f)(void *));
t_lst	*get_first_elem_lst(t_lst *lst);
t_lst	*get_last_elem_lst(t_lst *lst);
t_lst	*remove_elem_lst(t_lst *elem);

/*****************************************************************************/
/**                               T_LST_2.c                                 **/
/*****************************************************************************/

t_lst	*remove_f_elem_lst(t_lst *elem);
void	f_elem_lst(t_lst *elem);
void	f_all_lst(t_lst *lst);
t_lst	*move_to_end_lst(t_lst *elem, t_lst *lst);
t_lst	*move_to_start_lst(t_lst *elem, t_lst *lst);

/*****************************************************************************/
/**                               T_LST_3.c                                 **/
/*****************************************************************************/

void	set_value_t_lst(t_lst *new, void *elem, void (*f)(void *));
t_lst	*add_before_lst(void *elem, t_lst *lst, void (*f)(void *));
t_lst	*add_after_lst(void *elem, t_lst *lst, void (*f)(void *));
int		ft_strlen_lst(t_lst *lst);
void	move_before_lst(t_lst *elem, t_lst *lst);

#endif