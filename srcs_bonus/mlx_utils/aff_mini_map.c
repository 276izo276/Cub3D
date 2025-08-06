#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>

void	aff_pix_in_img(t_utils_mini *u, t_mini *mini, t_data *data)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - data->map.mini.player_coo.x);
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
					*(unsigned int *)u->pixel_addr = 408080;
				else
				{
					*(unsigned int *)u->pixel_addr = *(unsigned int *)(data->screen->data_addr
							+ (((data->mlx.height - MARGIN - data->u.size)
									+ (u->s.y + u->i.y))
								* data->screen->size_line - (data->mlx.width
									- (u->s.x + u->i.x))
								* (data->screen->bits_per_pixel / 8)));
				}
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

void	aff_color_in_img(t_utils_mini *u, t_mini *mini, t_data *data)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - mini->player_coo.x);
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
				else
					get_pixel_color(data, MINI_FLOOR);
				*(unsigned int *)u->pixel_addr = u->color;
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

void	calc_value_player_mini_map_aff(t_utils_mini *u, t_img *img, double rad)
{
	u->cos_val = cos(rad);
	u->sin_val = sin(rad);
	u->xdest = u->x - 16;
	u->ydest = u->y - 19;
	u->xfloat = -(u->xdest) * u->cos_val + (u->ydest) * u->sin_val + 16;
	u->yfloat = (u->xdest) * u->sin_val + (u->ydest) * u->cos_val + 19;
	u->color = *(unsigned int *)(img->data_addr + ((u->y) * img->size_line
				+ (u->x) * (img->bits_per_pixel / 8)));
}

void	set_player_in_mini_map(t_utils_mini *u, t_img *img, double rad)
{
	int	start_y;
	int	start_x;

	start_y = u->size / 2 - img->height / 2;
	start_x = u->size / 2 - img->width / 2;
	u->y = -1;
	while (++u->y < img->height)
	{
		u->x = -1;
		while (++u->x < img->width)
		{
			calc_value_player_mini_map_aff(u, img, rad);
			if (u->color != 0x00000000)
			{
				u->pixel_addr = u->mmap.data_addr + (((int)ceil(u->yfloat)
							+ start_y) * u->mmap.size_line
						+ ((int)ceil(u->xfloat) + start_x)
						* (u->mmap.bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = u->color;
				u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat)
							+ start_y) * u->mmap.size_line
						+ ((int)floor(u->xfloat) + start_x)
						* (u->mmap.bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = u->color;
			}
		}
	}
}

void	aff_mini_map(t_data *data)
{
	data->u.y = -4;
	while (++data->u.y < 4)
	{
		data->u.x = -4;
		while (++data->u.x < 4)
		{
			data->u.new_y = data->map.player_coo->y + data->u.y;
			data->u.new_x = data->map.player_coo->x + data->u.x;
			if (data->u.new_y >= data->map.tabmap_height || data->u.new_y < 0
				|| data->u.new_x >= ft_strlen(data->map.tabmap[data->u.new_y])
				|| data->u.new_x < 0
				|| data->map.tabmap[data->u.new_y][data->u.new_x] == ' ')
			{
				aff_pix_in_img(&data->u, &data->map.mini, data);
			}
			else
			{
				aff_color_in_img(&data->u, &data->map.mini, data);
			}
		}
	}
	set_player_in_mini_map(&data->u, &data->map.mini.img[MINI_CURS],
		data->map.mini.rad);
	print_mini_map(data);
}
