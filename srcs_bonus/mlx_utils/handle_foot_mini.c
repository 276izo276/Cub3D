#include "struct_bonus.h"
#include "color_bonus.h"
#include "texture_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include <stdlib.h>


#include <stdio.h>
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

	//DBG1printf("start_y>%d, start_x>%d,   u->yfloat>%lf,   u->x_float>%lf,   color>%u\n",start_y,start_x,u->yfloat,u->xfloat,color);
	if (start_x < 0 || start_x + u->xfloat >= u->size || start_y < 0 || start_y + u->yfloat >= u->size)
		return ;
	if (u->color != YELLOW)
	{
		// for ceil
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

		// for floor
		u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat)
		+ start_y) * u->mmap.size_line
		+ ((int)floor(u->xfloat) + start_x)
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
	}
	//DBG1printf("end\n");
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

void	get_good_offset_y(t_data *data, int angle_deg, int *start_y, int i)
{
	if ((angle_deg >= 45 && angle_deg <= 135))
	{
		if (data->map.mini.foot_tab[i].is_left == false)
			*start_y -= 12;
	}
	else if ((angle_deg >= 225 && angle_deg <= 315))
	{
		if (data->map.mini.foot_tab[i].is_left == false)
			*start_y += 12;
	}
}

void	get_good_offset_x(t_data *data, int angle_deg, int *start_x, int i)
{
	if ((angle_deg >= 315 || angle_deg <= 45))
	{
		if (data->map.mini.foot_tab[i].is_left == false)
			*start_x += 12;
	}
	else if ((angle_deg > 135 && angle_deg < 225))
	{
		if (data->map.mini.foot_tab[i].is_left == false)
			*start_x -= 12;
	}
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
	get_good_offset_x(data, angle_deg, start_x, i);
	get_good_offset_y(data, angle_deg, start_y, i);
	data->map.mini.foot_tab[i].foot_x = *start_x;
	data->map.mini.foot_tab[i].foot_y = *start_y;

}

#include <stdio.h>

void	set_foot_in_mini_map(t_data *data, int i, t_utils_mini *u, t_img img, double distance)
{
	int		gap_x;
	int		gap_y;
	unsigned int	color;

	gap_x = ((data->map.mini.foot_tab[i].coo.case_x - data->map.player_coo->x) * 64) + (data->map.mini.foot_tab[i].coo.coo_x - data->map.mini.player_coo.x);
	gap_y = ((data->map.mini.foot_tab[i].coo.case_y - data->map.player_coo->y) * 64) + (data->map.mini.foot_tab[i].coo.coo_y - data->map.mini.player_coo.y);
	//DBG1printf("gapx >%d   gapy>%d\n",gap_x,gap_y);
	while (u->y < img.height)
	{
		u->x = 0;
		while (u->x < img.width)
		{
			//DBG1printf("a1\n");
			calc_value_player_mini_map_aff(u, &img, data->map.mini.foot_tab[i].rad);
			//DBG1printf("a2\n");
			if (u->color != 0x00000000)
			{
				//DBG1printf("a3\n");
				color = get_right_color(data->color, distance);
				//DBG1printf("a4\n");
				set_pix_old_player(u, u->start_y + gap_y, u->start_x + gap_x, color);
			}
			//DBG1printf("a5\n");
			++u->x;
		}
		++u->y;
	}
}

#include <stdio.h>

void	set_trail_foot(t_data *data, t_utils_mini *u)
{
	int	i;
	t_img	img;
	double distance;

	i = 1;
	distance = 0;
	//DBG1printf("i1\n");
	while (data->map.mini.foot_tab[i].is_save == true && i < 8)
	{
		distance += 5;
		if (data->map.mini.foot_tab[i].is_left == true)
			img = data->map.mini.img[MINI_LEFT];
		else
			img = data->map.mini.img[MINI_RIGHT];
		u->y = 0;
		//DBG1printf("i2  i>%d\n",i);
		angle_offset(data, &u->start_x, &u->start_y, i);
		//DBG1printf("i3\n");
		set_foot_in_mini_map(data, i , u, img, distance);
		//DBG1printf("i4\n");
		++i;
	}
}
