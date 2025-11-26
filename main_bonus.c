#include "cub3d_bonus.h"
#include "mlx.h"
#include "parsing_bonus.h"
#include "utils_bonus.h"
#include <fcntl.h>
#include "time_bonus.h"

void	run_init(t_data *data)
{
	init_struct_item(data);
	init_mutex(data);
	create_thread(data);
	open_window(data, &data->mlx);
	data->player.radius = 8;
	data->player.coo.coo_y = 32;
	data->player.coo.coo_x = 32;
	data->player.save.x = data->player.coo.case_x;
	data->player.save.y = data->player.coo.case_y;
	init_img_mini(data, &data->map.mini);
	init_foot_tab(data);
}

void	start(int ac, char **av)
{
	t_data	data;

	srand(get_mtime());
	init_data(&data, ac, av);
	parsing(&data);
	run_init(&data);
	mlx_do_key_autorepeatoff(data.mlx.mlx);
	mlx_mouse_hide(data.mlx.mlx, data.mlx.win);
	mlx_mouse_move(data.mlx.mlx, data.mlx.win, data.mlx.width / 2,
		data.mlx.height / 2);
	mlx_hook(data.mlx.win, ON_KEYDOWN, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, ON_KEYUP, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, ON_DESTROY, 0, close_win, &data);
	mlx_hook(data.mlx.win, ON_MOUSEMOVE, 1L << 6, mouse_move, &data);
	mlx_hook(data.mlx.win, ON_MOUSEDOWN, 1L << 2, mouse_key, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	pthread_barrier_destroy(&data.barrier_background);
	pthread_barrier_destroy(&data.barrier_display);
	f_exit(&data, 0);
}

int	main(int ac, char **av)
{
	start(ac, av);
	return (1);
}
