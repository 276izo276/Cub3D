#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void	player_invisible(t_data *data)
{
	if (data->player.invisible < 255)
	{
		if (get_mtime() > data->player.timer_invi_short + 100)
		{
			data->player.timer_invi_short = get_mtime();
			data->player.invisible += 1;
		}
		if (get_mtime() > data->player.timer_invi + 5 * 1000)
		{
			data->player.timer_invi = get_mtime();
			data->popo[3].nb--;
			data->player.invisible = 255 - data->popo[3].nb * 55;
			if (data->player.invisible < 32)
				data->player.invisible = 32;
		}
		if (data->player.invisible > 255)
		{
			data->player.invisible = 255;
		}
	}
}

static void	handle_sound(t_data *data)
{
	t_sound	*sound;
	t_lst	*lst;
	t_lst	*next;
	int		result;

	lst = get_first_elem_lst(data->sound);
	while (lst)
	{
		sound = lst->dt;
		next = lst->next;
		if (get_mtime() > sound->start + sound->duration * 1000)
		{
			result = waitpid(sound->pid, NULL, WNOHANG);
			if (result == 0 && sound->duration != -1)
			{
				kill(sound->pid, SIGTERM);
				data->sound = remove_f_elem_lst(lst);
			}
			else if (sound->duration != -1)
				data->sound = remove_f_elem_lst(lst);
		}
		lst = next;
	}
}

void	handle_input_cond(t_data *data, int i, int *move)
{
	if (data->keycode[i] >= KEY_1 && data->keycode[i] <= KEY_4)
	{
		if (data->spell[data->spell_take[data->keycode[i]
			- KEY_1]].necessary_lvl <= data->player.xp)
		{
			data->cast_spell = data->spell_take[data->keycode[i] - KEY_1];
			data->keycode[i] = 0;
		}
	}
	else if (is_move_player(data, i))
		*move = 1;
	else if (data->keycode[i] == KEY_E)
		rotate_right(data);
	else if (data->keycode[i] == KEY_Q)
		rotate_left(data);
	else if (data->keycode[i] == KEY_Z)
		data->popo[0].call(data);
	else if (data->keycode[i] == KEY_X)
		data->popo[1].call(data);
	else if (data->keycode[i] == KEY_C)
		data->popo[2].call(data);
	else if (data->keycode[i] == KEY_V)
		data->popo[3].call(data);
}

static void	handle_input_move(t_data *data, long long int cur)
{
	int	i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		player_invisible(data);
		move_item(data);
		move_enemy(data);
		handle_sound(data);
		data->time_move = cur;
		data->player_moved = false;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			handle_input_cond(data, i, &move);
			i++;
		}
		if (move)
			handle_move(&data->map, &data->map.mini, data);
		take_damage(data);
	}
}

void	remove_wall_msg(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == '1')
			{
				if (data->map.wall_map[y][x]->msg_nb < data->current_msg)
					data->map.wall_map[y][x]->is_active = false;
			}
			++x;
		}
		++y;
	}
}

void	handle_msg_utils(t_data *data, long long int cur)
{
	if (data->current_msg == 7 && data->display.elapsed_time == 0)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg >= 7 && cur
		- data->display.elapsed_time > data->display.time_remove)
	{
		remove_wall_msg(data);
		data->current_msg = 0;
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = true;
	}
}

void	handle_wall_msg(t_data *data, long long int cur)
{
	if (data->current_msg == 4 && data->display.elapsed_time == 0
		&& data->display.is_first_msg == true)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg == 4 && cur
		- data->display.elapsed_time > data->display.time_remove
		&& data->display.is_first_msg == true)
	{
		remove_wall_msg(data);
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = false;
	}
}

void	aff_xp_color(t_data *data, double *y, double *x)
{
	unsigned int	color;
	unsigned int	a;
	unsigned int	b;

	*x = data->mlx.width - 40;
	while (*x < data->mlx.width - 10)
	{
		*y = data->mlx.height - 38;
		while (*y < data->mlx.height - 8)
		{
			a = ((unsigned int)((*y - (data->mlx.height - 38)) / 30
						* data->img[XP].height)) * data->img[XP].size_line;
			b = ((unsigned int)((*x - (data->mlx.width - 40)) / 30
						* data->img[XP].width))
				* (data->img[XP].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[XP].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
						* data->screen->size_line + ((int)(*x))
						* (data->screen->bits_per_pixel >> 3)) = color;
			(*y)++;
		}
		(*x)++;
	}
}

