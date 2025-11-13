#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

#include <stdio.h>

void	player_invisible(t_data *data)
{
	if (data->player.invisible < 255)
	{
		// data->player.timer_invi = get_mtime();
		if (get_mtime() > data->player.timer_invi_short + 100)
		{
			data->player.timer_invi_short = get_mtime();
			data->player.invisible += 1;
		}
		if (get_mtime() > data->player.timer_invi + 5 * 1000)
		{
			data->player.timer_invi = get_mtime();
			data->popo[3].nb--;
			printf("time>>>%lld\n",(get_mtime() - data->player.timer_invi) / 1000);
			data->player.invisible = 255 - data->popo[3].nb * 55;
			if (data->player.invisible < 32)
				data->player.invisible = 32;
		}
		if (data->player.invisible > 255)
		{
			data->player.invisible = 255;
		}
		printf("invisible>>%d    \n",data->player.invisible);
	}
}

static void	handle_input_move(t_data *data, long long int cur)
{
	int i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		player_invisible(data);
		move_item(data);
		move_enemy(data);
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		// data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		data->player_moved = false;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (data->keycode[i] >= KEY_1 && data->keycode[i] <= KEY_4)
			{
				if (data->spell[data->spell_take[data->keycode[i] - KEY_1]].necessary_lvl <= data->player.xp)
				{
					data->cast_spell = data->spell_take[data->keycode[i] - KEY_1];
					data->keycode[i] = 0;
				}
			}
			else if (is_move_player(data, i))
				move = 1;
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
			else if (data->keycode[i] == KEY_5)
			{
				data->item = add_end_lst(create_item(data, MAC, 
					&data->player.coo, data->map.mini.deg), data->item, f_item);
				make_move_item(data->item->dt, 10);
				data->keycode[i] = 0;
			}
			else if (data->keycode[i] == KEY_6)
			{
				data->item = add_end_lst(create_item(data, LOGO_42, 
					&data->player.coo, data->map.mini.deg), data->item, f_item);
				make_move_item(data->item->dt, 10);
				data->keycode[i] = 0;
			}
			else if (data->keycode[i] == KEY_7)
			{
				data->item = add_end_lst(create_item(data, TIG, 
					&data->player.coo, data->map.mini.deg), data->item, f_item);
				make_move_item(data->item->dt, 10);
				data->keycode[i] = 0;
			}
			else if (data->keycode[i] == KEY_8)
			{
				data->item = add_end_lst(create_item(data, TIG, 
					&data->player.coo, data->map.mini.deg), data->item, f_item);
				make_move_item(data->item->dt, 10);
				data->keycode[i] = 0;
			}
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
void	handle_wall_msg(t_data *data, long long int cur)
{
	if (data->current_msg == 4 && data->display.elapsed_time == 0 && data->display.is_first_msg == true)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg == 4 && cur - data->display.elapsed_time > data->display.time_remove && data->display.is_first_msg == true)
	{
		remove_wall_msg(data);
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = false;
	}
	else if (data->current_msg == 7 && data->display.elapsed_time == 0)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg >= 7 && cur - data->display.elapsed_time > data->display.time_remove)
	{
		remove_wall_msg(data);
		data->current_msg = 0;
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = true;
	}
}

#include <stdio.h>

void	aff_xp(t_data *data)
{
	double			x;
	double			y;
	unsigned int	color;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + fmod(data->player.xp * 300, 300))
	{
		y = data->mlx.height - 30;
		while (y < data->mlx.height - 15)
		{
			
			*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = 0xFFFF00;
			y++;
		}
		x++;
	}
	x = data->mlx.width - 40;
	while (x < data->mlx.width - 10)
	{
		y = data->mlx.height - 38;
		while (y < data->mlx.height - 8)
		{
			unsigned int	a = ((unsigned int)((y - (data->mlx.height - 38)) / 30 * data->img[XP].height)) * data->img[XP].size_line;
			unsigned int	b = ((unsigned int)((x - (data->mlx.width - 40)) / 30 * data->img[XP].width)) * (data->img[XP].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[XP].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel >> 3)) = color;
			y++;
		}
		x++;
	}
	char *str;
	str = ft_itoa((int)data->player.xp);
	aff_text(str, 20, (t_coo){.x = calc_start_text(str, data->mlx.width - 365, data, 20), .y = data->mlx.height - 32}, data);
	free(str);
}

