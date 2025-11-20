#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	set_pix_img(t_utils_mini *u, t_data *data)
{
	*(unsigned int *)u->pixel_addr = *(unsigned int *)(data->screen->data_addr
			+ (((data->mlx.height - MARGIN - data->u.size)
					+ (u->s.y + u->i.y))
				* data->screen->size_line - (data->mlx.width
					- (u->s.x + u->i.x))
				* (data->screen->bits_per_pixel / 8)));
}

void	aff_pix_in_img(t_utils_mini *u, t_data *data)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - data->player.coo.coo_y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - data->player.coo.coo_x);
		u->i.x = 0;
		while (u->s.y + u->i.y >= 0 && u->s.y + u->i.y < u->size && u->i.x < 64)
		{
			if (u->s.x + u->i.x >= 0 && u->s.x + u->i.x < u->size)
			{
				u->pixel_addr = u->mmap.data_addr + ((u->s.y + u->i.y)
						* u->mmap.size_line + (u->s.x + u->i.x)
						* (u->mmap.bits_per_pixel / 8));
				if (data->map.mini.need_print[data->u.s.y
						+ data->u.i.y][data->u.s.x + data->u.i.x] != 0)
					*(unsigned int *)u->pixel_addr = 0x6e583e;
				else
					set_pix_img(u, data);
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

void	aff_color_in_img(t_utils_mini *u, t_data *data)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - data->player.coo.coo_y);
	u->i.y = 0;
	u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - data->player.coo.coo_x);
	while (u->i.y < 64)
	{
		u->i.x = 0;
		while (u->s.y + u->i.y >= 0 && u->s.y + u->i.y < u->size && u->i.x < 64)
		{
			if (u->s.x + u->i.x >= 0 && u->s.x + u->i.x < u->size)
			{
				u->pixel_addr = u->mmap.data_addr + ((u->s.y + u->i.y)
						* u->mmap.size_line + (u->s.x + u->i.x)
						* (u->mmap.bits_per_pixel / 8));
				if (data->map.tabmap[u->new_y][u->new_x] == '1')
					get_pixel_color(data, MINI_WALL);
				else if (data->map.tabmap[u->new_y][u->new_x] == 'D')
					get_pixel_color(data, MINI_DOOR);
				else if (data->map.tabmap[u->new_y][u->new_x] == 'F')
					get_pixel_color(data, MINI_FLOO);
				else
					get_pixel_color(data, MINI_FLOOR);
				*(unsigned int *)u->pixel_addr = u->color;
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

#include <stdio.h>

void	aff_mini_map(t_data *data)
{
	//DBG1printf("n1\n");
	data->u.y = -4;
	while (++data->u.y < 4)
	{
		data->u.x = -4;
		while (++data->u.x < 4)
		{
			data->u.new_y = data->player.coo.case_y + data->u.y;
			data->u.new_x = data->player.coo.case_x + data->u.x;
			if (data->u.new_y >= data->map.tabmap_height || data->u.new_y < 0
				|| data->u.new_x >= ft_strlen(data->map.tabmap[data->u.new_y])
				|| data->u.new_x < 0
				|| data->map.tabmap[data->u.new_y][data->u.new_x] == ' ')
				aff_pix_in_img(&data->u, data);
			else
			{
				aff_color_in_img(&data->u, data);
			}
		}
	}
	//DBG1printf("n2\n");
	set_player_in_mini_map(data, &data->u, data->map.mini.rad);
	print_mini_map(data);
	//DBG1printf("n3\n");
}
