#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"

static void	handle_input_move(t_data *data, long long int cur)
{
	int i;

	i = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		// printf("IN\n");
		while (i < 100)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (is_move_player(data, i))
				handle_move(&data->map, &data->map.mini, data->keycode[i],
					data);
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
	}
}
static int	get_texture_pixel(t_img *texture, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data_addr + (y * texture->size_line + x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

static void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char *tmp_addr;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		tmp_addr = data->screen->data_addr + (y * data->screen->size_line + x * (data->screen->bits_per_pixel / 8));
		*(unsigned int *)tmp_addr = color;
	}
}

static void	draw_texture_menu(t_data *data, t_img	*texture, int final_x, int final_y)
{
	int	x;
	int	y;
	unsigned int color;

	color = 0;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			color = get_texture_pixel(texture, x ,y);
			pixel_put(data, final_x + x, final_y + y, color);
			++x;
		}
		++y;
	}
}
static void draw_select_border(t_data *data, int start_x, int start_y)
{
	int	i;
	int	j;

	i = 0;
	if (data->selected == 1)
		start_x += data->menu[data->selected].img_coa->width + 150;
	else if (data->selected == 2)
		start_y += data->menu[0].img_coa->height + 100;
	else if (data->selected == 3)
	{
		start_x += data->menu[data->selected].img_coa->width + 150;
		start_y += data->menu[0].img_coa->height + 100;
	}
	while (i < data->menu[data->selected].img_coa->width)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, start_x + i, start_y + j, data->menu[data->selected].color);
			pixel_put(data, start_x + i, start_y + data->menu[data->selected].img_coa->height - j, data->menu[data->selected].color);
			++j;
		}
		++i;
	}
	i = 0;
	while (i < data->menu[data->selected].img_coa->height)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, start_x + j, start_y + i, data->menu[data->selected].color);
			pixel_put(data, start_x + data->menu[data->selected].img_coa->width - j, start_y + i, data->menu[data->selected].color);
			++j;
		}
		++i;
	}

}
static void display_menu(t_data *data)
{
	int	color;

	color = 0;
	int start_x = (data->mlx.width - (2 * data->menu[0].img_coa->width + 200)) / 2;
    int start_y = (data->mlx.height - (2 * data->menu[0].img_coa->height - 100)) / 2;
	draw_texture_menu(data, data->select, 0, 0);
	draw_texture_menu(data, data->menu[0].img_coa, start_x, start_y);
	draw_texture_menu(data, data->menu[1].img_coa, start_x + data->menu[0].img_coa->width + 150, start_y);
	draw_texture_menu(data, data->menu[2].img_coa, start_x, start_y + data->menu[0].img_coa->height + 100);
	draw_texture_menu(data, data->menu[3].img_coa, start_x + data->menu[0].img_coa->width  + 150, start_y + data->menu[0].img_coa->height + 100);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
	draw_select_border(data,  start_x, start_y);
}

#include <stdio.h>
int	game_loop(t_data *data)
{
	long long int	cur;

	if (data->status == MENU)
		display_menu(data);
	else
	{
		cur = get_mtime();
		handle_input_move(data, cur);
		if (data->time_fps + 1000 / FPS < cur)
		{
			// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
			data->time_fps = cur;
			ray_launch(data);
			sem_post(data->sem_background);
			sem_post(data->sem_background);
			display_game(data);
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
			aff_mini_map(data);
			pthread_barrier_wait(&data->barrier);
			// ray_launch_old(data);
		}
	}
	// printf("OUT\n");
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
