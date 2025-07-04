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

	// printf("Key pressed: %d\n", keycode);
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
		data->map.mini.deg += (double)-(x - data->mlx.width / 4) / 10;
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
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

// void	ray_launch(t_data *data)
// {
// 	int	i = 0;
// 	while (1)
// 	{
// 		double pos_y = data->map.mini.player_coo.y;
// 		double pos_x = data->map.mini.player_coo.x;
// 		int		case_x = data->map.player_coo->x;
// 		int		case_y = data->map.player_coo->y;
// 		double deg = data->map.mini.deg + i;
// 		deg = fmod(deg,360);
// 		printf("\n\nSTART\ndeg >>%lf\n",deg);
// 		while (1)
// 		{
// 			if (deg <= 270 && deg >= 180)
// 			{
// 				// double rad = deg * (M_PI / 180);
// 				double dx = 64 - pos_x;
// 				double dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 				printf("dx=%lf   dy=%lf\n",dx,dy);
// 				if (dy > dx)
// 				{
// 					printf("HIT HORI\n");
// 					if(data->map.tabmap[case_y + 1][case_x] != '1')
// 					{
// 						case_y++;
// 						dy = 64 - pos_y;
// 						printf("1dy >> %lf   %lf\n",dx,deg);
// 						dx = tan((deg - 180) * (M_PI / 180)) * dy;
// 						printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_x += dx;
// 						if (pos_x > 64)
// 						{	
// 							if(data->map.tabmap[case_y][case_x + 1] != '1')
// 							{
// 								case_x++;
// 								dx = 64 - pos_x;
// 								// printf("1dy >> %lf   %lf\n",dx,deg);
// 								dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 								// printf("1dy >> %lf   %lf\n",dy,deg);
// 								pos_y += dy;
// 								pos_x = 0;
// 							}
// 							else
// 							{
// 								dx = 64 - pos_x;
// 								// printf("2dy >> %lf   %lf\n",dx,deg);
// 								dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 								// printf("2dy >> %lf   %lf\n",dy,deg);
// 								pos_y += dy;
// 								pos_x = 64;
// 								break;
// 							}
// 						}
// 					}
// 					else
// 					{
// 						dy = 64 - pos_y;
// 						printf("2dy >> %lf   %lf\n",dx,deg);
// 						dx = tan((deg - 180) * (M_PI / 180)) * dy;
// 						printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_x += dx;
// 						if (pos_x > 64)
// 						{
// 							if(data->map.tabmap[case_y][case_x + 1] != '1')
// 							{
// 								case_x++;
// 								dx = 64 - pos_x;
// 								// printf("1dy >> %lf   %lf\n",dx,deg);
// 								dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 								// printf("1dy >> %lf   %lf\n",dy,deg);
// 								pos_y += dy;
// 								pos_x = 0;
// 							}
// 							else
// 							{
// 								dx = 64 - pos_x;
// 								// printf("2dy >> %lf   %lf\n",dx,deg);
// 								dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 								// printf("2dy >> %lf   %lf\n",dy,deg);
// 								pos_y += dy;
// 								pos_x = 64;
// 								break;
// 							}
// 						}
// 						// pos_y = 64;
// 						break;
// 					}
// 				}
// 				else
// 				{
// 					printf("HIT VERTI\n");
// 					if(data->map.tabmap[case_y][case_x + 1] != '1')
// 					{
// 						case_x++;
// 						dx = 64 - pos_x;
// 						// printf("1dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_y += dy;
// 						pos_x = 0;
// 					}
// 					else
// 					{
// 						dx = 64 - pos_x;
// 						// printf("2dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((270 - deg) * (M_PI / 180)) * dx;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_y += dy;
// 						pos_x = 64;
// 						break;
// 					}
// 				}
// 			}
// 			else if (deg <= 180 && deg >= 90)
// 			{
// 				// double rad = deg * (M_PI / 180);
// 				double dy = 64 - data->map.mini.player_coo.y;
// 				double dx = tan((180 - deg) * (M_PI / 180)) * dy;
// 				printf("dx=%lf   dy=%lf\n",dx,dy);
// 				if (dy > dx)
// 				{
// 					printf("HIT HORI\n");
// 					if(data->map.tabmap[case_y + 1][case_x] != '1')
// 					{
// 						case_y++;
// 						dy = 64 - pos_y;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						dx = tan((180 - deg) * (M_PI / 180)) * dy;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_x -= dx;
// 						pos_y = 0;
// 					}
// 					else
// 					{
// 						dy = 64 - pos_y;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						dx = tan((180 - deg) * (M_PI / 180)) * dy;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_x -= dx;
// 						pos_y = 64;
// 						break;
// 					}
// 				}
// 				else
// 				{
// 					printf("HIT VERTI\n");
// 					if(data->map.tabmap[case_y][case_x - 1] != '1')
// 					{
// 						case_x--;
// 						dx = pos_x;
// 						// printf("1dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((deg - 90) * (M_PI / 180)) * dx;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_y += dy;
// 						pos_x = 64;
// 					}
// 					else
// 					{
// 						dx = pos_x;
// 						// printf("2dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((deg - 90) * (M_PI / 180)) * dx;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_y += dy;
// 						pos_x = 0;
// 						break;
// 					}
// 				}
// 			}
// 			else if (deg >= 0 && deg <= 90)
// 			{
// 				printf("in \n ");
// 				// double rad = deg * (M_PI / 180);
// 				double dx = data->map.mini.player_coo.x;
// 				double dy = tan((90 - deg) * (M_PI / 180)) * dx;
// 				printf("dx=%lf   dy=%lf\n",dx,dy);
// 				if (dy > dx)
// 				{
// 					printf("HIT HORI\n");
// 					if(data->map.tabmap[case_y - 1][case_x] != '1')
// 					{
// 						case_y--;
// 						dy = 64 - pos_y;
// 						// printf("1dy >> %lf   %lf\n",dx,deg);
// 						dx = tan((deg - 180) * (M_PI / 180)) * dy;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_x -= dx;
// 						pos_y = 64;
// 					}
// 					else
// 					{
// 						dy = 64 - pos_y;
// 						// printf("2dy >> %lf   %lf\n",dx,deg);
// 						dx = tan((deg - 180) * (M_PI / 180)) * dy;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_x -= dx;
// 						pos_y = 0;
// 						break;
// 					}
// 				}
// 				else
// 				{
// 					printf("HIT VERTI\n");
// 					if(data->map.tabmap[case_y][case_x - 1] != '1')
// 					{
// 						case_x--;
// 						dx = pos_x;
// 						// printf("1dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((90 - deg) * (M_PI / 180)) * dx;
// 						// printf("1dy >> %lf   %lf\n",dy,deg);
// 						pos_y -= dy;
// 						pos_x = 64;
// 					}
// 					else
// 					{
// 						dx = pos_x;
// 						// printf("2dy >> %lf   %lf\n",dx,deg);
// 						dy = tan((90 - deg) * (M_PI / 180)) * dx;
// 						// printf("2dy >> %lf   %lf\n",dy,deg);
// 						pos_y -= dy;
// 						pos_x = 0;
// 						break;
// 					}
// 				}
// 			}
// 			else
// 				break;
// 		}
// 		if ((deg >= 90 && deg <= 270) || (deg >= 0 && deg <= 90))
// 		{
// 			printf("end >>>y=%d  x=%d  y=%d  x= %d\n y=%lf   x=%lf\n",case_y,case_x,data->map.player_coo->y,data->map.player_coo->x,pos_y,pos_x);

