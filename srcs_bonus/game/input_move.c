#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <color_bonus.h>
#include <math.h>
#include "time_bonus.h"

bool	is_move_player(t_data *data, int i)
{
	if (data->keycode[i] == KEY_W || data->keycode[i] == KEY_D
		|| data->keycode[i] == KEY_A || data->keycode[i] == KEY_S
		|| data->keycode[i] == KEY_1 || data->keycode[i] == KEY_UP
		|| data->keycode[i] == KEY_DOWN || data->keycode[i] == KEY_LEFT
		|| data->keycode[i] == KEY_RIGHT || data->keycode[i] == KEY_2)
		return (true);
	return (false);
}

int	mouse_move(int x, int y, t_data *data)
{
	double	dx;
	double	dy;

	if ((x != data->mlx.width / 2 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT) && data->status != FLOO_MAP
		&& data->status != MAP)
	{
		data->map.mini.deg += (double)-(x - data->mlx.width / 2) / data->sensitivity;
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
		calc_left_point_player(data);
		calc_right_point_player(data);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
			data->mlx.height / 2);
	}
	else if (data->status == FLOO_MAP || data->status == MAP)
	{
		dx = x - data->mlx.width / 2;
		dy = y - data->mlx.height / 2;
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
		data->mlx.height / 2);
		double sensitivity = (50 / data->sensitivity) / data->map.zoom;
		if (dx != 0 || dy != 0)
		{
			data->map.last_pos_x += dx * sensitivity;
			data->map.last_pos_y += dy * sensitivity;
		}
		data->map.last_mouse_x = x;
		data->map.last_mouse_y = y;
	}
	return (0);
}

