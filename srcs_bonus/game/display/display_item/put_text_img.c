#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <string.h>

static void	check_door_status(t_data *data, int i, int j, int fixed)
{
	data->ray[i].items[j]->door_status = 0;
	if (data->ray[i].items[j]->type == DOOR && !fixed)
	{
		if (data->ray[i].items[j]->door->pos >= 50)
			data->ray[i].items[j]->door_status = 50;
		else
			data->ray[i].items[j]->door_status
				= data->ray[i].items[j]->door->pos;
	}
}

static void	is_tornado_anim(t_data *data, int i, int j)
{
	int	frame_height;

	if (data->ray[i].items[j]->type == VENTUS)
	{
		frame_height = data->ray[i].items[j]->texture->height;
		data->ray[i].items[j]->texture_coo.y = ((data->ray[i].pix_y
					- data->ray[i].items[j]->htop
					+ data->ray[i].items[j]->door_status / 100
					* data->ray[i].items[j]->size) * frame_height)
			/ data->ray[i].items[j]->dist_height;
	}
	else
		data->ray[i].items[j]->texture_coo.y = (data->ray[i].pix_y
				- data->ray[i].items[j]->htop
				+ data->ray[i].items[j]->door_status / 100
				* data->ray[i].items[j]->size)
			* data->ray[i].items[j]->texture->height
			/ data->ray[i].items[j]->dist_height;
}

void	put_text_pix_img_item(t_data *data, int i, int j, int fixed)
{
	check_door_status(data, i, j, fixed);
	is_tornado_anim(data, i, j);
	if (data->ray[i].items[j]->texture_coo.y >= data->ray[i]
		.items[j]->texture->height
		|| data->ray[i].items[j]->texture_coo.y < 0)
		return ;
	data->ray[i].items[j]->pixel_addr = data->ray[i].img_addr
		+ (data->ray[i].pix_y * data->screen->size_line);
	data->ray[i].items[j]->text_pix = data->ray[i].items[j]->texture->data_addr
		+ (data->ray[i].items[j]->texture_coo.y
			* data->ray[i].items[j]->texture->size_line
			+ data->ray[i].items[j]->texture_coo.x);
	data->ray[i].items[j]->color = *(unsigned int *)data->ray[i]
		.items[j]->text_pix;
	if (data->ray[i].items[j]->color != WHITE
		&& data->ray[i].items[j]->color != RED)
	{
		if (data->ray[i].items[j]->color == YELLOW
			&& data->ray[i].items[j]->type != DOOR)
			*(unsigned int *)data->ray[i].items[j]->pixel_addr
				= data->ray[i].items[j]->enemy->color_coa;
		else if (data->ray[i].items[j]->color != YELLOW)
			*(unsigned int *)data->ray[i].items[j]->pixel_addr
				= data->ray[i].items[j]->color;
	}
}