void	aff_xp(t_data *data)
{
	double	x;
	double	y;
	char	*str;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + fmod(data->player.xp * 300, 300))
	{
		y = data->mlx.height - 30;
		while (y < data->mlx.height - 15)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel / 8)) = 0xFFFF00;
			y++;
		}
		x++;
	}
	aff_xp_color(data, &y, &x);
	str = ft_itoa((int)data->player.xp);
	aff_text(str, 20, (t_coo){.x = calc_start_text(str, data->mlx.width - 365,
			data, 20), .y = data->mlx.height - 32}, data);
	free(str);
}

void	aff_heart_color(t_data *data, double x, double y)
{
	t_aff	aff;

	aff.a = ((unsigned int)((y - (data->mlx.height - 57)) / 20
				* data->img[HEART].height)) * data->img[HEART].size_line;
	aff.b = ((unsigned int)((x - (data->mlx.width - 40)) / 20
				* data->img[HEART].width))
		* (data->img[HEART].bits_per_pixel >> 3);
	aff.color = *(unsigned int *)(data->img[HEART].data_addr + aff.a + aff.b);
	if (aff.color != WHITE)
		*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
				* data->screen->size_line + ((int)(x))
				* (data->screen->bits_per_pixel >> 3)) = aff.color;
}

void	aff_life_heart(t_data *data)
{
	double			x;
	double			y;

	x = data->mlx.width - 40;
	while (x < data->mlx.width - 20)
	{
		y = data->mlx.height - 57;
		while (y < data->mlx.height - 37)
		{
			aff_heart_color(data, x, y);
			y++;
		}
		x++;
	}
}

void	aff_life_red(t_data *data, double *x, double *y)
{
	while (*x < data->mlx.width - 50)
	{
		*y = data->mlx.height - 55;
		while (*y < data->mlx.height - 40)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
					* data->screen->size_line + ((int)(*x))
					* (data->screen->bits_per_pixel >> 3)) = 0xFF0000;
			(*y)++;
		}
		(*x)++;
	}
}

void	aff_life(t_data *data)
{
	double	x;
	double	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.life / 100 * 300))
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel >> 3)) = 0x00FF00;
			y++;
		}
		x++;
	}
	aff_life_red(data, &x, &y);
	aff_life_heart(data);
}

void	aff_shield_color(t_data *data, double *x, double *y)
{
	unsigned int	color;
	unsigned int	a;
	unsigned int	b;

	*x = data->mlx.width - 40;
	while (*x < data->mlx.width - 20)
	{
		*y = data->mlx.height - 82 - 1;
		while (++(*y) < data->mlx.height - 62)
		{
			a = ((unsigned int)((*y - (data->mlx.height - 82)) / 20
						* data->img[SHIELD].height))
				* data->img[SHIELD].size_line;
			b = ((unsigned int)((*x - (data->mlx.width - 40)) / 20
						* data->img[SHIELD].width))
				* (data->img[SHIELD].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[SHIELD].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
						* data->screen->size_line + ((int)(*x))
						* (data->screen->bits_per_pixel >> 3)) = color;
		}
		(*x)++;
	}
}

void	aff_shield(t_data *data)
{
	double	x;
	double	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.shield / 100
			* 300))
	{
		y = data->mlx.height - 80;
		while (y < data->mlx.height - 65)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel / 8)) = 0x0000FF;
			y++;
		}
		x++;
	}
	aff_shield_color(data, &x, &y);
}

void	define_spell_color(t_data *data, unsigned int *color, int i)
{
	*color = 0x000000;
	if (data->spell[data->spell_take[i]].class == DARK_SPELL)
		*color = 0x062B16;
	else if (data->spell[data->spell_take[i]].class == HEAL_SPELL)
		*color = 0x7CFC00;
	else if (data->spell[data->spell_take[i]].class == SUMMON_SPELL)
		*color = 0xFFE436;
	else if (data->spell[data->spell_take[i]].class == OFFENSIVE_SPELL)
		*color = 0x720004;
	else if (data->spell[data->spell_take[i]].class == DEFENSIVE_SPELL)
		*color = 0x00008B;
	else if (data->spell[data->spell_take[i]].class == CLASIC_SPELL)
		*color = 0xFFFFFF;
}