void	change_dir_verti(t_data *data)
{
	if (data->map.tabmap[data->map.pos_active_floo->y][data->map.pos_active_floo->x + 1] != '1')
	{
		data->player.coo.coo_x = 42.0;
		data->map.mini.deg = 270;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
	else
	{
		data->player.coo.coo_x = 22.0;
		data->map.mini.deg = 90;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
}

void	change_dir_not_verti(t_data *data)
{
	if (data->map.tabmap[data->map.pos_active_floo->y + 1][data->map.pos_active_floo->x] != '1')
	{
		data->player.coo.coo_y = 42.0;
		data->map.mini.deg = 180;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
	else
	{
		data->player.coo.coo_y = 22.0;
		data->map.mini.deg = 0;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
}

void	handle_mouse_click(t_data *data)
{
		if (data->map.door_map[data->map.pos_active_floo->y][data->map.pos_active_floo->x]->is_verti == true)
		{
			data->player.coo.coo_y = 32;
			change_dir_verti(data);
		}
		else
		{
			data->player.coo.coo_x = 32.0;
			change_dir_not_verti(data);
		}
}

int	mouse_key(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (key == 4 && data->status == GAME)
	{
		if (data->wand.nb_wand == 6)
			data->wand.nb_wand = 0;
		else
			++data->wand.nb_wand;
		while (data->wand.wand_status[data->wand.nb_wand] == false && data->wand.nb_wand < 5)
			++data->wand.nb_wand;
		if (data->wand.wand_status[data->wand.nb_wand] == false)
			data->wand.nb_wand = 0;
	}
	else if (key == 5 && data->status == GAME)
	{
		if (data->wand.nb_wand == 0)
			data->wand.nb_wand = 6;
		else
			--data->wand.nb_wand;
		while (data->wand.wand_status[data->wand.nb_wand] == false && data->wand.nb_wand > 0 )
			--data->wand.nb_wand;
		if (data->wand.wand_status[data->wand.nb_wand] == false)
			data->wand.nb_wand = 0;
	}
	if (key == 1 && data->map.floo_active == true && data->status == FLOO_MAP)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open = false;
		data->player.coo.case_x = data->map.pos_active_floo->x;
		data->player.coo.case_y = data->map.pos_active_floo->y;
		handle_mouse_click(data);
		data->map.zoom = 128;
		data->status = GAME;
	}
	if (key == 4 && data->map.zoom <= 128)
		data->map.zoom *= 2;
	else if (key == 5 && data->map.zoom >= 32)
		data->map.zoom /= 2;
	else if (key == 9)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		if (data->status == GAME)
		{
			data->status = MAP;
			data->map.last_pos_x = data->player.coo.case_x;
			data->map.last_pos_y = data->player.coo.case_y;
		}
		else if (data->status == MAP)
		{
			data->status = GAME;
		}
	}
	else if (key == 8)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		if (data->status == GAME)
		{
			data->status = MENU_SPELL;
			data->selected = 0;
			data->spell_menu.start_time = get_mtime();
		}
		else if (data->status == MENU_SPELL)
		{
			data->status = GAME;
			data->spell_menu.selected = -1;
		}
	}
	return (0);
}

int	is_key_pressed(t_data *data, int keycode)
{
	int	i;

	i = 0;
	while (i < KEYCODE_NB)
	{
		if (data->keycode[i] == keycode)
			return (1);
		i++;
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	int	i;

	// printf("Key released: %d\n", keycode);
	i = 0;

	if (keycode == KEY_Z)
		data->popo[0].active = 0;
	else if (keycode == KEY_X)
		data->popo[1].active = 0;
	else if (keycode == KEY_C)
		data->popo[2].active = 0;
	else if (keycode == KEY_V)
		data->popo[3].active = 0;
	while (i < KEYCODE_NB)
	{
			data->popo[3].active = 0;
		if (data->keycode[i] == keycode)
			data->keycode[i] = 0;
		if (keycode == KEY_ALT)
		{
			mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width,
				data->mlx.height);
		}
		else if (keycode == KEY_SHIFT)
			data->map.mini.speed = 1.5;
		i++;
	}
	return (0);
}

static void	key_select_coa(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
	{
		if (data->selected == 0)
			data->selected = 3;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		if (data->selected == 3)
			data->selected = 0;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_ENTER)
	{
		data->player.color = data->coa[data->selected].color;
		data->player.coa = data->selected;
		data->coa[data->player.coa].xp = data->player.xp;
		data->selected = 0;
		int i = 0;
		while (i < 9)
		{
			if (data->sorcerer[i].color != data->player.color)
				data->sorcerer[i].is_alive = false;
			++i;
		}
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

static void key_select_hand(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
	{
		if (data->selected == 1)
			data->selected -= 1;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		if (data->selected == 0)
			data->selected += 1;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_ENTER)
	{
		if (data->selected == 1)
			data->is_right_handed = true;
		else
			data->is_right_handed = false;
		select_right_hand(data);
		data->status = GAME;
		// init_img_msg(data);
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

void handle_death_menu_keys(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		if (data->selected == 1)
			data->selected -= 1;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		if (data->selected == 0)
			data->selected += 1;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_ENTER)
	{
		if (data->selected == 1)
			f_exit(data, 0); 
		else
			restart(data);
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 0);
}

static void	handle_menu_keys(int keycode, t_data *data)
{
	if (data->player.color == 0)
		key_select_coa(keycode, data);
	else if (data->is_right_handed == 0)
		key_select_hand(keycode, data);
}

void	handle_exit_map(int keycode, t_data *data)
{
	int	angle_deg;

	angle_deg = data->map.mini.deg;
	if (keycode == KEY_ESCAPE && data->status == FLOO_MAP)
	{
		data->status = GAME;
		if (angle_deg >= 315 || angle_deg <= 45)
			data->player.coo.coo_y = 42;
		else if (angle_deg > 135 && angle_deg < 225)
			data->player.coo.coo_y = 22;
		else if (angle_deg >= 45 && angle_deg <= 135)
			data->player.coo.coo_x = 42;
		else if (angle_deg >= 225 && angle_deg <= 315)
			data->player.coo.coo_x = 22;
		data->map.mini.deg += 180;
		data->map.mini.deg = fmod(data->map.mini.deg, 360);
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open = false;
		data->map.zoom = 128;
	}
	else if (keycode == KEY_ESCAPE)
	{
		data->status = GAME;
		data->map.zoom = 128;
	}
}

static void	handle_map_keys(int keycode, t_data *data)
{
	handle_exit_map(keycode, data);
	if (keycode == KEY_W)
		data->map.last_pos_y -= 1;
	else if (keycode == KEY_S)
		data->map.last_pos_y += 1;
	else if (keycode == KEY_A)
		data->map.last_pos_x -= 1;
	else if (keycode == KEY_D)
		data->map.last_pos_x += 1;
	else if (keycode == KEY_SPACE)
	{
		data->map.last_pos_x = data->player.coo.case_x;
		data->map.last_pos_y = data->player.coo.case_y;
	}
	if (keycode == KEY_1 && data->map.zoom <= 128)
		data->map.zoom *= 2;
	else if (keycode == KEY_2 && data->map.zoom >= 32)
		data->map.zoom /= 2;
	
}

bool	handle_floo_open(t_data *data)
{
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open == true)
			return (false);
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x]->is_floo_open = true;
		return (true);
	}
	else if (data->map.tabmap[data->player.coo.case_y - 1][data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y - 1][data->player.coo.case_x]->is_floo_open == true)
			return (false);
		data->map.door_map[data->player.coo.case_y - 1][data->player.coo.case_x]->is_floo_open = true;
		return (true);
	}
	else if (data->map.tabmap[data->player.coo.case_y + 1][data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y + 1][data->player.coo.case_x]->is_floo_open == true)
			return (false);
		data->map.door_map[data->player.coo.case_y + 1][data->player.coo.case_x]->is_floo_open = true;
		return (true);
	}
	else if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x + 1] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x + 1]->is_floo_open == true)
			return (false);
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x + 1]->is_floo_open = true;
		return (true);
	}
	else if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x - 1] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x - 1]->is_floo_open == true)
			return (false);
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x - 1]->is_floo_open = true;
		return (true);
	}
	return (false);
}

	// #include <stdio.h>
