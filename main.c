#include "struct.h"
#include "ft_printf.h"
#include "parsing.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
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

#define KEY_W 13 // 'W' key
#define KEY_A 0  // 'A' key

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


int key_press(int keycode) {
    // Add more conditions for other keys
    printf("Key pressed: %d\n", keycode);
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

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	mlx_do_key_autorepeatoff(data.mlx.mlx);
	mlx_hook(data.mlx.win, ON_KEYDOWN, 1L<<0, key_press, 0);
    mlx_hook(data.mlx.win, ON_KEYUP, 1L<<1, key_release, 0);
    mlx_hook(data.mlx.win, ON_DESTROY, 0, close_win, &data);
    mlx_loop_hook(data.mlx.mlx, game_loop, 0);
	mlx_loop(data.mlx.mlx);
	// f_exit(&data, 0);
	return (1);
}
