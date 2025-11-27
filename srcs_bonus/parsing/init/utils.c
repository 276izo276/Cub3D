#include "parsing_bonus.h"
#include "time_bonus.h"

static void	init_wand(t_data *data)
{
	int	i;

	i = 1;
	data->wand.secret_wand = "BAGUETTE";
	data->wand.secret_sword = "SWORD";
	data->wand.wand_status[0] = true;
	data->wand.is_drop[0] = true;
	while (i < 6)
	{
		data->wand.wand_status[i] = false;
		data->wand.is_drop[i] = false;
		++i;
	}
	data->cheat_code_xp = "SAMAOUCH";
	data->cheat_code_life = "ALE-GUEL";
	data->wand.wand_status[5] = false;
	data->wand.wand_status[6] = false;
}

void	init_utils(t_data *data)
{
	init_wand(data);
	data->nb_msg = 7;
	data->display.time_remove = 10000;
	data->display.elapsed_time = 0;
	data->current_msg = 0;
	data->display.is_msg_active = true;
	data->display.is_first_msg = true;
	data->sensitivity = 100;
	data->pause_menu.selected = 0;
	data->pause_menu.elapsed = 0;
	data->spawn_frame = 5000;
	data->last_spawn = get_mtime();
	data->map.zoom = 128;
	data->map.last_mouse_x = 960;
	data->map.last_mouse_y = 555;
	data->map.is_center = false;
	data->map.pos_active_floo = init_t_coo(0, 0);
	data->screen->width = data->mlx.width;
	data->screen->height = data->mlx.height;
	data->lumos.x_wand = 0;
	data->lumos.y_wand = 0;
	data->lumos.count_frame = 0;
	data->lumos.active = false;
	data->portkey_is_active = false;
	data->display.player_height = 16;
}
