#include "struct.h"
#include "ft_printf.h"
#include "parsing.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
#include "player.h"
#include <stdlib.h>
#include "texture.h"

#include <X11/keysym.h>   // Pour les définitions de Keysym (XK_w, XK_a, etc.)
#include <X11/Xlib.h>     // Pour Display et d'autres fonctions X11
#include <X11/XKBlib.h>   // Pour XkbKeycodeToKeysym

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	data->ac = ac;
	data->av = av;
}

int key_press(int keycode, t_data *data)
{
	int	i;

    // printf("Key pressed: %d\n", keycode);
	i = 0;
	while (data->keycode[i] != 0 && i < 100)
		i++;
	data->keycode[i] = keycode;
    return (0);
}

int key_release(int keycode, t_data *data)
{
	int	i;

	// printf("Key released: %d\n", keycode);
	i = 0;
	while (i < 100)
	{
		if (data->keycode[i] == keycode)
			data->keycode[i] = 0;
		i++;
	}
    return (0);

    return (0);
}

int mouse_move(int x, int y, t_data *data)
{
    // 'vars' est le pointeur 'param' que tu as passé à mlx_hook.
    // Tu peux l'utiliser pour accéder à mlx-> ou win-> si besoin,
    // ou à d'autres données spécifiques à ton programme.
    (void)data; // Supprime l'avertissement si 'vars' n'est pas utilisé directement ici.

    printf("Souris déplacée à X: %d, Y: %d\n", x, y);
    return (0); // Toujours retourner 0 pour indiquer que l'événement a été traité
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}

void	aff_mini_map(t_data *data)
{
	t_img	*mini;
	int		size;

	// data->wh = malloc(sizeof(t_img));
	// ft_bzero(data->wh,sizeof(t_img));
	// data->wh->path = ft_strdup("texture/mini_map/white.xpm");
	// data->wh->img = mlx_xpm_file_to_image(data->mlx.mlx,data->wh->path,&data->wh->width,&data->wh->height);

	// data->wh = malloc(sizeof(t_img));
	// ft_bzero(data->wh,sizeof(t_img));
	// data->wh->path = ft_strdup("texture/mini_map/black.xpm");
	// data->wh->img = mlx_xpm_file_to_image(data->mlx.mlx,data->wh->path,&data->wh->width,&data->wh->height);

	size = 5 * 64;
	mini = malloc(sizeof(t_img));
	mini->img = mlx_new_image(data->mlx.mlx, size, size);
	mini->data_addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel, &mini->size_line, &mini->endian);
	int	y = -5;
	while (y < 6)
	{
		int	x = -5;
		while (x < 6)
		{
			int	new_y = data->map.player_coo->y + y;
			int	new_x = data->map.player_coo->x + x;
			int	sy = 1*64+32 + (y*64+64-data->map.mini.player_coo.y);
			int	iy = 0;
			if (new_y >= data->map.tabmap_height || new_y < 0
			|| new_x >= ft_strlen(data->map.tabmap[new_y]) || new_x < 0
			|| data->map.tabmap[new_y][new_x] == ' ')
			{
				while (iy < 64)
				{
					int	sx = 1*64+32 + (x*64+64-data->map.mini.player_coo.x);
					int	ix = 0;
					while(sy+iy >= 0 && sy+iy<size && ix < 64)
					{
						if (sx+ix >= 0 && sx+ix<size)
						{
							char *pixel_addr = mini->data_addr + ((sy+iy) * mini->size_line + (sx+ix) * (mini->bits_per_pixel / 8));
							*(unsigned int *)pixel_addr = 0x00000000;
							
						}
						ix++;
					}
					iy++;
				}
			}
			else
			{
				while (iy < 64)
				{
					int	sx = 1*64+32 + (x*64+64-data->map.mini.player_coo.x);
					int	ix = 0;
					while(sy+iy >= 0 && sy+iy<size && ix < 64)
					{
						if (sx+ix >= 0 && sx+ix<size)
						{
							char *pixel_addr = mini->data_addr + ((sy+iy) * mini->size_line + (sx+ix) * (mini->bits_per_pixel / 8));
							if (data->map.tabmap[new_y][new_x] == '1')
							{
								// data->map.mini.img[MINI_WALL].data_addr + ((iy) * data->map.mini.img[MINI_WALL].size_line + (ix) * (data->map.mini.img[MINI_WALL].bits_per_pixel / 8)); 
								char *tmp = data->map.mini.img[MINI_WALL].data_addr + ((iy) * data->map.mini.img[MINI_WALL].size_line + (ix) * (data->map.mini.img[MINI_WALL].bits_per_pixel / 8));
								*(unsigned int *)pixel_addr = *(unsigned int *)tmp;
							}
							else
							{
								char *tmp = data->map.mini.img[MINI_FLOOR].data_addr + ((iy) * data->map.mini.img[MINI_FLOOR].size_line + (ix) * (data->map.mini.img[MINI_FLOOR].bits_per_pixel / 8));
								*(unsigned int *)pixel_addr = *(unsigned int *)tmp;
							}
						}
						ix++;
					}
					iy++;
				}
			}
			x++;
		}
		y++;
	}
	for (int y = size/2-2;y<=size/2+2;y++)
	{
		for(int x = size/2-2;x<=size/2+2;x++)
		{
			char *pixel_addr = mini->data_addr + (y * mini->size_line + x * (mini->bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = 0x00FF0000;
		}
	}
	// char *pixel_addr = mini->data_addr + (y * mini->size_line + x * (mini->bits_per_pixel / 8));
	// *(unsigned int *)pixel_addr = 0x00FF0000;
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,mini->img,0,data->mlx.height - MARGIN - size);
	mlx_destroy_image(data->mlx.mlx,mini->img);
	free(mini);
}

bool	is_move_player(t_data *data, int i)
{
	if (data->keycode[i] == KEY_W || data->keycode[i] == KEY_D
		|| data->keycode[i] == KEY_A || data->keycode[i] == KEY_S)
		return (true);
	return (false);
}

int game_loop(t_data *data) 
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


#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
int	main(int ac, char **av)
{
	t_data	data;
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

	(void)data;
	(void)ac;
	(void)av;
	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	init_img_mini(&data, &data.map.mini);
	data.map.mini.player_coo.y = 32;
	data.map.mini.player_coo.x = 32;
	// aff_mini_map(&data);
	mlx_do_key_autorepeatoff(data.mlx.mlx);
	mlx_hook(data.mlx.win, ON_KEYDOWN, 1L<<0, key_press, &data);
    mlx_hook(data.mlx.win, ON_KEYUP, 1L<<1, key_release, &data);
    mlx_hook(data.mlx.win, ON_DESTROY, 0, close_win, &data);
	// mlx_hook(data.mlx.win, ON_MOUSEMOVE, 1L << 6, mouse_move, &data);
    mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	f_exit(&data, 0);
	return (1);
}