// 			int	x = (5 * 64 / 2) - 32 + (case_x - data->map.player_coo->x) * 64 + (pos_x - data->map.mini.player_coo.x);

// 			int y = data->mlx.height - MARGIN - (5 * 64 / 2) - 32 + (case_y - data->map.player_coo->y) * 64 + (pos_y - data->map.mini.player_coo.y);

// 			// printf("y=%d   x=%d\n",y,x);

// 			mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->map.mini.img[MINI_DOOR].img,x,y);
// 			usleep(1000);
// 		}
// 		break;
// 	}

// }



void	ray_launch(t_data *data)
{

	int	i = 0;
	(void)data;
	while (1)
	{
		double deg = i + 180;
		double	coo_y = data->map.mini.player_coo.y;
		double	coo_x = data->map.mini.player_coo.x;
		// double	coo_y = 0;
		// double	coo_x = 13.525;
		deg = fmod(deg,360);
		printf("deg >>> %lf\n",deg);
		while (1)
		{
			double	mx = 0;
			double	my = 0;
			int	x = 0;
			int	y = 0;
			if (deg > 180)
			{
				mx = coo_x;
				x = -1;
			}
			else if (deg != 0 && deg != 180)
			{
				mx = 64 - coo_x;
				x = 1;
			}
			if (deg > 90 && deg < 270)
			{
				my = 64 - coo_y;
				y = -1;
			}
			else if (deg != 90 && deg != 270)
			{
				my = coo_y;
				y = 1;
			}
			double	dx = 0;
			double	dy = 0;
			if (deg != 180 && deg != 0)
				dy = tan((deg - 90) * (M_PI / 180)) * mx;
			else
				dy = my * y;
			if (deg != 270 && deg != 90)
				dx = tan(-deg * (M_PI / 180)) * my;
			else
				dx = mx * x;
			printf("mx=%lf   dy=%lf   my=%lf   dx=%lf\n",mx * x,dy,my * y,dx);
			exit(1);
			break;
		}

		// int	x = (5 * 64 / 2) - 32 + (case_x - data->map.player_coo->x) * 64 + (pos_x - data->map.mini.player_coo.x);

		// int y = data->mlx.height - MARGIN - (5 * 64 / 2) - 32 + (case_y - data->map.player_coo->y) * 64 + (pos_y - data->map.mini.player_coo.y);


		// mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->map.mini.img[MINI_DOOR].img,x,y);
		break;
	}
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
	ray_launch(data);
	return (0);
}

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_data	data;

	(void)data;
	(void)ac;
	(void)av;
	init_data(&data, ac, av);
	parsing(&data);
	open_window(&data, &data.mlx);
	data.map.mini.player_coo.y = 32;
	data.map.mini.player_coo.x = 32;
	data.map.mini.speed = 0.4;
	init_img_mini(&data, &data.map.mini);
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
}
