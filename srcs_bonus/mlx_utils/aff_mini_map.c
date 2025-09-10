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
					*(unsigned int *)u->pixel_addr = 0x6e583e;
				else
					set_pix_img(u, data);
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

static void	aff_enemy(t_data *data, t_utils_mini *u, t_mini *mini)
{
	t_lst	*lst;
	t_enemy	*enemy;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		u->s.y = 1 * 64 + 32 + (u->y * 64 + 64 - mini->player_coo.y);
		u->s.x = 1 * 64 + 32 + (u->x * 64 + 64 - mini->player_coo.x);
		for(int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				if (enemy->center.case_x == u->new_x && enemy->center.case_y == u->new_y
					&& (u->s.y + i + enemy->center.coo_y >= 0
					&& u->s.y + i + enemy->center.coo_y < u->size
					&& u->s.x + j + enemy->center.coo_x >= 0
					&& u->s.x + j + enemy->center.coo_x < u->size))
				{
					u->pixel_addr = u->mmap.data_addr + ((u->s.y + i + (int)enemy->center.coo_y)
						* u->mmap.size_line + (u->s.x + j + (int)enemy->center.coo_x)
						* (u->mmap.bits_per_pixel / 8));
					*(unsigned int *)u->pixel_addr = 0xff0000;
				}
				if (enemy->left.case_x == u->new_x && enemy->left.case_y == u->new_y
					&& (u->s.y + i + enemy->left.coo_y >= 0
					&& u->s.y + i + enemy->left.coo_y < u->size
					&& u->s.x + j + enemy->left.coo_x >= 0
					&& u->s.x + j + enemy->left.coo_x < u->size))
				{
					u->pixel_addr = u->mmap.data_addr + ((u->s.y + i + (int)enemy->left.coo_y)
						* u->mmap.size_line + (u->s.x + j + (int)enemy->left.coo_x)
						* (u->mmap.bits_per_pixel / 8));
					*(unsigned int *)u->pixel_addr = 0x00ff00;
				}
				if (enemy->right.case_x == u->new_x && enemy->right.case_y == u->new_y
					&& (u->s.y + i + enemy->right.coo_y >= 0
					&& u->s.y + i + enemy->right.coo_y < u->size
					&& u->s.x + j + enemy->right.coo_x >= 0
					&& u->s.x + j + enemy->right.coo_x < u->size))
				{
					u->pixel_addr = u->mmap.data_addr + ((u->s.y + i + (int)enemy->right.coo_y)
						* u->mmap.size_line + (u->s.x + j + (int)enemy->right.coo_x)
						* (u->mmap.bits_per_pixel / 8));
					*(unsigned int *)u->pixel_addr = 0x0000ff;
				}
			}
		}
		lst = lst->next;
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
				aff_pix_in_img(&data->u, &data->map.mini, data);
			else
			{
				aff_color_in_img(&data->u, &data->map.mini, data);
				aff_enemy(data, &data->u, &data->map.mini);
			}
		}
	}
	set_player_in_mini_map(data, &data->u, &data->map.mini.img[MINI_LEFT],
		data->map.mini.rad);
	print_mini_map(data);
}