void	is_easter_egg(int keycode, t_data *data)
{
	if (keycode == data->wand.secret_wand[data->wand.count_egg] + 32)
		data->wand.count_egg++;
	if (data->wand.count_egg == 7 && data->wand.wand_status[5] == false)
	{
		data->wand.wand_status[5] = true;
		data->wand.nb_wand = 5;
	}
	else if (keycode == data->wand.secret_sword[data->wand.count_sword] + 32)
		data->wand.count_sword++;
	if (data->wand.count_sword == 5 && data->wand.wand_status[6] == false)
	{
		data->wand.wand_status[6] = true;
		data->wand.nb_wand = 6;
	}
}

void	cheat_code(t_data *data, int keycode)
{
	if (keycode == data->cheat_code_xp[data->index_xp] + 32)
	{
		data->index_xp++;
		if (data->index_xp == 8)
		{
			data->index_xp = 0;
			data->player.xp += 20;
		}
	}
	else if (keycode == data->cheat_code_life[data->index_life] + 32
	|| (keycode == KEY_MINUS && data->index_life == 3))
	{
		data->index_life++;
		if (data->index_life == 8)
		{
			data->player.life = 100;
			data->player.shield = 100;
			data->index_life = 0;
		}
	}
	if(data->wand.wand_status[5] != true || data->wand.wand_status[6] != true)
		is_easter_egg(keycode, data);
}

#include <stdio.h>
int	key_press(int keycode, t_data *data)
{
	int	i;

	// printf("keycode >%d\n",keycode);
	cheat_code(data, keycode);
	if (data->status == MENU)
	{
		handle_menu_keys(keycode, data);
		return (0);
	}
	else if (data->status == FLOO_MAP || data->status == MAP)
	{
		handle_map_keys(keycode, data);
		return (0);
	}
	else if (data->status == MENU_SPELL)
	{
		handle_menu_spell_keys(keycode, data);
		return (0);
	}
	else if (data->status == MENU_DEATH || data->status == MENU_END)
	{
		handle_death_menu_keys(keycode, data);
		return (0);
	}
	i = 0;
	while (data->keycode[i] != 0 && i < KEYCODE_NB)
		i++;
	// if (keycode == KEY_5)
	// 	handle_floo_open(data);
	if (keycode == KEY_CTRL)
	{
		if (data->display.player_height != 16) // a changer on a plus besoins un bool suffit
			data->display.player_height = 16;
		else
			data->display.player_height = 18;
	}
	else if (keycode == KEY_TAB)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		if (data->status == GAME)
			data->status = PAUSE;
		else
			data->status = GAME;
	}
	else if (keycode == KEY_N)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		if (data->status == GAME)
		{
			data->status = MENU_SPELL;
			data->spell_menu.start_time = get_mtime();
			data->selected = 0;
		}
	}
	else if (keycode == KEY_M)
	{
		data->sound = add_end_lst(create_sound(data, 28), data->sound, free_sound);
		data->status = MAP;
		data->map.last_pos_x = data->player.coo.case_x;
		data->map.last_pos_y = data->player.coo.case_y;
	}
	else
		data->keycode[i] = keycode;
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	else if (keycode == KEY_SHIFT)
		data->map.mini.speed = 3;
	return (0);
}
