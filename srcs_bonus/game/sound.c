/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:20 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:21 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <signal.h>
#include <sys/wait.h>

void	handle_sound(t_data *data)
{
	t_sound	*sound;
	t_lst	*lst;
	t_lst	*next;
	int		result;

	lst = get_first_elem_lst(data->sound);
	while (lst)
	{
		sound = lst->dt;
		next = lst->next;
		if (get_mtime() > sound->start + sound->duration * 1000)
		{
			result = waitpid(sound->pid, NULL, WNOHANG);
			if (result == 0 && sound->duration != -1)
			{
				kill(sound->pid, SIGTERM);
				data->sound = remove_f_elem_lst(lst);
			}
			else if (sound->duration != -1)
				data->sound = remove_f_elem_lst(lst);
		}
		lst = next;
	}
}

void	remove_sound(t_data *data, int info)
{
	t_sound	*sound;
	t_lst	*lst;
	t_lst	*next;
	int		result;

	lst = get_first_elem_lst(data->sound);
	while (lst)
	{
		sound = lst->dt;
		next = lst->next;
		if (info == sound->id)
		{
			result = waitpid(sound->pid, NULL, WNOHANG);
			if (result == 0 && sound->duration != -1)
			{
				kill(sound->pid, SIGTERM);
				data->sound = remove_f_elem_lst(lst);
			}
			else
				data->sound = remove_f_elem_lst(lst);
		}
		lst = next;
	}
}

void	sound_dead(t_data *data)
{
	f_all_lst(data->sound);
	data->sound = NULL;
	data->sound = add_end_lst(create_sound(data, 26), data->sound, free_sound);
}
