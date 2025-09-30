#include "struct_bonus.h"
#include "color_bonus.h"
#include "texture_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include <stdlib.h>

static void	set_pix_old_player(t_utils_mini *u, int start_y, int start_x, unsigned int color)
{
	int		a_new;
	int		r_new;
	int		g_new;
	int		b_new;
	int		r_old;
	int		g_old;
	int		b_old;
	unsigned int old_color;

	if (start_x < 0 || start_x >= u->size || start_y < 0 || start_y >= u->size)
		return ;
	if (u->color != YELLOW)
	{
		u->pixel_addr = u->mmap.data_addr + (((int)ceil(u->yfloat)
				+ start_y) * u->mmap.size_line
			+ ((int)ceil(u->xfloat) + start_x)
			* (u->mmap.bits_per_pixel / 8));
		old_color = *(unsigned int *)u->pixel_addr;
		r_old = (old_color >> 16) & 255;
		g_old = (old_color >> 8) & 255;
		b_old = old_color & 255;

		a_new = (color >> 24) & 255;
		r_new = (color >> 16) & 255;
		g_new = (color >> 8) & 255;
		b_new = color & 255;
		r_new = (int)((1 - (a_new / 255.0)) * r_old + (a_new / 255.0) * r_new);
		g_new = (int)((1 - (a_new / 255.0)) * g_old + (a_new / 255.0) * g_new);
		b_new = (int)((1 - (a_new / 255.0)) * b_old + (a_new / 255.0) * b_new);
		*(unsigned int *)u->pixel_addr = (r_new << 16) + (g_new << 8) + b_new;
		u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat)
		+ start_y) * u->mmap.size_line
		+ ((int)floor(u->xfloat) + start_x)
		* (u->mmap.bits_per_pixel / 8));
		*(unsigned int *)u->pixel_addr = (r_new << 16) + (g_new << 8) + b_new;
	}
}

static bool	check_gap(t_data *data)
{
	int	gap_x;
	int	gap_y;

	gap_x = (data->map.mini.foot_tab[0].coo.case_x - data->map.player_coo->x) * 64 +
        ((int)data->map.mini.foot_tab[0].coo.coo_x - (int)data->map.mini.player_coo.x);
	gap_y = (data->map.mini.foot_tab[0].coo.case_y - data->map.player_coo->y) * 64 +
        ((int)data->map.mini.foot_tab[0].coo.coo_y - (int)data->map.mini.player_coo.y);
	if ((abs(gap_x) < 20 && abs(gap_y) < 20))
		return (false);
	return (true);
}

void	save_and_move_foot(t_data *data, double rad)
{
	int	i;

	i = 0;
	if (check_gap(data) == false)
		return ;
	while(data->map.mini.foot_tab[i].is_save == true && i < 7)
		++i;
	while (i > 0)
	{
		data->map.mini.foot_tab[i] = data->map.mini.foot_tab[i - 1];
		--i;
	}
	data->map.mini.foot_tab[0].coo.case_x = data->map.player_coo->x;
	data->map.mini.foot_tab[0].coo.case_y = data->map.player_coo->y;
	data->map.mini.foot_tab[0].coo.coo_y = data->map.mini.player_coo.y;
	data->map.mini.foot_tab[0].coo.coo_x = data->map.mini.player_coo.x;
	data->map.mini.foot_tab[0].rad = rad;
	data->map.mini.foot_tab[0].foot_x = -1;
	data->map.mini.foot_tab[0].foot_y = -1;
	if (data->map.mini.foot_tab[1].is_save == true && data->map.mini.foot_tab[1].is_left == false)
		data->map.mini.foot_tab[0].is_left = true;
	else
		data->map.mini.foot_tab[0].is_left = false;
	data->map.mini.foot_tab[0].is_save = true;
}

void	angle_offset(t_data *data, int *start_x, int *start_y, int i)
{
	int	angle_deg;
	
	if (data->map.mini.foot_tab[i].foot_x != -1)
	{
		*start_x = data->map.mini.foot_tab[i].foot_x;
		*start_y = data->map.mini.foot_tab[i].foot_y;
		return ;
	}
	angle_deg = data->map.mini.foot_tab[i].rad * 180 / M_PI;
	if ((angle_deg >= 315 || angle_deg <= 45) || (angle_deg > 135 && angle_deg < 225))
	{
		if (data->map.mini.foot_tab[i].is_left == true)
			*start_x -= 5;
		else
			*start_x += 5;
		data->map.mini.foot_tab[i].foot_x = *start_x;
		data->map.mini.foot_tab[i].foot_y = *start_y;
	}
	else if ((angle_deg >= 45 && angle_deg <= 135) || (angle_deg >= 225 && angle_deg <= 315))
	{
		if (data->map.mini.foot_tab[i].is_left == true)
			*start_y += 5;
		else
			*start_y -= 5;
		data->map.mini.foot_tab[i].foot_x = *start_x;
		data->map.mini.foot_tab[i].foot_y = *start_y;
	}

}

void	set_foot_in_mini_map(t_data *data, int i, t_utils_mini *u, t_img img, double distance)
{
	int		gap_x;
	int		gap_y;
	unsigned int	color;

	gap_x = ((data->map.mini.foot_tab[i].coo.case_x - data->map.player_coo->x) * 64) + (data->map.mini.foot_tab[i].coo.coo_x - data->map.mini.player_coo.x);
		gap_y = ((data->map.mini.foot_tab[i].coo.case_y - data->map.player_coo->y) * 64) + (data->map.mini.foot_tab[i].coo.coo_y - data->map.mini.player_coo.y);
	while (u->y < img.height)
	{
		u->x = 0;
		while (u->x < img.width)
		{
			calc_value_player_mini_map_aff(u, &img, data->map.mini.foot_tab[i].rad);
			if (u->color != 0x00000000)
			{
				color = get_right_color(data->color, distance);
				set_pix_old_player(u, u->start_y + gap_y, u->start_x + gap_x, color);
			}
			++u->x;
		}
		++u->y;
	}
}

void	set_trail_foot(t_data *data, t_utils_mini *u)
{
	int	i;
	t_img	img;
	double distance;

	i = 1;
	distance = 0;
	while (data->map.mini.foot_tab[i].is_save == true && i < 8)
	{
		distance += 5;
		if (data->map.mini.foot_tab[i].is_left == true)
			img = data->map.mini.img[MINI_LEFT];
		else
			img = data->map.mini.img[MINI_RIGHT];
		u->y = 0;
		angle_offset(data, &u->start_x, &u->start_y, i);
		set_foot_in_mini_map(data, i , u, img, distance);
		++i;
	}
}
