#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "texture_bonus.h"

void	v_norm_d(t_mini *mini, t_data *data)
{
	double	v_normalize;
	int		i;

	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->dy = mini->dy / v_normalize;
	mini->dx = mini->dx / v_normalize;
	i = -1;
	while (++i < KEYCODE_NB)
	{
		if (data->keycode[i] == KEY_S)
		{
			mini->dy *= .6;
			mini->dx *= .6;
		}
		else if (data->keycode[i] == KEY_A || data->keycode[i] == KEY_D)
		{
			mini->dy *= .9;
			mini->dx *= .9;
		}
		if (data->keycode[i] == KEY_SHIFT)
		{
			mini->dy *= 1.6;
			mini->dx *= 1.6;
		}
	}
}

void	v_norm_sd(t_mini *mini, t_data *data)
{
	double	v_normalize;
	int		i;

	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->sdy = mini->sdy / v_normalize;
	mini->sdx = mini->sdx / v_normalize;
	i = -1;
	while (++i < KEYCODE_NB)
	{
		if (data->keycode[i] == KEY_S)
		{
			mini->sdy *= .6;
			mini->sdx *= .6;
		}
		else if (data->keycode[i] == KEY_A || data->keycode[i] == KEY_D)
		{
			mini->sdy *= .9;
			mini->sdx *= .9;
		}
		if (data->keycode[i] == KEY_SHIFT)
		{
			mini->sdy *= 1.6;
			mini->sdx *= 1.6;
		}
	}
}

void	calc_dx_dy(t_data *data, int keycode, t_mini *mini)
{
	int	angle;

	(void)data;
	angle = 0;
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		data->player.is_front = true;
		angle = 180;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		angle = 0;
		data->player.is_front = false;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		angle = 90;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		angle = 270;
	if (angle % 180 != 0)
	{
		mini->sdx += sin(mini->rad + angle * (M_PI / 180.0));
		mini->sdy += cos(mini->rad + angle * (M_PI / 180.0));
	}
	mini->dx += sin(mini->rad + angle * (M_PI / 180.0));
	mini->dy += cos(mini->rad + angle * (M_PI / 180.0));
}

void	recalc_x(t_data *data, t_mini *mini, t_map *map)
{
	mini->nx = data->player.coo.coo_x + mini->dx;
	mini->cx = 0;
	if (mini->nx < 0)
	{
		if (map->tabmap[data->player.coo.case_y]
			[data->player.coo.case_x - 1] != '1')
		{
			mini->cx = -1;
			mini->nx = 64 + mini->nx;
		}
	}
	else if (mini->nx >= 64)
	{
		if (map->tabmap[data->player.coo.case_y]
			[data->player.coo.case_x + 1] != '1')
		{
			mini->cx = 1;
			mini->nx = mini->nx - 64;
		}
	}
}

void	recalc_y(t_data *data, t_mini *mini, t_map *map)
{
	mini->ny = data->player.coo.coo_y + mini->dy;
	mini->cy = 0;
	if (mini->ny < 0)
	{
		if (map->tabmap[data->player.coo.case_y - 1]
			[data->player.coo.case_x] != '1')
		{
			mini->cy = -1;
			mini->ny = 64 + mini->ny;
		}
	}
	else if (mini->ny >= 64)
	{
		if (map->tabmap[data->player.coo.case_y + 1]
			[data->player.coo.case_x] != '1')
		{
			mini->cy = 1;
			mini->ny = mini->ny - 64;
		}
	}
}
