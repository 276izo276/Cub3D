#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <color_bonus.h>
#include <math.h>


static int	menu_border_case_spell(double x, double y, double base_x, double base_y)
{
	double	dist_x;
	double	dist_y;
	double	ray;

	ray = 10;
	if (y < base_y - (64 - ray))
	{
		if (x < base_x - (64 - ray))
		{
			dist_x = abs_value(base_x - (64 - ray) - x);
			dist_y = abs_value(base_y - (64 - ray) - y);
		}
		else if (x > base_x + (64 - ray))
		{
			dist_x = abs_value(base_x + (64 - ray) - x);
			dist_y = abs_value(base_y - (64 - ray) - y);
		}
		else
			return (1);
	}
	else if (y > base_y + (64 - ray))
	{
		if (x < base_x - (64 - ray))
		{
			dist_x = abs_value(base_x - (64 - ray) - x);
			dist_y = abs_value(base_y + (64 - ray) - y);
		}
		else if (x > base_x + (64 - ray))
		{
			dist_x = abs_value(base_x + (64 - ray) - x);
			dist_y = abs_value(base_y + (64 - ray) - y);
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

static void	display_spell_take(t_data *data)
{
	unsigned int	color;
	double				y;
	double				x;
	int				i;

	i = 0;
	while (i < 4)
	{
		x =  634 + 128 * i + 40 * (i);
		while (x < 634 + 128 * (i + 1) + 40 * (i))
		{
			y = 460;
			while (y < 460 + 128)
			{
				unsigned int	a = ((unsigned int)((y - 460) / 128 * data->spell[data->spell_take[i]].icn->height)) *  data->spell[data->spell_take[i]].icn->size_line;
				unsigned int	b = ((unsigned int)((x - (634 + 128 * i + 40 * (i))) / 128 * data->spell[data->spell_take[i]].icn->width)) * ( data->spell[data->spell_take[i]].icn->bits_per_pixel >> 3);
				color = *(unsigned int *)(data->spell[data->spell_take[i]].icn->data_addr + a + b);

				if (menu_border_case_spell(x, y, 64 + 634 + 128 * i + 40 * (i), 64 + 460))
				{
					if (data->selected != i)
						color = darken_the_color(color);
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				}
				y++;
			}
			x++;
		}
		i++;
	}
}

void	display_name(t_data *data, int i, int pos_x)
{
	unsigned int	color;
	int				x;
	int				y;

	if (i % 8 == 0 && i != 0)
		data->spell_menu.name_pos_y += 110;
	else if (i == 20)
		data->spell_menu.name_pos_y += 35;
	y = 0;
	if (!data->spell[i].icn_name)
		return ;
	while (y < data->spell[i].icn_name->height)
	{
		x = 0;
		while (x < data->spell[i].icn_name->width)
		{
			color = get_texture_pixel(data->spell[i].icn_name, x, y);
			if (color != YELLOW)
			{
				if (data->selected - 4 != i)
					color = darken_the_color(color);
				pixel_put(data, x + pos_x, y + data->spell_menu.name_pos_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	display_spell_list(t_data *data)
{
	unsigned int	color;
	double				y;
	double				x;
	int				i;
	int				final_pos_y;

	data->spell_menu.name_pos_y = 570;
	final_pos_y = 660;
	i = 0;
	while (i < 20)
	{		
		x =  440 + 64 * (i % 8) + 71 * (i % 8);
		while (x < 440 + 64 * (i % 8 + 1) + 71 * (i % 8))
		{
			y = final_pos_y;
			while (y < final_pos_y + 64)
			{
				if(data->spell[i].icn)
				{
					unsigned int	a = ((unsigned int)((y - final_pos_y) / 64 * data->spell[i].icn->height)) *  data->spell[i].icn->size_line;
					unsigned int	b = ((unsigned int)((x - (440 + 64 * (i % 8) + 71 * (i % 8))) / 64 * data->spell[i].icn->width)) * ( data->spell[i].icn->bits_per_pixel >> 3);
					color = *(unsigned int *)(data->spell[i].icn->data_addr + a + b);
				}
				if (border_case_spell(x, y, 32 + 440 + 64 * (i % 8) + 71 * (i % 8), 32 + final_pos_y))
				{
					if (data->spell_menu.selected != i)
						color = darken_the_color(color);
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				}
				y++;
			}
			x++;
		}
		display_name(data, i, 410 + 64 * (i % 8) + 72 * (i % 8));
		i++;
		if (i % 8 == 0)
			final_pos_y += 120;
	}
	final_pos_y += 30;
	while (i < 22)
	{
		x =  600 + 64 * (i % 8) + 71 * (i % 8);
		while (x < 600 + 64 * (i % 8 + 1) + 71 * (i % 8))
		{
			y = final_pos_y;
			while (y < final_pos_y + 64)
			{
				if(data->spell[i].icn)
				{
					unsigned int	a = ((unsigned int)((y - final_pos_y) / 64 * data->spell[i].icn->height)) *  data->spell[i].icn->size_line;
					unsigned int	b = ((unsigned int)((x - (600 + 64 * (i % 8) + 71 * (i % 8))) / 64 * data->spell[i].icn->width)) * ( data->spell[i].icn->bits_per_pixel >> 3);
					color = *(unsigned int *)(data->spell[i].icn->data_addr + a + b);
				}
				if (border_case_spell(x, y, 32 + 600 + 64 * (i % 8) + 71 * (i % 8), 32 + final_pos_y))
				{
					if (data->spell_menu.selected != i)
						color = darken_the_color(color);
					*(unsigned int *)(data->screen->data_addr + (int)(y - MARGIN) * data->screen->size_line + (int)(x) * (data->screen->bits_per_pixel / 8))
					= color;
				}
				y++;
			}
			x++;
		}
		display_name(data, i, 560 + 64 * (i % 8) + 72 * (i % 8));
		i++;
	}
}

void	handle_menu_spell_keys(int keycode, t_data *data)
{
	if(keycode == KEY_ESCAPE || keycode == KEY_X)
	{
		data->spell_menu.selected = -1;
		data->status = GAME;
	}
	if (data->spell_menu.selected == -1)
	{
		if (keycode == KEY_D || keycode == KEY_RIGHT)
		{
			if (data->selected != 3)
				++data->selected;
			else
				data->selected = 0;
		}
		else if (keycode == KEY_LEFT || keycode == KEY_A)
		{
			if (data->selected != 0)
				--data->selected;
			else
				data->selected = 3;
		}
		else if (keycode == KEY_ENTER)
			data->spell_menu.selected = 0;
	}
	else
	{
		if (keycode == KEY_D || keycode == KEY_RIGHT)
		{
			if (data->spell_menu.selected % 8 != 7)
				++data->spell_menu.selected;
			else if (data->spell_menu.selected != 21)
				data->spell_menu.selected -= 7;
			if (data->spell_menu.selected == 22)
				data->spell_menu.selected = 16;
		}

		else if (keycode == KEY_LEFT || keycode == KEY_A)
		{
			if (data->spell_menu.selected % 8 != 0)
				--data->spell_menu.selected;
			else if (data->spell_menu.selected != 16)
				data->spell_menu.selected += 7;
			else
				data->spell_menu.selected = 21;
		}
		else if (keycode == KEY_S || keycode == KEY_DOWN)
		{
			if (data->spell_menu.selected == 14
				|| data->spell_menu.selected == 15)
				data->spell_menu.selected = 21;
			else if (data->spell_menu.selected == 13)
				data->spell_menu.selected = 20;
			else if (data->spell_menu.selected == 21)
				data->spell_menu.selected = 6;
			else if (data->spell_menu.selected == 20)
				data->spell_menu.selected = 5;
			else if (data->spell_menu.selected >= 16)
				data->spell_menu.selected -= 16;
			else
				data->spell_menu.selected += 8;
		}
		else if (keycode == KEY_W || keycode == KEY_UP)
		{
			if (data->spell_menu.selected < 5)
				data->spell_menu.selected += 16;
			else if (data->spell_menu.selected == 6
				|| data->spell_menu.selected == 7)
				data->spell_menu.selected = 21;
			else if (data->spell_menu.selected == 5)
				data->spell_menu.selected = 20;
			else if (data->spell_menu.selected == 21
				|| data->spell_menu.selected == 20)
				data->spell_menu.selected -= 7;
			else
				data->spell_menu.selected -= 8;
		}
		else if (keycode == KEY_ENTER)
		{
			data->spell_take[data->selected] = data->spell_menu.selected;
			data->spell_menu.selected = -1;
		}
	}
}
void	handle_spells_menu(t_data *data, long long int cur)
{
	(void)cur;
	display_menu_background(data, data->spell_menu.background, 384, 57);
	display_spell_take(data);
	display_spell_list(data);
	// if (data->pause_menu.elapsed + 1000 / 10 < cur)
	// {
	// 	handle_spell_menu_keys(data);
	// 	data->pause_menu.elapsed = cur;
	// }
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
}
 