int	border_case_top(t_aff *aff)
{
	if (aff->dx < aff->base_x - (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x - (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y - (32 - aff->ray) - aff->dy);
	}
	else if (aff->dx > aff->base_x + (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x + (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y - (32 - aff->ray) - aff->dy);
	}
	else
		return (1);
	return (0);
}

int	border_case_bottom(t_aff *aff)
{
	if (aff->dx < aff->base_x - (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x - (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y + (32 - aff->ray) - aff->dy);
	}
	else if (aff->dx > aff->base_x + (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x + (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y + (32 - aff->ray) - aff->dy);
	}
	else
		return (1);
	return (0);
}

int	border_case_spell(double x, double y, double base_x, double base_y)
{
	t_aff	aff;

	aff.dist_x = abs_value(base_x - x);
	aff.dist_y = abs_value(base_y - y);
	aff.ray = 10;
	aff.base_x = base_x;
	aff.base_y = base_y;
	aff.dy = y;
	aff.dx = x;
	if (aff.dy < aff.base_y - (32 - aff.ray))
	{
		if (border_case_top(&aff))
			return (1);
	}
	else if (aff.dy > base_y + (32 - aff.ray))
	{
		if (border_case_bottom(&aff))
			return (1);
	}
	else
		return (1);
	if (sqrt(aff.dist_x * aff.dist_x + aff.dist_y * aff.dist_y) > aff.ray)
		return (0);
	return (1);
}

int	cond_back_color(t_data *data, double x, double y, double i)
{
	if ((x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2)
			&& y <= data->mlx.height - 105 - 96 && data->popo[3].nb < 4)
		|| (x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2)
			&& data->popo[3].nb < 3) || (x >= data->mlx.width - 350 + 64 * (i)
			+ 13 * (i) + (64 / 2) && y >= data->mlx.height - 105 - 96
			&& data->popo[3].nb < 2) || (x >= data->mlx.width - 350 + 64 * (i)
			+ 13 * (i) + (64 / 2) && y <= data->mlx.height - 105 - 96
			&& data->popo[3].nb < 1))
		return (1);
	return (0);
}

void	set_back_color(t_data *data, double *y, double x, int i)
{
	unsigned int	color;

	*y = data->mlx.height - 105 - 128;
	while (*y < data->mlx.height - 105 - 64)
	{
		if (i == 0)
			color = 0xFF5555;
		else if (i == 1)
			color = 0x00BFFF;
		else
			color = 0x888888;
		if (i == 3)
		{
			if (cond_back_color(data, x, *y, i))
				color = darken_the_color(color);
		}
		if (color != 0x000000 && border_case_spell(x, *y, 32 + data->mlx.width
				- 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 105 - 128))
			*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel / 8)) = color;
		(*y)++;
	}
}

void	popo_back_color(t_data *data)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			set_back_color(data, &y, x, i);
			x++;
		}
		i++;
	}
}

void	popo_img(t_data *data, double *y, double *x, int i)
{
	t_aff	aff;

	while (*y < data->mlx.height - 115 - 64)
	{
		aff.a = ((unsigned int)((*y - (data->mlx.height - 115 - 128)) / 64
					* data->popo[i].img->height))
			* data->popo[i].img->size_line;
		aff.b = ((unsigned int)((*x - (data->mlx.width - 350 + 64 * i + 13
							* (i))) / 64 * data->popo[i].img->width))
			* (data->popo[i].img->bits_per_pixel >> 3);
		aff.color = *(unsigned int *)(data->popo[i].img->data_addr + aff.a
				+ aff.b);
		if (aff.color != WHITE && border_case_spell(*x, *y, 32 + data->mlx.width
				- 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 105 - 128))
		{
			if (i == 3)
				if (cond_back_color(data, *x, *y, i))
					aff.color = darken_the_color(aff.color);
			*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
					* data->screen->size_line + ((int)(*x))
					* (data->screen->bits_per_pixel / 8)) = aff.color;
		}
		(*y)++;
	}
	(*x)++;
}

