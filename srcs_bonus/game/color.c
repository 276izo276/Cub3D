#include "cub3d_bonus.h"

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