void	aff_life(t_data *data)
{
	double			x;
	double			y;
	unsigned int	color;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.life / 100 * 300))
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			
			*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel >> 3)) = 0x00FF00;
			y++;
		}
		x++;
	}
	while (x < data->mlx.width - 50)
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			
			*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel >> 3)) = 0xFF0000;
			y++;
		}
		x++;
	}
	x = data->mlx.width - 40;
	while (x < data->mlx.width - 20)
	{
		y = data->mlx.height - 57;
		while (y < data->mlx.height - 37)
		{
			unsigned int	a = ((unsigned int)((y - (data->mlx.height - 57)) / 20 * data->img[HEART].height)) * data->img[HEART].size_line;
			unsigned int	b = ((unsigned int)((x - (data->mlx.width - 40)) / 20 * data->img[HEART].width)) * (data->img[HEART].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[HEART].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel >> 3)) = color;
			y++;
		}
		x++;
	}
}

void	aff_shield(t_data *data)
{
	double			x;
	double			y;
	unsigned int	color;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.shield / 100 * 300))
	{
		y = data->mlx.height - 80;
		while (y < data->mlx.height - 65)
		{
			
			*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = 0x0000FF;
			y++;
		}
		x++;
	}
	x = data->mlx.width - 40;
	while (x < data->mlx.width - 20)
	{
		y = data->mlx.height - 82;
		while (y < data->mlx.height - 62)
		{
			unsigned int	a = ((unsigned int)((y - (data->mlx.height - 82)) / 20 * data->img[SHIELD].height)) * data->img[SHIELD].size_line;
			unsigned int	b = ((unsigned int)((x - (data->mlx.width - 40)) / 20 * data->img[SHIELD].width)) * (data->img[SHIELD].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[SHIELD].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel >> 3)) = color;
			y++;
		}
		x++;
	}
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

int	border_case_spell(double x, double y, double base_x, double base_y)
{
	double	dist_x;
	double	dist_y;
	double	ray;

	// dist_x = abs_value(base_x - x);
	// dist_y = abs_value(base_y - y);
	ray = 10;
	if (y < base_y - (32 - ray))
	{
		if (x < base_x - (32 - ray))
		{
			dist_x = abs_value(base_x - (32 - ray) - x);
			dist_y = abs_value(base_y - (32 - ray) - y);
		}
		else if (x > base_x + (32 - ray))
		{
			dist_x = abs_value(base_x + (32 - ray) - x);
			dist_y = abs_value(base_y - (32 - ray) - y);
		}
		else
			return (1);
	}
	else if (y > base_y + (32 - ray))
	{
		if (x < base_x - (32 - ray))
		{
			dist_x = abs_value(base_x - (32 - ray) - x);
			dist_y = abs_value(base_y + (32 - ray) - y);
		}
		else if (x > base_x + (32 - ray))
		{
			dist_x = abs_value(base_x + (32 - ray) - x);
			dist_y = abs_value(base_y + (32 - ray) - y);
		}
		else
			return (1);
	}
	else
		return (1);
	if (sqrt(dist_x * dist_x + dist_y * dist_y) > ray)
		return (0);
	return (1);
}

