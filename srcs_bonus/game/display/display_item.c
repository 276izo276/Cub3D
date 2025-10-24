#include "struct_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include <string.h>


#include <stdio.h>
#include <unistd.h>

void	set_texture(t_data *data, int i, int j)
{
	t_img	*front;
	t_img	*back;
	t_img	*side;
	t_img	*side_front;
	t_img	*side_back;

	if (data->ray[i].items[j]->type == ITEM)
	{
		front = data->ray[i].items[j]->item->front_img;
		back = data->ray[i].items[j]->item->back_img;
	}
	if (data->ray[i].items[j]->type == ENEMY)
	{
		front = data->ray[i].items[j]->enemy->front_img;
		back = data->ray[i].items[j]->enemy->back_img;
		side = data->ray[i].items[j]->enemy->side_img;
		side_back = data->ray[i].items[j]->enemy->side_back_img;
		side_front = data->ray[i].items[j]->enemy->side_front_img;
	}
	if (data->ray[i].items[j]->type == DOOR)
		data->ray[i].items[j]->texture = &data->img[DOOR_FIXED];
	else if (data->ray[i].items[j]->type == FLOO_CLOSE)
		data->ray[i].items[j]->texture = &data->img[FLOO_CLOSE];
	else if (data->ray[i].items[j]->type == FLOO_OPEN)
		data->ray[i].items[j]->texture = &data->img[FLOO_OPEN];
	else if (data->ray[i].items[j]->side == BACK)
		data->ray[i].items[j]->texture = back;
	else if (data->ray[i].items[j]->side == FRONT)
		data->ray[i].items[j]->texture = front;
	else if (data->ray[i].items[j]->side == RIGHT || data->ray[i].items[j]->side == LEFT)
		data->ray[i].items[j]->texture = side;
	else if (data->ray[i].items[j]->side == LEFT_FRONT || data->ray[i].items[j]->side == RIGHT_FRONT)
		data->ray[i].items[j]->texture = side_front;
	else if (data->ray[i].items[j]->side == LEFT_BACK || data->ray[i].items[j]->side == RIGHT_BACK)
		data->ray[i].items[j]->texture = side_back;
}

void	define_posx_texture(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = data->ray[i].items[j]->posx;
	// printf("widdth >>>%d\n",data->ray[i].items[j]->texture->width);
	if (data->ray[i].items[j]->side == REVERSED || data->ray[i].items[j]->side == LEFT
		|| data->ray[i].items[j]->side == LEFT_FRONT || data->ray[i].items[j]->side == RIGHT_BACK)
		posx_display = 1 - posx_display;
	data->ray[i].items[j]->texture_coo.x = (int)(posx_display * data->ray[i].items[j]->texture->width);
	if (data->ray[i].items[j]->texture_coo.x < 0)
		data->ray[i].items[j]->texture_coo.x = 0;
	if (data->ray[i].items[j]->texture_coo.x >= data->ray[i].items[j]->texture->width)
		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture->width - 1;
}

void	put_text_pix_img_item(t_data *data, int i, int j, int fixed)
{
	data->ray[i].items[j]->door_status = 0;
	if (data->ray[i].items[j]->type == DOOR && !fixed)
	{
		if (data->ray[i].items[j]->door->pos >= 50)
			data->ray[i].items[j]->door_status = 50;
		else
			data->ray[i].items[j]->door_status = data->ray[i].items[j]->door->pos;
	}
	// printf("a\n");
	data->ray[i].items[j]->texture_coo.y = (data->ray[i].pix_y - data->ray[i].items[j]->htop + data->ray[i].items[j]->door_status / 100 * data->ray[i].items[j]->size)
		* data->ray[i].items[j]->texture->height / data->ray[i].items[j]->dist_height;
	if (data->ray[i].items[j]->texture_coo.y >= data->ray[i].items[j]->texture->height
	|| data->ray[i].items[j]->texture_coo.y < 0)
		return ;
	// printf("b\n");
	data->ray[i].items[j]->pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	data->ray[i].items[j]->text_pix = data->ray[i].items[j]->texture->data_addr + (data->ray[i].items[j]->texture_coo.y
			* data->ray[i].items[j]->texture->size_line + data->ray[i].items[j]->texture_coo.x);
	data->ray[i].items[j]->color = *(unsigned int *)data->ray[i].items[j]->text_pix;
	if (data->ray[i].items[j]->color != WHITE && data->ray[i].items[j]->color != YELLOW && data->ray[i].items[j]->color != RED)
		*(unsigned int *)data->ray[i].items[j]->pixel_addr = data->ray[i].items[j]->color;
}

void	display_item(t_data *data, int i)
{
	double	dist_max;
	int	j;
	
	dist_max = -1;
	j = 0;
	while (j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
	{
		if (data->ray[i].items[j]->dist < data->ray[i].dist_wall
			&& data->ray[i].items[j]->use == true)
		{
			data->ray[i].items[j]->print = true;
		}
		// else
		// 	ft_bzero(data->ray[i].items[j], sizeof(t_hit_item));
		j++;
	}
	while (dist_max != 0)
	{
		dist_max = 0;
		j = 0;
		while (j <  MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
		{
			if (dist_max < data->ray[i].items[j]->dist
				&& data->ray[i].items[j]->print == true)
			{
				dist_max = data->ray[i].items[j]->dist;
			}
			j++;
		}
		if (dist_max == 0)
			break ;
		j = -1;
		while (++j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
			if (data->ray[i].items[j]->dist == dist_max)
				break ;
		if (data->ray[i].items[j]->type == DOOR)
		{
			data->ray[i].items[j]->texture = &data->img[DOOR_MOVE];
			define_posx_texture(data, i, j);
			data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
				* data->ray[i].calc_bits;
			data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture_coo.x * (data->ray[i].items[j]->texture->bits_per_pixel >> 3);
			data->ray[i].pix_y = data->ray[i].items[j]->htop;
			if (data->ray[i].pix_y < 0)
				data->ray[i].pix_y = 0;
			data->ray[i].items[j]->dist_height = data->ray[i].items[j]->hbot - data->ray[i].items[j]->htop;
			while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
				&& data->ray[i].pix_y < data->mlx.height)
			{
				if (data->ray[i].pix_y > data->ray[i].items[j]->htop + data->ray[i].items[j]->dist_height * .15)
					put_text_pix_img_item(data, i, j, 0);
				data->ray[i].pix_y++;
			}
		}
		set_texture(data, i, j);
		define_posx_texture(data, i, j);
		data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
			* data->ray[i].calc_bits;
		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture_coo.x * (data->ray[i].items[j]->texture->bits_per_pixel >> 3);
		data->ray[i].pix_y = data->ray[i].items[j]->htop;
		if (data->ray[i].pix_y < 0)
			data->ray[i].pix_y = 0;
		data->ray[i].items[j]->dist_height = data->ray[i].items[j]->hbot - data->ray[i].items[j]->htop;
		while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
			&& data->ray[i].pix_y < data->mlx.height)
		{
			put_text_pix_img_item(data, i, j, 1);
			data->ray[i].pix_y++;
		}
		bzero(data->ray[i].items[j], sizeof(t_hit_item));
	}
	j = 0;
	while (j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
	{
		if (data->ray[i].items[j]->use)
			bzero(data->ray[i].items[j], sizeof(t_hit_item));
		j++;
	}
}