void	aff_popo(t_data *data)
{
	double	x;
	double	y;
	int		i;
	char	*str;

	popo_back_color(data);
	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 115 - 128;
			popo_img(data, &y, &x, i);
		}
		str = ft_itoa(data->popo[i].nb);
		aff_text(str, 25, (t_coo){.y = data->mlx.height - 115 - 80,
			.x = calc_start_text(str, 10 + data->mlx.width - 350 + 64 * i + 13
				* (i), data, 25)}, data);
		aff_text(data->popo[i].key, 25, (t_coo){.y = data->mlx.height - 115
			- 80, .x = calc_start_text(data->popo[i].key, 50 + data->mlx.width
				- 350 + 64 * i + 13 * (i), data, 25)}, data);
		i++;
	}
}

void	aff_spell_color(t_data *data)
{
	int				i;
	unsigned int	color;
	double			x;
	double			y;

	i = -1;
	while (++i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i) - 1;
		while (++x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 90 - 64 - 1;
			while (++y < data->mlx.height - 90)
			{
				define_spell_color(data, &color, i);
				if (color != 0x000000 && border_case_spell(x, y, 32
						+ data->mlx.width - 350 + 64 * i + 13 * (i), 32
						+ data->mlx.height - 90 - 64))
					*(unsigned int *)(data->screen->data_addr + ((int)(y
									- MARGIN)) * data->screen->size_line
							+ ((int)(x)) * (data->screen->bits_per_pixel
								/ 8)) = color;
			}
		}
	}
}

void	darken_color_spell(t_aff *aff, t_data *data, int i)
{
	aff->a = ((unsigned int)((aff->dy - (data->mlx.height - 90 - 64)) / 64
				* data->spell[data->spell_take[i]].icn->height))
		* data->spell[data->spell_take[i]].icn->size_line;
	aff->b = ((unsigned int)((aff->dx - (data->mlx.width - 350 + 64 * i + 13
						* (i))) / 64
				* data->spell[data->spell_take[i]].icn->width))
		* (data->spell[data->spell_take[i]].icn->bits_per_pixel >> 3);
	aff->color = *(unsigned int *)(data->spell[
			data->spell_take[i]].icn->data_addr
			+ aff->a + aff->b);
	if (get_mtime() < data->spell[data->spell_take[i]].end_time
		+ data->spell[data->spell_take[i]].base_cooldown * 1000)
		aff->color = darken_the_color(aff->color);
	if (aff->color != WHITE && aff->color != RED && border_case_spell(aff->dx,
			aff->dy, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32
			+ data->mlx.height - 90 - 64))
		*(unsigned int *)(data->screen->data_addr + ((int)(aff->dy - MARGIN))
				* data->screen->size_line + ((int)(aff->dx))
				* (data->screen->bits_per_pixel / 8)) = aff->color;
}

void	level_spell(t_aff *aff, t_data *data, int i)
{
	if (data->spell[data->spell_take[i]].necessary_lvl > data->player.xp)
	{
		aff->a = ((unsigned int)((aff->dy - (data->mlx.height - 90 - 64)) / 64
					* data->img[SPELL_LOCK].height))
			* data->img[SPELL_LOCK].size_line;
		aff->b = ((unsigned int)((aff->dx - (data->mlx.width - 350 + 64 * i + 13
							* (i))) / 64 * data->img[SPELL_LOCK].width))
			* (data->img[SPELL_LOCK].bits_per_pixel >> 3);
		aff->color = *(unsigned int *)(data->img[SPELL_LOCK].data_addr + aff->a
				+ aff->b);
		if (aff->color != YELLOW && border_case_spell(aff->dx, aff->dy, 32
				+ data->mlx.width - 350 + 64 * i + 13 * (i), 32
				+ data->mlx.height - 90 - 64))
			*(unsigned int *)(data->screen->data_addr + ((int)(aff->dy
							- MARGIN)) * data->screen->size_line
					+ ((int)(aff->dx)) * (data->screen->bits_per_pixel
						/ 8)) = aff->color;
	}
}