void	aff_popo(t_data *data)
{
	double			x;
	double			y;
	int				i;
	unsigned int	color;
	
	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 105 - 128;
			while (y < data->mlx.height - 105 - 64)
			{
				if (i == 0)
					color = 0xFF5555;
				else if (i == 1)
					color = 0x00BFFF;
				else
					color = 0x888888;
				if (i == 3)
				{
					if ((x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y <= data->mlx.height - 105 - 96 && data->popo[3].nb < 4)
					|| (x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && data->popo[3].nb < 3)
					|| (x >= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y >= data->mlx.height - 105 - 96 && data->popo[3].nb < 2)
					|| (x >= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y <= data->mlx.height - 105 - 96 && data->popo[3].nb < 1))
						color = darken_the_color(color);
				}
				if (color != 0x000000 && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 105 - 128))
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = color;
				y++;
			}
			x++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 115 - 128;
			while (y < data->mlx.height - 115 - 64)
			{
				unsigned int	a = ((unsigned int)((y - (data->mlx.height - 115 - 128)) / 64 * data->popo[i].img->height)) * data->popo[i].img->size_line;
				unsigned int	b = ((unsigned int)((x - (data->mlx.width - 350 + 64 * i + 13 * (i))) / 64 * data->popo[i].img->width)) * ( data->popo[i].img->bits_per_pixel >> 3);
				unsigned int	color = *(unsigned int *)(data->popo[i].img->data_addr + a + b);
				
				if (color != WHITE && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 105 - 128))
				{

					if (i == 3)
					{
						if ((x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y <= data->mlx.height - 105 - 96 && data->popo[3].nb < 4)
						|| (x <= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && data->popo[3].nb < 3)
						|| (x >= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y >= data->mlx.height - 105 - 96 && data->popo[3].nb < 1)
						|| (x >= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y > data->mlx.height - 105 - 96 && data->popo[3].nb < 2)
						|| (x >= data->mlx.width - 350 + 64 * (i) + 13 * (i) + (64 / 2) && y <= data->mlx.height - 105 - 96 && data->popo[3].nb < 1))
							color = darken_the_color(color);	
					}
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = color;
				}
				y++;
			}
			x++;
		}
		char *str;
		str = ft_itoa(data->popo[i].nb);
		aff_text(str, 25, (t_coo){.y=data->mlx.height - 115 - 80,.x=calc_start_text(str, 10 + data->mlx.width - 350 + 64 * i + 13 * (i), data, 25)}, data);
		aff_text(data->popo[i].key, 25, (t_coo){.y=data->mlx.height - 115 - 80,.x=calc_start_text(data->popo[i].key,  50 + data->mlx.width - 350 + 64 * i + 13 * (i), data, 25)}, data);
		i++;
	}
}

void	aff_spell(t_data *data)
{
	double			x;
	double			y;
	int				i;
	unsigned int	color;

	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 90 - 64;
			while (y < data->mlx.height - 90)
			{
				define_spell_color(data, &color, i);
				if (color != 0x000000 && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 90 - 64))
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = color;
				y++;
			}
			x++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 90 - 64;
			while (y < data->mlx.height - 90)
			{
				// define_spell_color(data, &color, i);
				unsigned int	a = ((unsigned int)((y - (data->mlx.height - 90 - 64)) / 64 * data->spell[data->spell_take[i]].icn->height)) *  data->spell[data->spell_take[i]].icn->size_line;
				unsigned int	b = ((unsigned int)((x - (data->mlx.width - 350 + 64 * i + 13 * (i))) / 64 * data->spell[data->spell_take[i]].icn->width)) * ( data->spell[data->spell_take[i]].icn->bits_per_pixel >> 3);
				unsigned int	color = *(unsigned int *)(data->spell[data->spell_take[i]].icn->data_addr + a + b);
				if (get_mtime() < data->spell[data->spell_take[i]].end_time + data->spell[data->spell_take[i]].base_cooldown * 1000)
					color = darken_the_color(color);
				if (color != WHITE && color != RED && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 90 - 64))
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				if (data->spell[data->spell_take[i]].necessary_lvl > data->player.xp)
				{
					unsigned int	a = ((unsigned int)((y - (data->mlx.height - 90 - 64)) / 64 * data->img[SPELL_LOCK].height)) *  data->img[SPELL_LOCK].size_line;
					unsigned int	b = ((unsigned int)((x - (data->mlx.width - 350 + 64 * i + 13 * (i))) / 64 * data->img[SPELL_LOCK].width)) * ( data->img[SPELL_LOCK].bits_per_pixel >> 3);
					unsigned int	color = *(unsigned int *)(data->img[SPELL_LOCK].data_addr + a + b);
					if (color != YELLOW && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 90 - 64))
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				}
				y++;
			}
			x++;
		}
		if (get_mtime() < data->spell[data->spell_take[i]].end_time + data->spell[data->spell_take[i]].base_cooldown * 1000)
		{
			char *str;
			str = ft_itoa(((data->spell[data->spell_take[i]].end_time + data->spell[data->spell_take[i]].base_cooldown * 1000) - get_mtime()) / 1000 + 1);
			aff_text(str, 32, (t_coo){.x = calc_start_text(str, data->mlx.width - 350 + 64 * i + 13 * (i) + 32, data, 32), .y = data->mlx.height - 90 - 64 + 16}, data);
			free(str);
		}
		i++;
	}
}

