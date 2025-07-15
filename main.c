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
	mlx_get_screen_size(data->mlx.mlx, &data->mlx.width, &data->mlx.height);
	init_utils_mini(data);
	data->screen = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width / 2, data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,&data->screen->bits_per_pixel,&data->screen->size_line,&data->screen->endian);
	// ft_bzero(&data->screen->data_addr, sizeof(data->screen->data_addr));
	// for (int y = 0; y < data->screen->height; y++) {
	// 	for (int x = 0; x < data->screen->width / 2; x++)
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
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 4,
				data->mlx.height / 2);
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
	// t_img	img_proj;
	double	i = -45;
	while (i <= 45)
	{
		double deg = data->map.mini.deg + i + 270;
		double	coo_y = data->map.mini.player_coo.y;
		double	coo_x = data->map.mini.player_coo.x;
		int		case_y = data->map.player_coo->y;
		int		case_x = data->map.player_coo->x;
		// printf("\n\n\nSTART\n");
		// printf("Case   y=%d  x=%d\n",case_y,case_x);
		// deg = fmod(deg,360);
		// printf("deg >>> %lf\n",deg);
		double	rad = deg * (M_PI / 180);
		// printf("rad >>> %lf\n",rad);
		double	delta_x = -cos(rad);
		// if (fabs(delta_x) <= 0.0000000001)
		// 	delta_x = 0.0000000001;
		double	delta_y = sin(rad);
		// if (fabs(delta_y) <= 0.0000000001)
		// 	delta_y = 0.0000000001;
		while (1)
		{

			double rx, ry;

            if (delta_x > 0)
                rx = (64 - coo_x) / delta_x;
            else
                rx = -coo_x / delta_x;
            if (delta_y > 0)
                ry = (64 - coo_y) / delta_y;
            else
                ry = -coo_y / delta_y;
			// rx = fabs(rx);
			// ry = fabs(ry);
			// printf("t ____ >>>%lf\n",rx);
			// printf("t |||| >>>%lf\n",ry);
			// if (rx < 0 || ry < 0)
			// 	printf("INFIFNFINFIFNFNIFNFINFIF\n");
			if (rx < ry)
			{
				// printf("MOVE XXXX\n");
				// printf("coo y >>>%lf\n",coo_y + rx * delta_y);
				// printf("coo x >>>%lf\n",coo_x + rx * delta_x);
				if (delta_x < 0)
				{
					if (data->map.tabmap[case_y][case_x - 1] != '1')
					{
						case_x--;
						coo_x = 63;
						coo_y = coo_y + rx * delta_y;
					}
					else
					{
						coo_x = 0;
						coo_y = coo_y + rx * delta_y;
						// printf("AFF COL\nCase   y=%d  x=%d\n",case_y,case_x);
						for (int i = -2;i < 2;i++)
						{
							for (int j = -2; j< 2; j++)
							{
								int	x = i + (5 * 64 / 2) + (case_x - data->map.player_coo->x) * 64 + (coo_x - data->map.mini.player_coo.x);
								int	y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (case_y - data->map.player_coo->y) * 64 + (coo_y  - data->map.mini.player_coo.y);
								mlx_pixel_put(data->mlx.mlx,data->mlx.win,x,y,0xFF0000);
							}
						}
						break;
					}
				}
				else
				{
					if (data->map.tabmap[case_y][case_x + 1] != '1')
					{
						case_x++;
						coo_x = 0;
						coo_y = coo_y + rx * delta_y;
					}
					else
					{
						coo_x = 63;
						coo_y = coo_y + rx * delta_y;
						// printf("AFF COL\nCase   y=%d  x=%d\n",case_y,case_x);
						for (int i = -2;i < 2;i++)
						{
							for (int j = -2; j< 2; j++)
							{
								int	x = i + (5 * 64 / 2) + (case_x - data->map.player_coo->x) * 64 + (coo_x - data->map.mini.player_coo.x);
								int	y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (case_y - data->map.player_coo->y) * 64 + (coo_y  - data->map.mini.player_coo.y);
								mlx_pixel_put(data->mlx.mlx,data->mlx.win,x,y,0xFF0000);
							}
						}
						break;
					}
				}
			}
			else
			{
				// printf("MOVE YYYY\n");
				// printf("coo y >>>%lf\n",coo_y + ry * delta_y);
				// printf("coo x >>>%lf\n",coo_x + ry * delta_x);
				if (delta_y < 0)
				{
					// printf("NEGA DELTA Y %lf",delta_y);
					if (data->map.tabmap[case_y - 1][case_x] != '1')
					{
						case_y--;
						coo_y = 63;
						coo_x = coo_x + ry * delta_x;
					}
					else
					{
						coo_y = 0;
						coo_x = coo_x + ry * delta_x;
						// printf("AFF COL\nCase   y=%d  x=%d\n",case_y,case_x);
						for (int i = -2;i < 2;i++)
						{
							for (int j = -2; j< 2; j++)
							{
								int	x = i + (5 * 64 / 2) + (case_x - data->map.player_coo->x) * 64 + (coo_x - data->map.mini.player_coo.x);
								int	y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (case_y - data->map.player_coo->y) * 64 + (coo_y  - data->map.mini.player_coo.y);
								mlx_pixel_put(data->mlx.mlx,data->mlx.win,x,y,0xFF0000);
							}
						}
						break;
					}
				}
				else
				{
					// printf("POSI DELTA Y %lf",delta_y);
					if (data->map.tabmap[case_y + 1][case_x] != '1')
					{
						case_y++;
						coo_y = 0;
						coo_x = coo_x + ry * delta_x;
					}
					else
					{
						coo_y = 63;
						coo_x = coo_x + ry * delta_x;
						// printf("AFF COL\nCase   y=%d  x=%d\n",case_y,case_x);
						for (int i = -2;i < 2;i++)
						{
							for (int j = -2; j< 2; j++)
							{
								int	x = i + (5 * 64 / 2) + (case_x - data->map.player_coo->x) * 64 + (coo_x - data->map.mini.player_coo.x);
								int	y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (case_y - data->map.player_coo->y) * 64 + (coo_y  - data->map.mini.player_coo.y);
								mlx_pixel_put(data->mlx.mlx,data->mlx.win,x,y,0xFF0000);
							}
						}
						break;
					}
				}
			}
		}
	// 	data->f_display.hit_x = case_x;
	// 	data->f_display.hit_y = case_y;
	// 	double wall_height = (128  * 60) / sqrt(((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))  *  ((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))
	// +	((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x)) * ((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x)));
	// 	get_pixel_col(data, &data->f_display, wall_height);
		// printf("Angle=%lf   Distance_x=%d    %d   %lf   %lf    Distance_y=%d    %d   %lf   %lf\n",
		// 	i,case_x,data->map.player_coo->x,coo_x,data->map.mini.player_coo.x,
		// 	case_y,data->map.player_coo->y,coo_y,data->map.mini.player_coo.y
		// );
	// 	printf("Angle=%lf   Distance_x=%lf    Distance_y=%lf     Distance_total=%lf\n",
	// 	i,
	// 	sqrt(((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x)) * ((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x))),
	// 	sqrt( ((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))  *  ((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y)) ),
	// 	sqrt(((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))  *  ((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))
	// +	((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x)) * ((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x))  ));

		double	dist_wall = sqrt(((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))  *  ((case_y - data->map.player_coo->y) * 64.0 + (coo_y - data->map.mini.player_coo.y))
	+	((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x)) * ((case_x - data->map.player_coo->x) * 64.0 + (coo_x - data->map.mini.player_coo.x))  );
		// printf("Angle=%lf   Distance_total=%lf\n",i,dist_wall);
		double	size_wall = data->mlx.height / 2 * tan(30 * (M_PI / 180)) / (double)(dist_wall/64.0);
		// printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(30 * (M_PI / 180)), size_wall, data->mlx.height);
		int	pix_x = data->mlx.width / 2 - ((data->mlx.width / 2)/90 * (i + 45));
		int	pix_y = data->mlx.height / 2;
		// img_proj.img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
		// img_proj.data_addr = mlx_get_data_addr(img_proj.img,&img_proj.bits_per_pixel,&img_proj.size_line,&img_proj.endian);
		// double	pix_img_y = 1024;
		// double	pix_img_x = 1024;
		// write(1,"HERE\n",5);
		while (pix_y > data->mlx.height / 2 - size_wall/2 && pix_y > 0 )
		{
			char *pixel_addr = data->screen->data_addr + (pix_y
						* data->screen->size_line + pix_x
						* (data->screen->bits_per_pixel / 8));
			// printf("----  %d     %d  ----\n",pix_y,pix_x);
			*(unsigned int *)pixel_addr = 0x000000FF;
			// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,pix_y,0x0000FF);
			// printf("put pixel >>> %d  %d\n",pix_x,pix_y);
			pix_y--;
		}
		while (pix_y > 0)
		{
			char *pixel_addr = data->screen->data_addr + ((pix_y)
						* data->screen->size_line + (pix_x)
						* (data->screen->bits_per_pixel / 8));
			// printf("put pixel >>> %d  %d\n",pix_x,pix_y);
			*(unsigned int *)pixel_addr = 0x00000000;
			// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,pix_y,0x000000);
			pix_y--;
		}
		pix_y = data->mlx.height / 2;
		while (pix_y < data->mlx.height / 2 + size_wall/2 && pix_y < data->mlx.height )
		{
			char *pixel_addr = data->screen->data_addr + ((pix_y)
						* data->screen->size_line + (pix_x)
						* (data->screen->bits_per_pixel / 8));
			// printf("put pixel >>> %d  %d\n",pix_x,pix_y);
			*(unsigned int *)pixel_addr = 0x000000FF;
			// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,pix_y,0x0000FF);
			pix_y++;
		}
		while (pix_y < data->mlx.height)
		{
			char *pixel_addr = data->screen->data_addr + ((pix_y)
						* data->screen->size_line + (pix_x)
						* (data->screen->bits_per_pixel / 8));
			// printf("put pixel >>> %d  %d\n",pix_x,pix_y);
			*(unsigned int *)pixel_addr = 0x00000000;
			// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,pix_y,0x000000);
			pix_y++;
		}
		i += .1;
	}
	
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
	// mlx_destroy_image(data->mlx.mlx,img_proj.img);
}

int	game_loop(t_data *data)
{
	int	i;
	long long int cur = get_mtime();

	if (data->time_move + 1000 / 90  < cur)
	{
		// printf("fps >>>%lld     \n",1000 / (cur - data->time_move));
		data->time_move = cur;
		// printf("IN\n");
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
	}
	if (data->time_fps + 1000 / FPS  < cur)
	{
		// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
		data->time_fps = cur;
		ray_launch(data);
		aff_mini_map(data);
		// ray_launch(data);
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
	ft_bzero(&data.ray, sizeof(t_ray));
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
	f_exit(&data, 0);
	return (1);
}