void	aff_spell_img(t_data *data, int i)
{
	t_aff	aff;

	aff.dx = data->mlx.width - 350 + 64 * i + 13 * (i);
	while (aff.dx < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
	{
		aff.dy = data->mlx.height - 90 - 64;
		while (aff.dy < data->mlx.height - 90)
		{
			darken_color_spell(&aff, data, i);
			level_spell(&aff, data, i);
			aff.dy++;
		}
		aff.dx++;
	}
}

void	aff_spell(t_data *data)
{
	int		i;
	char	*str;

	aff_spell_color(data);
	i = 0;
	while (i < 4)
	{
		aff_spell_img(data, i);
		if (get_mtime() < data->spell[data->spell_take[i]].end_time
			+ data->spell[data->spell_take[i]].base_cooldown * 1000)
		{
			str = ft_itoa(((data->spell[data->spell_take[i]].end_time
							+ data->spell[data->spell_take[i]].base_cooldown
							* 1000) - get_mtime()) / 1000 + 1);
			aff_text(str, 32, (t_coo){.x = calc_start_text(str, data->mlx.width
					- 350 + 64 * i + 13 * (i) + 32, data, 32),
				.y = data->mlx.height - 90 - 64 + 16}, data);
			free(str);
		}
		i++;
	}
}

void	aff_img_effect_info(t_img *img, int nb_effect, t_data *data)
{
	double			x;
	double			y;
	unsigned int	a;
	unsigned int	b;
	unsigned int	color;

	x = data->mlx.width - 370 - (nb_effect * 20) - 30;
	while (x < data->mlx.width - 370 - (nb_effect * 20) - 10)
	{
		y = data->mlx.height - 35 - 1;
		while (++y < data->mlx.height - 15)
		{
			a = ((unsigned int)((y - (data->mlx.height - 35)) / 20
						* img->height)) * img->size_line;
			b = ((unsigned int)((x - (data->mlx.width - 370 - (nb_effect * 20)
								- 30)) / 20 * img->width))
				* (img->bits_per_pixel >> 3);
			color = *(unsigned int *)(img->data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
						* data->screen->size_line + ((int)(x))
						* (data->screen->bits_per_pixel / 8)) = color;
		}
		x++;
	}
}

void	aff_effect_info_utils(t_data *data, int nb_effect)
{
	if (data->player.damage.curse_force_take > 0)
	{
		aff_img_effect_info(&data->img[CURSE], nb_effect, data);
		nb_effect++;
	}
	if (data->player.episkey_heal > 0)
	{
		aff_img_effect_info(&data->img[EPISKEY_ICN], nb_effect, data);
		nb_effect++;
	}
	if (data->player.vul_sanen_heal > 0)
	{
		aff_img_effect_info(&data->img[HEART], nb_effect, data);
		nb_effect++;
	}
}

void	aff_effect_info(t_data *data)
{
	int	nb_effect;

	nb_effect = 0;
	if (data->player.damage.fire_force_take > 0)
	{
		aff_img_effect_info(&data->img[FLAME], nb_effect, data);
		nb_effect++;
	}
	if (data->player.damage.poison_force_take > 0)
	{
		aff_img_effect_info(&data->img[POISON], nb_effect, data);
		nb_effect++;
	}
	if (data->player.damage.slow_force_take > 0)
	{
		aff_img_effect_info(&data->img[SLOW], nb_effect, data);
		nb_effect++;
	}
	aff_effect_info_utils(data, nb_effect);
}

void	img_protego(t_data *data, double x, double y, t_img *img)
{
	t_aff	aff;

	aff.a = ((unsigned int)((y - (data->mlx.height - 70)) / 30 * img->height))
		* img->size_line;
	aff.b = ((unsigned int)((x - (data->mlx.width - 350 - 40)) / 30
				* img->width)) * (img->bits_per_pixel >> 3);
	aff.color = *(unsigned int *)(img->data_addr + aff.a + aff.b);
	if (aff.color != WHITE)
		*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
				* data->screen->size_line + ((int)(x))
				* (data->screen->bits_per_pixel / 8)) = aff.color;
}

void	aff_protego(t_data *data)
{
	double	x;
	double	y;
	t_img	*img;

	if (data->player.protego > 0)
	{
		img = &data->img[SHIELD_1 + data->player.protego - 1];
		x = data->mlx.width - 350 - 40;
		while (x < data->mlx.width - 350 - 10)
		{
			y = data->mlx.height - 70;
			while (y < data->mlx.height - 40)
			{
				img_protego(data, x, y, img);
				y++;
			}
			x++;
		}
	}
}

