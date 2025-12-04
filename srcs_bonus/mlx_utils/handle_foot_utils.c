#include "color_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>

static void	get_new_color_comp(t_data *data, t_utils_mini *u)
{
	data->aff.old_color = *(unsigned int *)u->pixel_addr;
	data->aff.r_old = (data->aff.old_color >> 16) & 255;
	data->aff.g_old = (data->aff.old_color >> 8) & 255;
	data->aff.b_old = data->aff.old_color & 255;
	data->aff.a_new = (data->aff.color >> 24) & 255;
	data->aff.r_new = (data->aff.color >> 16) & 255;
	data->aff.g_new = (data->aff.color >> 8) & 255;
	data->aff.b_new = data->aff.color & 255;
	data->aff.r_new = (int)((1 - (data->aff.a_new / 255.0)) * data->aff.r_old
			+ (data->aff.a_new / 255.0) * data->aff.r_new);
	data->aff.g_new = (int)((1 - (data->aff.a_new / 255.0)) * data->aff.g_old
			+ (data->aff.a_new / 255.0) * data->aff.g_new);
	data->aff.b_new = (int)((1 - (data->aff.a_new / 255.0)) * data->aff.b_old
			+ (data->aff.a_new / 255.0) * data->aff.b_new);
	*(unsigned int *)u->pixel_addr = (data->aff.r_new << 16)
		+ (data->aff.g_new << 8) + data->aff.b_new;
}

void	set_pix_old_player(t_utils_mini *u, int start_y, int start_x,
		t_data *data)
{
	if (start_x < 0 || start_x + u->xfloat >= u->size || start_y < 0 || start_y
		+ u->yfloat >= u->size)
		return ;
	if (u->color != YELLOW)
	{
		if (((int)ceil(u->yfloat) + start_y) < 0 || ((int)ceil(u->yfloat)
				+ start_y) >= data->u.size || ((int)ceil(u->xfloat)
				+ start_x) < 0 || ((int)ceil(u->xfloat)
				+ start_x) >= data->u.size)
			return ;
		u->pixel_addr = u->mmap.data_addr + (((int)ceil(u->yfloat) + start_y)
				* u->mmap.size_line + ((int)ceil(u->xfloat) + start_x)
				* (u->mmap.bits_per_pixel / 8));
		get_new_color_comp(data, u);
		if (((int)floor(u->yfloat) + start_y) < 0 || ((int)floor(u->yfloat)
				+ start_y) >= data->u.size || ((int)floor(u->xfloat)
				+ start_x) < 0 || ((int)floor(u->xfloat)
				+ start_x) >= data->u.size)
			return ;
		u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat) + start_y)
				* u->mmap.size_line + ((int)floor(u->xfloat) + start_x)
				* (u->mmap.bits_per_pixel / 8));
		get_new_color_comp(data, u);
	}
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

void	calc_gap(t_data *data, int i, int *gap_x, int *gap_y)
{
	*gap_x = ((data->map.mini.foot_tab[i].coo.case_x - data->player.coo.case_x)
			* 64) + (data->map.mini.foot_tab[i].coo.coo_x
			- data->player.coo.coo_x);
	*gap_y = ((data->map.mini.foot_tab[i].coo.case_y - data->player.coo.case_y)
			* 64) + (data->map.mini.foot_tab[i].coo.coo_y
			- data->player.coo.coo_y);
}
