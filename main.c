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

int	main(int ac, char **av)
{
	t_data	data;


	(void)data;
	(void)ac;
	(void)av;
	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	init_t_coo_mini(32, 32);
	// data.map.mini.player_coo.y = 32;
	// data.map.mini.player_coo.x = 32;
	init_img_mini(&data, &data.map.mini);
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


	// mlx_mouse_move();
}