void	damage_effect(t_data *data)
{
	data->player.damage.damage_take = 0;
	if (data->player.damage.poison_frame_take > 0)
	{
		data->player.life -= data->player.damage.poison_force_take;
		data->player.damage.poison_frame_take--;
		if (data->player.damage.poison_frame_take <= 0)
			data->player.damage.poison_force_take = 0;
	}
	if (data->player.damage.fire_frame_take > 0)
	{
		data->player.life -= data->player.damage.fire_force_take;
		data->player.damage.fire_frame_take--;
		if (data->player.damage.fire_frame_take <= 0)
			data->player.damage.fire_force_take = 0;
	}
	if (data->player.damage.curse_frame_take > 0)
	{
		data->player.life -= data->player.damage.curse_force_take;
		data->player.damage.curse_frame_take--;
		if (data->player.damage.curse_frame_take <= 0)
			data->player.damage.curse_force_take = 0;
	}
	if (data->player.life <= 0 && data->player.life >= -114)
		data->player.life -= 1;
}

void	sound_dead(t_data *data)
{
	f_all_lst(data->sound);
	data->sound = NULL;
	data->sound = add_end_lst(create_sound(data, 27), data->sound, free_sound);
}

void	take_damage(t_data *data)
{
	double	damage;

	damage = data->player.damage.damage_take;
	while (damage > 0 && data->player.protego > 0)
	{
		damage -= 5;
		data->player.protego--;
	}
	if (damage < 0)
		damage = 0;
	data->player.shield -= damage;
	if (data->player.shield < 0)
	{
		data->player.life += data->player.shield;
		data->player.shield = 0;
	}
	damage_effect(data);
	if (data->player.life <= -115)
	{
		sound_dead(data);
		data->status = MENU_DEATH;
		data->selected = 0;
	}
}

double	max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

void	spawn_after_dementor(t_data *data, double total_factor, int random)
{
	total_factor += data->wolf_factor;
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('<',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
	}
}

void	spawn_after_elem(t_data *data, double total_factor, int random)
{
	total_factor += data->dementor_factor;
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('.',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
	}
	else
	{
		spawn_after_dementor(data, total_factor, random);
	}
}

void	spawn_after_spider(t_data *data, double total_factor, int random)
{
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('>',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
	}
	else
	{
		spawn_after_elem(data, total_factor, random);
	}
}

void	spawn_enemy_utils(t_data *data, double total_factor, int random)
{
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy(',',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
	}
	else
	{
		total_factor += data->elem_factor;
		spawn_after_spider(data, total_factor, random);
	}
}

void	spawn_enemy(t_data *data, double total_factor)
{
	int	x;
	int	y;
	int	random;

	y = -1;
	while (data->map.tabmap[y])
	{
		x = -1;
		while (data->map.tabmap[y][++x])
		{
			if (data->nb_enemy < 5 + data->player.xp * 2
				&& data->map.tabmap[++y][x] == '0')
			{
				random = rand() % 15000;
				if (random <= data->player.xp * 2)
				{
					random = rand() % 100;
					total_factor = data->spider_factor;
					data->aff.x = x;
					data->aff.y = y;
					spawn_enemy_utils(data, total_factor, random);
				}
			}
		}
	}
}

void	update_enemy(t_data *data)
{
	double	total_factor;

	data->spider_factor = max(10, 100 - (data->player.xp * 10));
	data->elem_factor = min(15, data->player.xp * 5);
	if (data->player.xp >= 3)
		data->dementor_factor = min(35, (data->player.xp - 2) * 2);
	if (data->player.xp >= 7)
		data->wolf_factor = min(40, (data->player.xp - 6) * 2);
	total_factor = data->spider_factor + data->dementor_factor
		+ data->elem_factor + data->wolf_factor;
	data->spider_factor = (data->spider_factor / total_factor) * 100;
	data->elem_factor = (data->elem_factor / total_factor) * 100;
	data->dementor_factor = (data->dementor_factor / total_factor) * 100;
	data->wolf_factor = (data->wolf_factor / total_factor) * 100;
	spawn_enemy(data, total_factor);
}

