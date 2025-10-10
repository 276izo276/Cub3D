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
			else if (data->keycode[i] >= KEY_1 && data->keycode[i] <= KEY_2)
				data->cast_spell = data->spell_take[data->keycode[i] - KEY_1];
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
	int	x;
	int	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + fmod(data->player.xp * 300, 300))
	{
		y = data->mlx.height - 35;
		while (y < data->mlx.height - 20)
		{
			
			*(unsigned int *)(data->screen->data_addr + (y - MARGIN) * data->screen->size_line + (x) * (data->screen->bits_per_pixel / 8)) = 0xFFFF00;
			y++;
		}
		x++;
	}
}


void	aff_life(t_data *data)
{
	int	x;
	int	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.life / 100 * 300))
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			
			*(unsigned int *)(data->screen->data_addr + (y - MARGIN) * data->screen->size_line + (x) * (data->screen->bits_per_pixel / 8)) = 0x00FF00;
			y++;
		}
		x++;
	}
	while (x < data->mlx.width - 50)
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			
			*(unsigned int *)(data->screen->data_addr + (y - MARGIN) * data->screen->size_line + (x) * (data->screen->bits_per_pixel / 8)) = 0xFF0000;
			y++;
		}
		x++;
	}
}


void	aff_shield(t_data *data)
{
	int	x;
	int	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.shield / 100 * 300))
	{
		y = data->mlx.height - 75;
		while (y < data->mlx.height - 60)
		{
			
			*(unsigned int *)(data->screen->data_addr + (y - MARGIN) * data->screen->size_line + (x) * (data->screen->bits_per_pixel / 8)) = 0x0000FF;
			y++;
		}
		x++;
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
		take_damage(data);
		handle_input_move(data, cur);
		if (data->cast_spell != -1)
			data->spell[data->cast_spell].call(data, data->cast_spell);
		move_enemy(data);
		move_item(data);
		handle_wall_msg(data, cur);
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
			display_hand(data);
			aff_mini_map(data);
			handle_door(data);
			// pthread_mutex_unlock(&data->m_data_ray);
			// pthread_barrier_wait(&data->barrier);
		}
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
