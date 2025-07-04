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

void	ray_launch(t_data *data)
{
	int	i = 270;
	while (1)
	{
		double pos_y = data->map.mini.player_coo.y;
		double pos_x = data->map.mini.player_coo.x;
		int		case_x = data->map.player_coo->x;
		int		case_y = data->map.player_coo->y;
		double deg = data->map.mini.deg + i;
		while (1)
		{

			printf("deg >>%lf\n",deg);
			if (deg <= 270 && deg >= 180)
			{
				// double rad = deg * (M_PI / 180);
				double dx = 64 - data->map.mini.player_coo.x;
				double dy = tan(270 - deg) * dx;
				// printf("dx=%lf   dy=%lf",dx,dy);
				if (dy > dx)
				{
					printf("HIT HORI\n");
					if(data->map.tabmap[case_y + 1][case_x] != '1')
					{
						case_y++;
						pos_y = 0;
						dy = 64 - data->map.mini.player_coo.y;
						dx = tan(deg - 180) * dy;
						pos_x += 64 - data->map.mini.player_coo.x;
					}
					else
					{
						pos_y = 64;
						dy = 64 - data->map.mini.player_coo.y;
						dx = tan(deg - 180) * dy;
						pos_x += 64 - data->map.mini.player_coo.x;
						break;
					}
				}
				else
				{
					printf("HIT VERTI\n");
					if(data->map.tabmap[case_y][case_x + 1] != '1')
					{
						case_x++;
						dx = 64 - pos_x;
						dy = tan(270 - deg) * dy;
						pos_y += dy;
						pos_x = 0;
					}
					else
					{
						dx = 64 - pos_x;
						dy = tan(270 - deg) * dx;
						pos_y += dy;
						pos_x = 64;
						break;
					}
				}
			}
			else
				break;
		}
		if (deg >= 180 && deg <= 270)
		{
			printf("end >>>y=%d  x=%d  y=%d  x= %d\n y=%lf   x=%lf\n",case_y,case_x,data->map.player_coo->y,data->map.player_coo->x,pos_y,pos_x);

			int	x = (5 * 64 / 2) - 32 + (case_x - data->map.player_coo->x) * 64 + (pos_x - data->map.mini.player_coo.x);

			int y = data->mlx.height - MARGIN - (5 * 64 / 2) - 32 + (case_y - data->map.player_coo->y) * 64 + (pos_y - data->map.mini.player_coo.y);

			printf("y=%d   x=%d\n",y,x);

			mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->map.mini.img[MINI_DOOR].img,x,y);
			usleep(1000);
		}
		break;
	}

}


// void	ray_launchs(t_data *data)
// {
// 	double	i = 270;
// 	while (1)
// 	{
// 		printf("deg = %lf\n",data->map.mini.deg);
// 		double deg = data->map.mini.deg + i;
// 		deg = fmod(deg, 360);
// 		printf("deg = %lf\n",deg);
// 		double rad = deg * (M_PI / 180.0);
// 		printf("rad = %lf\n",rad);
// 		double epsilon = 1e-9;
// 		double gap_y = -sin(rad);
// 		double gap_x = -cos(rad);
// 		double nb_gap_y = 0;
// 		double nb_gap_x = 0;
// 		double pos_y = data->map.mini.player_coo.y;
// 		double pos_x = data->map.mini.player_coo.x;
// 		int		case_x = data->map.player_coo->x;
// 		int		case_y = data->map.player_coo->y;
// 		printf("\nstart >>>y=%d  x=%d   y=%lf   x=%lf     gy=%lf  gx=%lf\n",case_y,case_x,pos_y,pos_x,gap_y,gap_x);
// 		while (1)
// 		{
// 			double	


