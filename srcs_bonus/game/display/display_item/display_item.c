#include "cub3d_bonus.h"
#include <strings.h>

void	display_redir_item_type(t_data *data, int i, int j)
{
	// if (i < data->mlx.width / 4)
    	//write(1,"d1\n",3);
	if (data->ray[i].items[j]->type == DOOR)
		display_door(data, i, j);
	if (data->ray[i].items[j]->type == EXPECTO_PATRONUM
		&& !data->ray[i].items[j]->categ)
		display_patronum(data, i, j);
	else if (data->ray[i].items[j]->type == ANIM_DEATH)
		display_anim_death(data, i, j);
	else if (data->ray[i].items[j]->type == BH)
		display_bh(data, i, j);
	else
		display_others(data, i, j);
	// if (i < data->mlx.width / 4)
    	//write(1,"d2\n",3);
	bzero(data->ray[i].items[j], sizeof(t_hit_item));
	// if (i < data->mlx.width / 4)
    	//write(1,"d3\n",3);
}

void	reset_data_display(t_data *data, int i)
{
	int	j;

	j = 0;
	// if (i < data->mlx.width / 4)
		//write(1,"q\n",2);
	while (j <= MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
		+ data->map.nb_floo)
	{
		if (data->ray[i].items[j]->use)
		{
			// if (i < data->mlx.width / 4)
   				//write(1,"q2\n",3);
			bzero(data->ray[i].items[j], sizeof(t_hit_item));
			// if (i < data->mlx.width / 4)
    			//write(1,"q3\n",3);
		}
		j++;
	}
	// if (i < data->mlx.width / 4)
		//write(1,"w\n",3);
}

bool	display_item_loop(t_data *data, int i, int *j, double *dist_max)
{
	*dist_max = 0;
	*j = 0;
	while (*j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
		+ data->map.nb_floo)
	{
		if (*dist_max < data->ray[i].items[*j]->dist
			&& data->ray[i].items[*j]->print == true)
			*dist_max = data->ray[i].items[*j]->dist;
		(*j)++;
	}
	if (*dist_max == 0)
		return (true);
	*j = -1;
	while (++(*j) < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
		+ data->map.nb_floo)
		if (data->ray[i].items[*j]->dist == *dist_max)
			break ;
	display_redir_item_type(data, i, *j);
	return (false);
}

#include <stdio.h>

void	display_item(t_data *data, int i)
{
	double	dist_max;
	int		j;

	dist_max = -1;
	j = 0;
	// //write(1,"n\n",2);
	// if (i < data->mlx.width / 4)
	{
		// printf("i>%d\n",i);
    	//write(1,"o0\n",3);
		while (j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
			+ data->map.nb_floo)
		{
    		// //write(1,"l1\n",3);
			if (data->ray[i].items[j]->dist < data->ray[i].dist_wall
				&& data->ray[i].items[j]->use == true)
				data->ray[i].items[j]->print = true;
    		// //write(1,"l2\n",3);
			j++;
		}
		//write(1,"o1\n",3);
		while (dist_max != 0)
		{
			if (display_item_loop(data, i, &j, &dist_max) == true)
				break ;
			//write(1,"o2\n",3);
			bzero(data->ray[i].items[j], sizeof(t_hit_item));
			//write(1,"o3\n",3);
		}
	}
	// //write(1,"y\n",2);
	reset_data_display(data, i);
	// //write(1,"f\n",2);
}
