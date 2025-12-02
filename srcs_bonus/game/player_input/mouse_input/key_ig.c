#include "cub3d_bonus.h"
#include "time_bonus.h"

void	mouse_key_ig(t_data *data, int key)
{
	if (key == 4 && data->status == GAME)
	{
		if (data->wand.nb_wand == 6)
			data->wand.nb_wand = 0;
		else
			++data->wand.nb_wand;
		while (data->wand.wand_status[data->wand.nb_wand] == false
			&& data->wand.nb_wand < 5)
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
		while (data->wand.wand_status[data->wand.nb_wand] == false
			&& data->wand.nb_wand > 0)
			--data->wand.nb_wand;
		if (data->wand.wand_status[data->wand.nb_wand] == false)
			data->wand.nb_wand = 0;
	}
}

void	mouse_key_spell_menu(t_data *data)
{
	data->sound = add_end_lst(create_sound(data, 27), data->sound, free_sound);
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
