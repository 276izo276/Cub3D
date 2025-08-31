#include "cub3d_bonus.h"
#include "mlx.h"
#include "parsing_bonus.h"
#include "utils_bonus.h"
#include <fcntl.h>

static void	init_semaphores(t_data *data)
{
	sem_unlink(SEM_BACKGROUND);
	// sem_unlink(SEM_START);
	data->sem_background = sem_open(SEM_BACKGROUND, O_CREAT, 0644, 0);
	if (data->sem_background == SEM_FAILED)
		f_exit(data, 1); // error msg
	// data->sem_start = sem_open(SEM_START, O_CREAT, 0644, 0);
	// if (data->sem_start == SEM_FAILED)
	// 	f_exit(data, 1); // error msg
	// data->sem_door = sem_open(SEM_DOOR, O_CREAT, 0644, 0);
	// if (data->sem_door == SEM_FAILED)
	// 	f_exit(data, 1);
	// data->sem_map = sem_open(SEM_MAP, O_CREAT, 0644, 0);
	// if (data->sem_map == SEM_FAILED)
	// 	f_exit(data, 1);
}

static void	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_data_ray, NULL) != 0) // error msg
		f_exit(data, 1);
}

static void	create_thread(t_data *data)
{
	if (pthread_barrier_init(&data->barrier, NULL, 3) != 0)
	{
        // error msg
		f_exit(data, 1);
    }
	if (pthread_create(&data->thread_sky, NULL, display_sky, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_sky);
	if (pthread_create(&data->thread_floor, NULL, display_floor, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_floor);
}

#include <stdio.h>

void	init_struct_door(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mlx.width)
	{
		// printf("i>>>%d\n",i);
		data->ray[i].doors = malloc(sizeof(t_hit_door *) * (data->nb_door));
		if (!data->ray[i].doors)
			f_exit(data, 1);
		ft_bzero(data->ray[i].doors, sizeof(t_hit_door *) * (data->nb_door));
		j = 0;
		// printf("datanb door>>%d\n",data->nb_door);
		while (j < data->nb_door)
		{
			// printf("i>>>%d    j>>>%d\n",i,j);
			data->ray[i].doors[j] = malloc(sizeof(t_hit_door));
			if (!data->ray[i].doors[j])
				f_exit(data, 1);
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
			j++;
		}
		++i;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	init_struct_door(&data);
	init_mutex(&data);
	init_semaphores(&data);
	create_thread(&data);
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
	sem_close(data.sem_background);
	sem_unlink(SEM_BACKGROUND);
	pthread_barrier_destroy(&data.barrier);
	return (1);
}
