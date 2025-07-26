#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "time.h"

void	fill_need_print(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SIZE_MAP)
	{
		x = 0;
		while (x < SIZE_MAP)
		{
			if (sqrt(pow(y - SIZE_MAP / 2, 2) + pow(x - SIZE_MAP / 2,
						2)) > SIZE_MAP / 2)
			{
				data->map.mini.need_print[y][x] = 0;
			}
			else
			{
				data->map.mini.need_print[y][x] = 1;
			}
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	// mlx_get_screen_size(data->mlx.mlx, &data->mlx.width, &data->mlx.height);
	data->mlx.height = 1000;
	data->mlx.width = 1000;
	init_utils_mini(data);
	data->ray = malloc(sizeof(t_ray) * data->mlx.width);
	if (data->ray == NULL)
		f_exit(data, 1);
	ft_bzero(data->ray, sizeof(t_ray) * data->mlx.width);
	double fov;

	fov = data->mlx.height / 2 * tan((45 * (M_PI / 180)));
	if (data->mlx.height < data->mlx.width)
		fov *= (data->mlx.width / data->mlx.height);
	else
		fov /= (data->mlx.height / data->mlx.width) * 0.75;
	int i = 0;
	while (i < data->mlx.width)
	{
		data->ray[i].d_proj = fov;
		++i;
	}
	data->screen = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,&data->screen->bits_per_pixel,&data->screen->size_line,&data->screen->endian);
	// ft_bzero(&data->screen->data_addr, sizeof(data->screen->data_addr));
	// for (int y = 0; y < data->screen->height; y++) {
	// 	for (int x = 0; x < data->screen->width; x++)
	// 	{
	// 		char *pixel_addr = data->screen->data_addr + ((y) * data->screen->size_line
	// 					+ (x) * (data->screen->bits_per_pixel / 8));
	// 		*(unsigned int *)pixel_addr = 0x000000;
	// 	}
	// }
	// mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->screen->img,0,0);
	data->ac = ac;
	data->av = av;
}

int	key_press(int keycode, t_data *data)
{
	int	i;

	// printf("Key pressed: %d\n", keycode);
	i = 0;
	while (data->keycode[i] != 0 && i < 100)
		i++;
	data->keycode[i] = keycode;
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	else if (keycode == KEY_SHIFT)
		data->map.mini.speed = 3;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	int	i;

	// printf("Key released: %d\n", keycode);
	i = 0;
	while (i < 100)
	{
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
	return (0);
}

int	is_key_pressed(t_data *data, int keycode)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (data->keycode[i] == keycode)
			return (1);
		i++;
	}
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)data;
	if ((x != data->mlx.width / 2 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT))
	{
		data->map.mini.deg += (double)-(x - data->mlx.width / 2) / 40;
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
			data->mlx.height / 2);
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}

bool	is_move_player(t_data *data, int i)
{
	if (data->keycode[i] == KEY_W || data->keycode[i] == KEY_D
		|| data->keycode[i] == KEY_A || data->keycode[i] == KEY_S)
		return (true);
	return (false);
}

int	game_loop(t_data *data)
{
	int	i;
	long long int cur = get_mtime();

	if (data->time_move + 1000 / FPM  < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		// printf("IN\n");
		i = 0;
		while (i < 100)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (is_move_player(data, i))
				handle_move(&data->map, &data->map.mini, data->keycode[i], data);
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
	}
	if (data->time_fps + 1000 / FPS  < cur)
	{
		// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
		data->time_fps = cur;
		aff_mini_map(data);
		ray_launch(data);
		usleep(1000);
		// ray_launch_old(data);
	}
	// printf("OUT\n");
	return (0);
}

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	open_window(&data, &data.mlx);

	data.map.mini.player_coo.y = 32;
	data.map.mini.player_coo.x = 32;
	data.map.mini.speed = 1.5;
	init_img_mini(&data, &data.map.mini);
	// init_display(&data, &data.f_display);
	mlx_do_key_autorepeatoff(data.mlx.mlx);
	mlx_mouse_hide(data.mlx.mlx, data.mlx.win);
	mlx_mouse_move(data.mlx.mlx, data.mlx.win, data.mlx.width / 4,
		data.mlx.height / 2);
	mlx_hook(data.mlx.win, ON_KEYDOWN, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, ON_KEYUP, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, ON_DESTROY, 0, close_win, &data);
	mlx_hook(data.mlx.win, ON_MOUSEMOVE, 1L << 6, mouse_move, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	// ray_launch(&data, data.ray);
	f_exit(&data, 0);
	return (1);
}
