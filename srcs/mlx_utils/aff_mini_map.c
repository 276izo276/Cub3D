#include "struct.h"
#include "texture.h"
#include "cub3d.h"
#include "utils.h"
#include <stdlib.h>

void	aff_pix_in_img(t_utils_mini *u, t_mini *mini)
{
	u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
	u->i.y = 0;
	while (u->i.y < 64)
	{
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64
			- u->data->map.mini.player_coo.x);
		u->i.x = 0;
		while (u->s.y + u->i.y >= 0 && u->s.y + u->i.y < u->size && u->i.x < 64)
		{
			if (u->s.x + u->i.x >= 0 && u->s.x + u->i.x < u->size)
			{
				u->pixel_addr = u->mmap->data_addr + ((u->s.y + u->i.y) * u->mmap
						->size_line + (u->s.x + u->i.x)
						* (u->mmap->bits_per_pixel / 8));
				*(unsigned int *)u->pixel_addr = 0x00000000;
			}
			u->i.x++;
		}
		u->i.y++;
	}
}

void	aff_color_in_img(t_utils_mini *u, t_mini *mini)
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
				u->pixel_addr = u->mmap->data_addr
						+ ((u->s.y + u->i.y) * u->mmap
						->size_line + (u->s.x + u->i.x)
						* (u->mmap->bits_per_pixel / 8));
				if (u->data->map.tabmap[u->new_y][u->new_x] == '1')
					u->color = get_pixel_color(u, MINI_WALL);
				else
					u->color = get_pixel_color(u, MINI_FLOOR);
				*(unsigned int *)u->pixel_addr = *(unsigned int *)u->color;
			}
			u->i.x++;
		}
		u->i.y++;
	}
}


void	set_player_in_mini_map(t_utils_mini *u)
{
	u->y = u->size / 2 - 2;
	while (u->y < u->size / 2 + 2)
	{
		u->x = u->size / 2 - 2;
		while (u->x < u->size / 2 + 2)
		{
			char *pixel_addr = u->mmap->data_addr
				+ (u->y * u->mmap->size_line + u->x
				* (u->mmap->bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = 0x00FF0000;
			u->x++;
		}
		u->y++;
	}
}


void	aff_mini_map(t_data *data)
{
	t_utils_mini	u;

	init_utils_mini(&u, data);
	while (++u.y < 4)
	{
		u.x = -4;
		while (++u.x < 4)
		{
			u.new_y = data->map.player_coo->y + u.y;
			u.new_x = data->map.player_coo->x + u.x;
			if (u.new_y >= data->map.tabmap_height || u.new_y < 0
			|| u.new_x >= ft_strlen(data->map.tabmap[u.new_y]) || u.new_x < 0
			|| data->map.tabmap[u.new_y][u.new_x] == ' ')
			{
				aff_pix_in_img(&u, &u.data->map.mini);
			}
			else
			{
				aff_color_in_img(&u,&u.data->map.mini);
			}
		}
	}
	set_player_in_mini_map(&u);
	print_mini_map(&u);
}