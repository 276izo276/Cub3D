#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

static void	handle_input_move(t_data *data, long long int cur)
{
	int i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		data->player_moved = false;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (data->keycode[i] >= KEY_1 && data->keycode[i] <= KEY_3)
			{
				data->cast_spell = data->spell_take[data->keycode[i] - KEY_1];
				data->keycode[i] = 0;
			}
			else if (is_move_player(data, i))
				move = 1;
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
		if (move)
			handle_move(&data->map, &data->map.mini, data);
	}
	data->player.damage.slow_take = 0;
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
				if (color != WHITE && color != RED && border_case_spell(x, y, 32 + data->mlx.width - 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 90 - 64))
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				y++;
			}
			x++;
		}
		i++;
	}
}

void	take_damage(t_data *data)
{
	double	damage;

	damage = data->player.damage.damage_take;
	data->player.shield -= damage;
	if (data->player.shield < 0)
	{
		data->player.life += data->player.shield;
		data->player.shield = 0;
	}
	data->player.damage.damage_take = 0;
	if (data->player.damage.poison_take > 0)
	{
		data->player.damage.poison_take--;
		data->player.life--;
	}
	if (data->player.life <= 0)
		f_exit(data, 1);
}

int	game_loop(t_data *data)
{
	long long int	cur;
	
	cur = get_mtime();
	if (data->status == MENU)
		display_menu(data);
	else if (data->status == PAUSE)
	{
		handle_pause_menu(data, cur);
	}
	else if (data->status == MAP)
		display_floo_map(data);
	else
	{
		//DBG1printf("0\n");
		take_damage(data);
		handle_input_move(data, cur);
		if (data->cast_spell != -1)
			data->spell[data->cast_spell].call(data, data->cast_spell);
		move_enemy(data);
		move_item(data);
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
			pthread_barrier_wait(&data->barrier_display);
			pthread_barrier_wait(&data->barrier_display);
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
			// if (data->life > 0)
			// 	--data->life;
			// else if (data->life <= 0 && data->life >= -92)
			// 	data->life -= 5;
			display_blood_border(data);
			aff_xp(data);
			aff_life(data);
			aff_shield(data);
			aff_spell(data);
			display_hand(data);
			aff_mini_map(data);
			handle_door(data);
			// pthread_mutex_unlock(&data->m_data_ray);
			// pthread_barrier_wait(&data->barrier);
		}
		//DBG1printf("6\n");
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