void	aff_img_effect_info(t_img *img, int nb_effect, t_data *data)
{
	double	x;
	double	y;

	x = data->mlx.width - 370 - (nb_effect * 20) - 30;
	while (x < data->mlx.width - 370 - (nb_effect * 20) - 10)
	{
		y = data->mlx.height - 35;
		while (y < data->mlx.height - 15)
		{
			unsigned int	a = ((unsigned int)((y - (data->mlx.height - 35)) / 20 * img->height)) * img->size_line;
			unsigned int	b = ((unsigned int)((x - (data->mlx.width - 370 - (nb_effect * 20) - 30)) / 20 * img->width)) * ( img->bits_per_pixel >> 3);
			unsigned int	color = *(unsigned int *)(img->data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = color;
			y++;
		}
		x++;
	}
}

void	aff_effect_info(t_data *data)
{
	int		nb_effect;

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
				unsigned int	a = ((unsigned int)((y - (data->mlx.height - 70)) / 30 * img->height)) * img->size_line;
				unsigned int	b = ((unsigned int)((x - (data->mlx.width - 350 - 40)) / 30 * img->width)) * ( img->bits_per_pixel >> 3);
				unsigned int	color = *(unsigned int *)(img->data_addr + a + b);
				if (color != WHITE)
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8)) = color;
				y++;
			}
			x++;
		}
	}
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
	if (data->player.life <= 0 && data->player.life >= -114) // Lock le heal
		data->player.life -= 1;
	if (data->player.life <= -115)
	{
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
void	update_enemy(t_data *data)
{
	int	random;
	int	x;
	int	y;

	y = 0;
	data->spider_factor = max(10, 100 - (data->player.xp * 10));
	data->elem_factor = min(15, data->player.xp * 5);
	if (data->player.xp >= 3)
		data->dementor_factor = min(35, (data->player.xp - 2) * 2);
	if (data->player.xp >= 7)
		data->wolf_factor = min(40, (data->player.xp - 6) * 2);
	double total_factor = data->spider_factor + data->dementor_factor + data->elem_factor + data->wolf_factor;
	data->spider_factor = (data->spider_factor / total_factor) * 100;
	data->elem_factor = (data->elem_factor / total_factor) * 100;
	data->dementor_factor = (data->dementor_factor / total_factor) * 100;
	data->wolf_factor = (data->wolf_factor / total_factor) * 100;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->nb_enemy < 5 + data->player.xp * 2 && data->map.tabmap[y][x] == '0')
			{
				random = rand() % 15000;
				if (random <= data->player.xp * 2)
				{
					random = rand() % 100;
					total_factor = data->spider_factor;
					if (random <= total_factor)
					{
						// printf("add spider\n");
						data->enemy = add_end_lst(init_enemy(',', (t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
						if (!data->enemy)
							f_exit(data, 1);
						data->nb_enemy++;
					}
					else
					{
						total_factor += data->elem_factor;
						if (random <= total_factor)
						{

							data->enemy = add_end_lst(init_enemy('>', (t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
							if (!data->enemy)
								f_exit(data, 1);
							// printf("add elem\n");
						}
						else
						{
							total_factor += data->dementor_factor;
							if (random <= total_factor)
							{
	
								data->enemy = add_end_lst(init_enemy('.', (t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
								if (!data->enemy)
									f_exit(data, 1);
								// printf("add dementor\n");
							}
							else
							{
								total_factor += data->wolf_factor;
								if (random <= total_factor)
								{
		
									data->enemy = add_end_lst(init_enemy('<', (t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
									if (!data->enemy)
										f_exit(data, 1);
									// printf("add wolf\n");
								}
							}
						}
					}
				}
			}
			++x;
		}
		++y;
	}
}

void	spawn_sorcerer(t_data *data, char type)
{
	int	y;
	int	x;
	int	random_y;
	int	random_x;
	int	attempts;

	attempts = 0;
	random_y = 0;
	printf("type > %c\n", type);
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
		attempts++;
	}
	data->enemy = add_end_lst(init_enemy(type, (t_fcoo){.case_x=random_x,.case_y=random_y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
	if (!data->enemy)
		f_exit(data, 1);
	data->nb_enemy++;
}

void	update_sorcerer(t_data *data)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (data->sorcerer[i].is_alive == false)
			spawn_sorcerer(data, data->sorcerer[i].type);
		++i;
	}
}
int	game_loop(t_data *data)
{
	long long int	cur;
	
	cur = get_mtime();
	update_sorcerer(data);
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
		// restart(data);
	else
	{
		//DBG1printf("0\n");
		// data->player.life -= .5;
		if (cur - data->last_spawn >= data->spawn_frame)
		{
			update_enemy(data);
			data->last_spawn = get_mtime();
			// data->player.xp++;
		}
		handle_input_move(data, cur);
		if (data->cast_spell != -1)
			data->spell[data->cast_spell].call(data, data->cast_spell);
		handle_wall_msg(data, cur);
		//DBG1printf("5\n");
		if (data->time_fps + 1000 / FPS < cur)
		{
			// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
			data->time_fps = cur;
			pthread_barrier_wait(&data->barrier_background);
			// sem_post(data->sem_background);
			// sem_post(data->sem_background);
			// ray_launch(data);
			pthread_barrier_wait(&data->barrier_background);
			// display_game(data);
			// pthread_mutex_lock(&data->m_data_ray);
			// sem_post(data->sem_display);
			// sem_post(data->sem_display);
			// sem_post(data->sem_display);
			// sem_post(data->sem_display);
			// data->player.life--;
			pthread_barrier_wait(&data->barrier_display);
			pthread_barrier_wait(&data->barrier_display);

			// int	x1 = 500;
			// int	y1 = 500;
			// while (x1 < 800)
			// {
			// 	y1 = 500;
			// 	while (y1 < 800)
			// 	{
			// 		if (sqrt((x1 - 650) * (x1 - 650)
			// 			+ (y1 - 650) * (y1 - 650))
			// 			< 150)
			// 		{
			// 			*(unsigned int *)(data->screen->data_addr + (y1 * data->screen->size_line) + (x1
			// 			* data->screen->bits_per_pixel >> 3)) = 0xFF0000;
			// 		}
			// 		y1++;
			// 	}
			// 	x1++;

			// }
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
			// display_blood_border(data);
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
			// pthread_mutex_unlock(&data->m_data_ray);
			// pthread_barrier_wait(&data->barrier);
		}
		//DBG1printf("6\n");
	}
	// is_new_level(data);
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
