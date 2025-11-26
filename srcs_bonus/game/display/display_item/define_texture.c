#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <string.h>

static void	which_texture_enemy(t_data *data, int i, int j)
{
	t_img	*front;
	t_img	*back;
	t_img	*side;
	t_img	*side_front;
	t_img	*side_back;

	front = data->ray[i].items[j]->enemy->front_img;
	back = data->ray[i].items[j]->enemy->back_img;
	side = data->ray[i].items[j]->enemy->side_img;
	side_back = data->ray[i].items[j]->enemy->side_back_img;
	side_front = data->ray[i].items[j]->enemy->side_front_img;
	if (data->ray[i].items[j]->side == BACK)
		data->ray[i].items[j]->texture = back;
	else if (data->ray[i].items[j]->side == FRONT)
		data->ray[i].items[j]->texture = front;
	else if (data->ray[i].items[j]->side == RIGHT
		|| data->ray[i].items[j]->side == LEFT)
		data->ray[i].items[j]->texture = side;
	else if (data->ray[i].items[j]->side == LEFT_FRONT
		|| data->ray[i].items[j]->side == RIGHT_FRONT)
		data->ray[i].items[j]->texture = side_front;
	else if (data->ray[i].items[j]->side == LEFT_BACK
		|| data->ray[i].items[j]->side == RIGHT_BACK)
		data->ray[i].items[j]->texture = side_back;
}

void	set_texture(t_data *data, int i, int j)
{
	t_img	*front;
	t_img	*back;

	if (data->ray[i].items[j]->type == ITEM
		|| data->ray[i].items[j]->type == VENTUS)
	{
		front = data->ray[i].items[j]->item->front_img;
		back = data->ray[i].items[j]->item->back_img;
	}
	if (data->ray[i].items[j]->type == ENEMY)
		which_texture_enemy(data, i, j);
	else if (data->ray[i].items[j]->type == DOOR)
		data->ray[i].items[j]->texture = &data->img[DOOR_FIXED];
	else if (data->ray[i].items[j]->type == FLOO_CLOSE)
		data->ray[i].items[j]->texture = &data->img[FLOO_CLOSE];
	else if (data->ray[i].items[j]->type == FLOO_OPEN)
		data->ray[i].items[j]->texture = &data->img[FLOO_OPEN];
	else if (data->ray[i].items[j]->side == BACK)
		data->ray[i].items[j]->texture = back;
	else if (data->ray[i].items[j]->side == FRONT)
		data->ray[i].items[j]->texture = front;
}

void	define_posx_texture(t_data *data, int i, int j)
{
	double	posx_display;
	int		frame_width;

	posx_display = data->ray[i].items[j]->posx;
	if (data->ray[i].items[j]->side == REVERSED || data->ray[i].items[j]->side
		== LEFT || data->ray[i].items[j]->side == LEFT_FRONT
		|| data->ray[i].items[j]->side == RIGHT_BACK)
		posx_display = 1 - posx_display;
	if (data->ray[i].items[j]->type == VENTUS)
	{
		frame_width = data->ray[i].items[j]->texture->width / 32;
		data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->status
			* frame_width + (int)(posx_display * frame_width);
		++data->ray[i].items[j]->status;
	}
	else
		data->ray[i].items[j]->texture_coo.x = (int)(posx_display
				* data->ray[i].items[j]->texture->width);
	if (data->ray[i].items[j]->texture_coo.x < 0)
		data->ray[i].items[j]->texture_coo.x = 0;
	if (data->ray[i].items[j]->texture_coo.x >= data->ray[i].items[j]
		->texture->width)
		data->ray[i].items[j]->texture_coo.x = data->ray[i]
			.items[j]->texture->width - 1;
}
