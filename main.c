#include "struct.h"
#include "ft_printf.h"
#include "parsing.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
#include "player.h"
#include <stdlib.h>

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
    // Add more conditions for other keys
    printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESCAPE)
		f_exit(data, 0);
	else if (keycode == KEY_W)
		move_up(&data->map, &data->map.mini);
	else if (keycode == KEY_D)
		move_right(&data->map, &data->map.mini);
	else if (keycode == KEY_A)
		move_left(&data->map, &data->map.mini);
	else if (keycode == KEY_S)
		move_down(&data->map, &data->map.mini);
    return (0);
}

// Function called when a key is released
int key_release(int keycode) {
    // Add more conditions for other keys
    printf("Key released: %d\n", keycode);
    return (0);
}

int game_loop() {
    return (0);
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

	data->wh = malloc(sizeof(t_img));
	ft_bzero(data->wh,sizeof(t_img));
	data->wh->path = ft_strdup("texture/mini_map/white.xpm");
	data->wh->img = mlx_xpm_file_to_image(data->mlx.mlx,data->wh->path,&data->wh->width,&data->wh->height);

	data->wh = malloc(sizeof(t_img));
	ft_bzero(data->wh,sizeof(t_img));
	data->wh->path = ft_strdup("texture/mini_map/black.xpm");
	data->wh->img = mlx_xpm_file_to_image(data->mlx.mlx,data->wh->path,&data->wh->width,&data->wh->height);

	size = 9 * 64;
	mini = malloc(sizeof(t_img));
	mini->img = mlx_new_image(data->mlx.mlx, size, size);
	mini->data_addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel, &mini->size_line, &mini->endian);
 	for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            char *pixel_addr = mini->data_addr + (y * mini->size_line + x * (mini->bits_per_pixel / 8));
            *(unsigned int *)pixel_addr = 0x00FF0000;
        }
    }
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win,mini->img,0,data->mlx.height - MARGIN - size);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	// if (!load_img_mini_map(&data.mlx, &data.map.mini))
	// 	f_exit(&data, 1);
	// display_mini_map(&data, &data.map);
	aff_mini_map(&data);
	data.map.mini.player_coo = init_t_coo(32, 32);
	if (!data.map.mini.player_coo) // msg error
		f_exit(&data, 1);
	mlx_do_key_autorepeatoff(data.mlx.mlx);
	mlx_hook(data.mlx.win, ON_KEYDOWN, 1L<<0, key_press, &data);
    mlx_hook(data.mlx.win, ON_KEYUP, 1L<<1, key_release, &data);
    mlx_hook(data.mlx.win, ON_DESTROY, 0, close_win, &data);
    mlx_loop_hook(data.mlx.mlx, game_loop, 0);
	mlx_loop(data.mlx.mlx);
	// f_exit(&data, 0);
	return (1);
}