// 			// nb_gap_y = 0;
// 			// nb_gap_x = 0;
// 			// double	tmpy = pos_y;
// 			// double	tmpx = pos_x;
// 			// while (tmpy >= 0 && tmpy < 64 && fabs(gap_y) >= epsilon)
// 			// {
// 			// 	// printf("ingpx %lf\n",gap_y);
// 			// 	tmpy += gap_y;
// 			// 	nb_gap_y++;
// 			// }
// 			// while (tmpx >= 0 && tmpx < 64 && fabs(gap_x) >= epsilon)
// 			// {
// 			// 	// printf("ingpx %lf\n",gap_x);
// 			// 	tmpx += gap_x;
// 			// 	nb_gap_x++;
// 			// }
// 			// printf("nbgapx>%lf<  gpx>%lf<     nbgapy>%lf< gpy >%lf<\n",nb_gap_x,gap_x,nb_gap_y,gap_y);
// 			// if (gap_y < gap_x)
// 			// {
// 			// 	printf("PAROI HORIZONTAL\n");
// 			// 	if (gap_y < 0)
// 			// 	{
// 			// 		if(data->map.tabmap[case_y - 1][case_x] != '1')
// 			// 		{
// 			// 			case_y--;
// 			// 			pos_y = 64;
// 			// 			pos_x += nb_gap_y * gap_x;
// 			// 			printf("not 1\n");
// 			// 		}
// 			// 		else
// 			// 		{
// 			// 			// pos_y = 0;
// 			// 			pos_x += nb_gap_y * gap_x;
// 			// 			printf("is a 1\n");
// 			// 			break;
// 			// 		}
// 			// 	}
// 			// 	else
// 			// 	{
// 			// 		if(data->map.tabmap[case_y + 1][case_x] != '1')
// 			// 		{
// 			// 			case_y++;
// 			// 			pos_y = 0;
// 			// 			pos_x += nb_gap_x * gap_y;
// 			// 			printf("not 1\n");
// 			// 		}
// 			// 		else
// 			// 		{
// 			// 			// pos_y = 64;
// 			// 			pos_x += nb_gap_x * gap_y;
// 			// 			printf("is a 1\n");
// 			// 			break;
// 			// 		}
// 			// 	}
// 			// }
// 			// else
// 			// {
// 			// 	printf("PAROI VERTICAL\n");
// 			// 	if (gap_x < 0)
// 			// 	{
// 			// 		if(data->map.tabmap[case_y][case_x - 1] != '1')
// 			// 		{
// 			// 			case_x--;
// 			// 			pos_x = 64;
// 			// 			pos_y += nb_gap_y * gap_x;
// 			// 			printf("not 1\n");
// 			// 		}
// 			// 		else
// 			// 		{
// 			// 			// pos_x = 0;
// 			// 			pos_y += nb_gap_y * gap_x;
// 			// 			printf("is a 1\n");
// 			// 			break;
// 			// 		}
// 			// 	}
// 			// 	else
// 			// 	{
// 			// 		if(data->map.tabmap[case_y][case_x + 1] != '1')
// 			// 		{
// 			// 			case_x++;
// 			// 			pos_x = 0;
// 			// 			pos_y += nb_gap_y * gap_x;
// 			// 			printf("not 1\n");
// 			// 		}
// 			// 		else
// 			// 		{
// 			// 			// pos_x = 64;
// 			// 			pos_y += nb_gap_y * gap_x;
// 			// 			printf("is a 1\n");
// 			// 			break;
// 			// 		}
// 			// 	}
// 			// }
// 			// printf("search\n");
// 		printf("end >>>y=%d  x=%d  y=%d  x= %d\n y=%lf   x=%lf\n",case_y,case_x,data->map.player_coo->y,data->map.player_coo->x,pos_y,pos_x);

// 		}
// 		printf("end >>>y=%d  x=%d  y=%d  x= %d\n y=%lf   x=%lf\n",case_y,case_x,data->map.player_coo->y,data->map.player_coo->x,pos_y,pos_x);
// 		if (round(gap_x) >= 0 && round(gap_y) >= 0)
// 		{
// 			// printf("end >>>y=%d  x=%d  y=%d  x= %d\n y=%lf   x=%lf\n",case_y,case_x,data->map.player_coo->y,data->map.player_coo->x,pos_y,pos_x);
// 			int	x = (5 * 64 / 2) - 32 + (case_x - data->map.player_coo->x) * 64 + (data->map.mini.player_coo.x - pos_x);
// 			int y = data->mlx.height - MARGIN - (5 * 64 / 2) - 32 + (case_y - data->map.player_coo->y) * 64 + (pos_y - data->map.mini.player_coo.y);
// 			mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,data->map.mini.img[MINI_DOOR].img,x,y);
// 			usleep(100000);
// 		}
// 		i++;
// 		break;
// 	}
// }


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
