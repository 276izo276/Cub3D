#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "utils.h"
#include <X11/XKBlib.h> // Pour XkbKeycodeToKeysym
#include <X11/Xlib.h>   // Pour Display et d'autres fonctions X11
#include <X11/keysym.h> // Pour les définitions de Keysym (XK_w, XK_a, etc.)
#include <math.h>
#include <stdlib.h>

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
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	data->ac = ac;
	data->av = av;
}

int	key_press(int keycode, t_data *data)
{
	int	i;

	printf("Key pressed: %d\n", keycode);
	i = 0;
	while (data->keycode[i] != 0 && i < 100)
		i++;
	data->keycode[i] = keycode;
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	else if (keycode == KEY_SHIFT)
		data->map.mini.speed = 0.65;
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
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 4,
				data->mlx.height / 2);
		}
		else if (keycode == KEY_SHIFT)
			data->map.mini.speed = 0.4;
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
	if ((x != data->mlx.width / 4 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT))
	{
		// printf("Souris déplacée à X: %d, Y: %d    move: %lf\n", x, y,
			(double)(x - data->mlx.width / 4) / 5);
		data->map.mini.deg += (double)-(x - data->mlx.width / 4) / 10;
			// INFO baisser le 10 pour avoir plus de sensi et augenter pour avoir moins de sensi
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
		// printf("new angle >>> %lf %lf\n",data->map.mini.deg,data->map.mini.rad);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 4,
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

	i = 0;
	while (i < 100)
	{
		if (data->keycode[i] == KEY_ESCAPE)
			f_exit(data, 0);
		else if (is_move_player(data, i))
			handle_move(&data->map, &data->map.mini, data->keycode[i]);
		else if (data->keycode[i] == KEY_E)
			rotate_right(data);
		else if (data->keycode[i] == KEY_Q)
			rotate_left(data);
		i++;
	}
	aff_mini_map(data);
	// ft_printf_fd(2,"loop");
	return (0);
}

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

// double	t1 = 0;

// int fd = open("/proc/uptime",O_RDONLY);
// int	i = 0;
// char	*line;
// get_next_line(fd, &line);
// int	pt = 1;
// while (line[i] && line[i] != ' ')
// {
// 	if (line[i] == '.')
// 	{
// 		i++;
// 		pt *= 10;
// 	}
// 	if (pt == 1)
// 	{
// 		t1 = t1 * 10 + line[i] - 48;
// 	}
// 	else
// 	{
// 		t1 = t1 + (double)(line[i] - 48) / pt;
// 		// printf("HERE %lf    %d    %d\n",t1,(line[i] - 48) / pt, pt);
// 		pt *= 10;
// 	}
// 	i++;
// }
// close(fd);
// printf("double nb >>> %lf\n",t1);

void	rotate_image(void)
{
	int		x_dest;
	int		y_dest;
	int		center_x;
	int		center_y;
	double	translated_x_dest;
	double	translated_y_dest;
	double	rad;
	double	cos_theta;
	double	sin_theta;
	double	src_x_float;
	double	src_y_float;

	x_dest = 288;
	y_dest = 288 - 10;
	center_x = 288;
	center_y = 288;
	translated_x_dest = x_dest - center_x;
	translated_y_dest = y_dest - center_y;
	rad = 90 * M_PI / 180.0;
	cos_theta = cos(rad);
	sin_theta = sin(rad);
	// Appliquer la transformation inverse pour trouver la coordonnée correspondante dans l'image source
	// Note: rotation inverse de l'angle -theta
	src_x_float = translated_x_dest * cos_theta + translated_y_dest * sin_theta
		+ center_x;
	src_y_float = -translated_x_dest * sin_theta + translated_y_dest * cos_theta
		+ center_y;
	printf("data >>> %lf    %lf", src_x_float, src_y_float);
	// int src_x = (int)round(src_x_float);
		// Utilise round pour une meilleure précision
	// int src_y = (int)round(src_y_float); // Utilise round
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)data;
	(void)ac;
	(void)av;
	// rotate_image();
	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	data.map.mini.player_coo.y = 32;
	data.map.mini.player_coo.x = 32;
	data.map.mini.speed = 0.4;
	init_img_mini(&data, &data.map.mini);
	// aff_mini_map(&data);
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
	f_exit(&data, 0);
	return (1);
	// mlx_mouse_move();
}