int	spawn_sorcerer_utils(t_data *data, char type, int y, int x)
{
	int	attempts;
	int	random_y;
	int	random_x;

	attempts = 0;
	random_y = 0;
	while (++attempts < 1000)
	{
		y = 0;
		while (data->map.tabmap[y])
			++y;
		random_y = rand() % y;
		x = 0;
		while (data->map.tabmap[random_y][x])
			++x;
		random_x = rand() % x;
		if (data->map.tabmap[random_y][random_x] == '0')
			break ;
	}
	if (attempts >= 1000)
		return (1);
	data->enemy = add_end_lst(init_enemy(type, (t_fcoo){.case_x = random_x,
				.case_y = random_y, .coo_y = 32, .coo_x = 32}, data,
				data->map.mini.deg), data->enemy, f_enemy);
	return (0);
}

void	spawn_sorcerer(t_data *data, char type)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (spawn_sorcerer_utils(data, type, y, x))
		return ;
	if (!data->enemy)
		f_exit(data, 1);
	check_enemy_can_escape(data, data->enemy);
}

void	portkey_utils(t_data *data, int attempts, int random_x, int random_y)
{
	if (attempts >= 1000)
		return ;
	data->item = add_end_lst(create_item(data, PORTKEY,
				&(t_fcoo){.case_x = random_x, .case_y = random_y, .coo_y = 32,
				.coo_x = 32}, data->map.mini.deg), data->item, f_item);
	if (!data->item)
		f_exit(data, 1);
	data->item = add_end_lst(create_item(data, PILLAR,
				&(t_fcoo){.case_x = random_x, .case_y = random_y, .coo_y = 32,
				.coo_x = 32}, data->map.mini.deg), data->item, f_item);
	if (!data->item)
		f_exit(data, 1);
	data->portkey_is_active = true;
}

void	spawn_portkey(t_data *data)
{
	int	y;
	int	x;
	int	random_y;
	int	random_x;
	int	attempts;

	attempts = 0;
	random_y = 0;
	while (attempts < 1000)
	{
		y = 0;
		while (data->map.tabmap[y])
			++y;
		random_y = rand() % y;
		x = 0;
		while (data->map.tabmap[random_y][x])
			++x;
		random_x = rand() % x;
		if (data->map.tabmap[random_y][random_x] == '0')
			break ;
		++attempts;
	}
	portkey_utils(data, attempts, random_x, random_y);
}

void	update_sorcerer(t_data *data)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (data->sorcerer[i].is_alive == false
			&& data->player.color != data->sorcerer[i].color)
			spawn_sorcerer(data, data->sorcerer[i].type);
		++i;
	}
}
int	game_loop(t_data *data)
{
	long long int	cur;

	cur = get_mtime();
	if (data->portkey_is_active == false && data->player.xp >= 16)
		spawn_portkey(data);
	if (data->status == MENU)
		display_menu(data);
	else if (data->status == PAUSE)
		handle_pause_menu(data, cur);
	else if (data->status == FLOO_MAP)
		display_floo_map(data);
	else if (data->status == MAP)
		display_floo_map(data);
	else if (data->status == MENU_SPELL)
		handle_spells_menu(data);
	else if (data->status == MENU_DEATH)
		handle_death_menu(data);
	else if (data->status == MENU_END)
		handle_end_menu(data);
	else
	{
		update_sorcerer(data);
		if (cur - data->last_spawn >= data->spawn_frame)
		{
			update_enemy(data);
			data->last_spawn = get_mtime();
		}
		handle_input_move(data, cur);
		if (data->cast_spell != -1)
			data->spell[data->cast_spell].call(data, data->cast_spell);
		handle_wall_msg(data, cur);
		if (data->time_fps + 1000 / FPS < cur)
		{
			printf("fps >>>%lld     \n", 1000 / (cur - data->time_fps));
			data->time_fps = cur;
			pthread_barrier_wait(&data->barrier_background);
			pthread_barrier_wait(&data->barrier_background);
			pthread_barrier_wait(&data->barrier_display);
			pthread_barrier_wait(&data->barrier_display);
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
				data->screen->img, 0, 0);
			aff_xp(data);
			aff_life(data);
			aff_shield(data);
			aff_spell(data);
			aff_popo(data);
			aff_effect_info(data);
			spell_protego(data);
			spell_heal(data);
			aff_protego(data);
			display_hand(data);
			aff_mini_map(data);
			handle_door(data);
		}
		// DBG1printf("6\n");
	}
	// is_new_level(data);
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
