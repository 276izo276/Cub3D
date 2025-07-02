#include "struct.h"
#include "utils.h"
#include "ft_printf.h"
#include "color.h"
#include <stdlib.h>

static int	check_color(t_color *color)
{
	if (!color || color->r < 0 || color->r > 255 || color->g < 0
		|| color->g > 255 || color->b < 0 || color->b > 255)
	{
		return (1);
	}
	return (0);
}

static int	get_color(char *line, int *i)
{
	int	nb;
	int	get_nb;

	while (line[*i] && line[*i] == ',')
		(*i)++;
	nb = 0;
	get_nb = 0;
	while (line[*i] && (line[*i] >= '0' && line[*i] <= '9'))
	{
		nb = nb * 10 + line[*i] - 48;
		(*i)++;
		get_nb++;
	}
	if ((line[*i] != ',' && line[*i] != 0) || !get_nb || get_nb > 3)
		return (-1);
	return (nb);
}

static int	fill_color(char *line, t_color *color)
{
	int	i;

	i = 2;
	if (!line[1])
		return (1);
	while (line[i] && line[i] == ' ')
		i++;
	color->r = get_color(line, &i);
	color->g = get_color(line, &i);
	color->b = get_color(line, &i);
	if (color->r == -1 || color->g == -1 || color->b == -1
		|| line[i] != 0 || check_color(color))
		return (1);
	return (0);
}

void	set_floor(char *line, t_data *data)
{
	if (!line[1])
		return ;
	data->map.floor = malloc(sizeof(t_color));
	if (!data->map.floor)
		return ;
	ft_bzero(data->map.floor, sizeof(t_color));
	if (fill_color(line, data->map.floor))
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE"Color >>> '"_RED _ITALIC"%s"_END _PURPLE \
_BOLD"' is not a valid color pattern\n"_END, line);
		f_exit(data, 1);
	}
}

void	set_ceiling(char *line, t_data *data)
{
	if (!line[1])
		return ;
	data->map.ceiling = malloc(sizeof(t_color));
	if (!data->map.ceiling)
		return ;
	ft_bzero(data->map.ceiling, sizeof(t_color));
	if (fill_color(line, data->map.ceiling))
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE"Color >>> '"_RED _ITALIC"%s"_END _PURPLE \
_BOLD"' is not a valid color pattern\n"_END, line);
		f_exit(data, 1);
	}
}
