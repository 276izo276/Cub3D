#include "cub3d_bonus.h"
#include "color_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"

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
