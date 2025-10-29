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

	if (data->ray[i].items[j]->type == ITEM || data->ray[i].items[j]->type == VENTUS)
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
	int		frame_width;
	int		frame_height;
	int		frame_index;

	posx_display = data->ray[i].items[j]->posx;
	if (data->ray[i].items[j]->side == REVERSED || data->ray[i].items[j]->side == LEFT
		|| data->ray[i].items[j]->side == LEFT_FRONT || data->ray[i].items[j]->side == RIGHT_BACK)
		posx_display = 1 - posx_display;
	if (data->ray[i].items[j]->type == VENTUS)
	{
		frame_index = data->ray[i].items[j]->status;
		frame_width = data->ray[i].items[j]->texture->width / 4;
		frame_height = data->ray[i].items[j]->texture->height / 4;
		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->status * frame_width + (int)(posx_display * frame_width);
		data->ray[i].items[j]->texture_coo.y_offset = (frame_index / 4) * frame_height;
		++data->ray[i].items[j]->status;
		// if (data->ray[i].items[j]->status >= 16)
		// 	data->ray[i].items[j]->status = 0;
	}
	else
		data->ray[i].items[j]->texture_coo.x = (int)(posx_display * data->ray[i].items[j]->texture->width);
	if (data->ray[i].items[j]->texture_coo.x < 0)
		data->ray[i].items[j]->texture_coo.x = 0;
	if (data->ray[i].items[j]->texture_coo.x >= data->ray[i].items[j]->texture->width)
		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture->width - 1;
}
// void	define_posx_texture(t_data *data, int i, int j)
// {
// 	double	posx_display;

// 	posx_display = data->ray[i].items[j]->posx;
// 	// printf("widdth >>>%d\n",data->ray[i].items[j]->texture->width);
// 	if (data->ray[i].items[j]->side == REVERSED || data->ray[i].items[j]->side == LEFT
// 		|| data->ray[i].items[j]->side == LEFT_FRONT || data->ray[i].items[j]->side == RIGHT_BACK)
// 		posx_display = 1 - posx_display;
// 	data->ray[i].items[j]->texture_coo.x = (int)(posx_display * data->ray[i].items[j]->texture->width);
// 	if (data->ray[i].items[j]->texture_coo.x < 0)
// 		data->ray[i].items[j]->texture_coo.x = 0;
// 	if (data->ray[i].items[j]->texture_coo.x >= data->ray[i].items[j]->texture->width)
// 		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture->width - 1;
// }

void	put_text_pix_img_item(t_data *data, int i, int j, int fixed)
{
	int	frame_height;

	data->ray[i].items[j]->door_status = 0;
	if (data->ray[i].items[j]->type == DOOR && !fixed)
	{
		if (data->ray[i].items[j]->door->pos >= 50)
			data->ray[i].items[j]->door_status = 50;
		else
			data->ray[i].items[j]->door_status = data->ray[i].items[j]->door->pos;
	}
	// printf("a\n");
	if (data->ray[i].items[j]->type == VENTUS)
	{
		frame_height = data->ray[i].items[j]->texture->height / 4;

		data->ray[i].items[j]->texture_coo.y = 	((data->ray[i].pix_y - data->ray[i].items[j]->htop + data->ray[i].items[j]->door_status / 100 * data->ray[i].items[j]->size) * frame_height) / data->ray[i].items[j]->dist_height + data->ray[i].items[j]->texture_coo.y_offset;
	}
	else
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
		if (data->ray[i].items[j]->type == EXPECTO_PATRONUM)
		{
			data->ray[i].items[j]->htop = data->mlx.height / 2 - (2 * data->ray[i].items[j]->item->radius) * data->ray[i].d_proj / data->ray[i].items[j]->dist;
			data->ray[i].pix_y = data->ray[i].items[j]->htop;
			if (data->ray[i].pix_y < 0)
				data->ray[i].pix_y = 0;
			if (data->ray[i].pix_y < round(data->ray[i].max_height - data->ray[i].items[j]->max_size))
				data->ray[i].pix_y = round(data->ray[i].max_height - data->ray[i].items[j]->max_size);
			// printf("\nmax_size>%lf\n",data->ray[i].items[j]->max_size);
			// printf("dist>%lf\n",data->ray[i].items[j]->dist);
			// printf("dproj>%lf\n",data->ray[i].d_proj);
			// printf("item radius>%lf\n",data->ray[i].items[j]->item->radius);
			data->ray[i].items[j]->hbot = data->mlx.height / 2 + (2 * data->ray[i].items[j]->item->radius) * data->ray[i].d_proj / data->ray[i].items[j]->dist;
			while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
				&& data->ray[i].pix_y < data->mlx.height && data->ray[i].pix_y < round(data->ray[i].max_height + data->ray[i].items[j]->max_size))
			{
				// double	div_part = ;
				double	rap_y = 0;
				// // if (div_part > 0.00001)
				rap_y = (data->ray[i].pix_y - data->mlx.height / 2) / ((data->ray[i].items[j]->hbot - data->ray[i].items[j]->htop) / 2);
				// printf("rap_y>%lf\n",rap_y);
				// printf("rap>%lf  pix_y>%d     radius>%lf\n",rap_y,data->ray[i].pix_y,data->ray[i].items[j]->item->radius);
				double dist = sqrt((data->ray[i].items[j]->posx - 0.5) * (data->ray[i].items[j]->posx - 0.5)
					+ rap_y * rap_y);
				if (dist < .5)
				{
					unsigned int color = *(unsigned int *)(data->screen->data_addr + (data->ray[i].pix_y * data->screen->size_line) + (data->ray[i].pix_x
					* data->ray[i].calc_bits));
					int r;
					int g;
					int b;
					b = (color & 255);
					b = (int)(b + (255 - b) * ((1 - dist * 2)));
					if (b > 255)
						b = 255;
					g = (color >> 8 & 255);
					g = (int)(g + ( 255 - g) * ((1 - dist * 2)));
					if (g > 255)
						g = 255;
					r = (color >> 16 & 255);
					r = (int)(r + ( 255 - r) * ((1 - dist * 2)));
					if (r > 255)
						r = 255;
					color = (r << 16) + (g << 8) + b;
					// return (color);
					// color = get_right_white(data, color, dist * 500000);
					*(unsigned int *)(data->screen->data_addr + (data->ray[i].pix_y * data->screen->size_line) + (data->ray[i].pix_x
					* data->ray[i].calc_bits)) = color;
				}
				data->ray[i].pix_y++;
			}

		}
		else 
		{
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
