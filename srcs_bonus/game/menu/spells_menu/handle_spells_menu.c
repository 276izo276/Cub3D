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

void	display_name(t_data *data, int i)
{
	unsigned int	color;
	int				x;
	int				y;

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
				pixel_put(data, x + 610 + 64 * i + 72 * i, y + 570, color);
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

	i = 0;
	while (i < 10)
	{
		x =  646 + 64 * i + 71 * (i);
		while (x < 646 + 64 * (i + 1) + 71 * (i))
		{
			y = 660;
			while (y < 660 + 64)
			{
				if(data->spell[i].icn)
				{
					unsigned int	a = ((unsigned int)((y - 660) / 64 * data->spell[i].icn->height)) *  data->spell[i].icn->size_line;
					unsigned int	b = ((unsigned int)((x - (646 + 64 * i + 71 * (i))) / 64 * data->spell[i].icn->width)) * ( data->spell[i].icn->bits_per_pixel >> 3);
					color = *(unsigned int *)(data->spell[i].icn->data_addr + a + b);
				}
				if (border_case_spell(x, y, 32 + 646 + 64 * i + 71 * (i), 32 + 660))
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
		display_name(data, i);
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
			if (data->spell_menu.selected != 4)
			++data->spell_menu.selected;
			else
			data->spell_menu.selected = 0;
		}
		else if (keycode == KEY_LEFT || keycode == KEY_A)
		{
			if (data->spell_menu.selected != 0)
			--data->spell_menu.selected;
			else
			data->spell_menu.selected = 4;
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
 
