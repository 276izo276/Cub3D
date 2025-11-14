#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <unistd.h>
#include "mlx.h"


void	put_top_color(t_data *data, int x, int y, unsigned int *color)
{
	if (y > 175)
		return ;
	if (*color == YELLOW)
	{
		if (x < data->img[SANDGLASS].width / 3)
			*color = data->coa[FIRE].color;
		else if (x < data->img[SANDGLASS].width / 2)
			*color = data->coa[WATER].color;
		else if (x < data->img[SANDGLASS].width - data->img[SANDGLASS].width / 3)
			*color = data->coa[EARTH].color;
		else
			*color = data->coa[AIR].color;
	}
}

void	fill_score_color(t_data *data, int x, int y, unsigned int *color)
{

	(void)y;
	if (*color == YELLOW)
	{
		if (x < data->img[SANDGLASS].width / 3 && y >= data->coa[FIRE].max_y)
			*color = data->coa[FIRE].color;
		if (x > data->img[SANDGLASS].width / 3 && x < data->img[SANDGLASS].width / 2 && y >= data->coa[WATER].max_y)
			*color = data->coa[WATER].color;
		if (x > data->img[SANDGLASS].width / 2 && x < data->img[SANDGLASS].width - data->img[SANDGLASS].width / 3 && y >= data->coa[EARTH].max_y)
			*color = data->coa[EARTH].color;
		if (x > data->img[SANDGLASS].width - data->img[SANDGLASS].width / 3 && x < data->img[SANDGLASS].width && y >= data->coa[AIR].max_y)
			*color = data->coa[AIR].color;
	}
}

void	display_sandglass(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[SANDGLASS].height)
	{
		x = 0;
		while (x < data->img[SANDGLASS].width)
		{
			color = get_texture_pixel(&data->img[SANDGLASS], x, y);
			put_top_color(data, x, y, &color);
			fill_score_color(data, x, y ,&color);
			if (color != YELLOW && color != RED)
				pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
	// while (y > 0)
	// {
	// 	x = 0;
	// 	while (x < data->img[SANDGLASS].width)
	// 	{
	// 		color = get_texture_pixel(&data->img[SANDGLASS], x, y);
	// 		if (color == YELLOW)
	// 		{
	// 			fill_score_color(data, x, y, &color);
	// 			if (color != YELLOW && color != RED)
	// 				pixel_put(data, x + start_x, y + start_y, color);
	// 		}
	// 		++x;
	// 	}
	// 	--y;
	// }
}

#include <stdio.h>
void	handle_end_menu(t_data *data)
{
	// printf("player coa >>> %f\nFIRE >> %f\nWATER >>> %f\nEARTH >> %f\nAIR >> %f\n", data->player.xp, data->coa[FIRE].xp, data->coa[WATER].xp, data->coa[EARTH].xp, data->coa[AIR].xp);
// 
	// printf("player coa >>> %f\nFIRE >> %f\nWATER >>> %f\nEARTH >> %f\nAIR >> %f\n", data->player.xp, data->coa[FIRE].max_y, data->coa[WATER].max_y, data->coa[EARTH].max_y, data->coa[AIR].max_y);
	display_menu_background(data, &data->img[END_BACKGROUND], 0, 0);
	display_sandglass(data, 510, 150);
	display_retry_button(data, 250, 780);
	display_quit_button(data, 1000, 780);

	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
}
