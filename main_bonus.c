#include "cub3d_bonus.h"
#include "mlx.h"
#include "parsing_bonus.h"
#include "utils_bonus.h"
#include <fcntl.h>
#include "time_bonus.h"

// static void	init_semaphores(t_data *data)
// {
// 	sem_unlink(SEM_BACKGROUND);
// 	// sem_unlink(SEM_START);
// 	data->sem_background = sem_open(SEM_BACKGROUND, O_CREAT, 0644, 0);
// 	if (data->sem_background == SEM_FAILED)
// 		f_exit(data, 1); // error msg
// 	// data->sem_start = sem_open(SEM_START, O_CREAT, 0644, 0);
// 	// if (data->sem_start == SEM_FAILED)
// 	// 	f_exit(data, 1); // error msg
// 	data->sem_display = sem_open(SEM_DISPLAY, O_CREAT, 0644, 0);
// 	if (data->sem_display == SEM_FAILED)
// 		f_exit(data, 1);
// 	// data->sem_map = sem_open(SEM_MAP, O_CREAT, 0644, 0);
// 	// if (data->sem_map == SEM_FAILED)
// 	// 	f_exit(data, 1);
// }

static void	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_data_ray, NULL) != 0) // error msg
		f_exit(data, 1);
}

static void	create_thread(t_data *data)
{
	if (pthread_barrier_init(&data->barrier_background, NULL, 13) != 0)
	{
        // error msg
		f_exit(data, 1);
    }
	if (pthread_create(&data->thread_sky_first, NULL, display_sky_first, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_sky_first);
	if (pthread_create(&data->thread_sky_snd, NULL, display_sky_snd, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_sky_snd);
	if (pthread_create(&data->thread_sky_third, NULL, display_sky_third, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_sky_third);
	if (pthread_create(&data->thread_sky_last, NULL, display_sky_last, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_sky_last);


	if (pthread_create(&data->thread_floor_first, NULL, display_floor_first, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_floor_first);
	if (pthread_create(&data->thread_floor_snd, NULL, display_floor_snd, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_floor_snd);
	if (pthread_create(&data->thread_floor_third, NULL, display_floor_third, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_floor_third);
	if (pthread_create(&data->thread_floor_last, NULL, display_floor_last, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_floor_last);


	if (pthread_create(&data->thread_ray_first, NULL, ray_launch_first, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_ray_first);
	if (pthread_create(&data->thread_ray_snd, NULL, ray_launch_snd, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_ray_snd);
	if (pthread_create(&data->thread_ray_third, NULL, ray_launch_third, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_ray_third);
	if (pthread_create(&data->thread_ray_last, NULL, ray_launch_last, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_ray_last);

	if (pthread_barrier_init(&data->barrier_display, NULL, 5) != 0)
	{
        // error msg
		f_exit(data, 1);
    }
	if (pthread_create(&data->thread_fst_part, NULL, display_fst_part, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_fst_part);
		if (pthread_create(&data->thread_snd_part, NULL, display_snd_part, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_snd_part);
	if (pthread_create(&data->thread_third_part, NULL, display_third_part, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_third_part);
	if (pthread_create(&data->thread_last_part, NULL, display_last_part, data) != 0)
	{
		// error msg
		f_exit(data, 1);
	}
	pthread_detach(data->thread_last_part);
}

#include <stdio.h>

// void	init_struct_door(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	while (i < data->mlx.width)
// 	{
// 		// printf("i>>>%d\n",i);
// 		data->ray[i].doors = malloc(sizeof(t_hit_door *) * (data->nb_door));
// 		if (!data->ray[i].doors)
// 			f_exit(data, 1);
// 		ft_bzero(data->ray[i].doors, sizeof(t_hit_door *) * (data->nb_door));
// 		j = 0;
// 		// printf("datanb door>>%d\n",data->nb_door);
// 		while (j < data->nb_door)
// 		{
// 			// printf("i>>>%d    j>>>%d\n",i,j);
// 			data->ray[i].doors[j] = malloc(sizeof(t_hit_door));
// 			if (!data->ray[i].doors[j])
// 				f_exit(data, 1);
// 			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
// 			j++;
// 		}
// 		++i;
// 	}
// }

// void	init_struct_enemy(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	while (i < data->mlx.width)
// 	{
// 		data->ray[i].enemys = malloc(sizeof(t_hit_enemy *) * (MAX_CREATE_ENEMY));
// 		if (!data->ray[i].enemys)
// 			f_exit(data, 1);
// 		ft_bzero(data->ray[i].enemys, sizeof(t_hit_enemy *) * (MAX_CREATE_ENEMY));
// 		j = 0;
// 		while (j < MAX_CREATE_ENEMY)
// 		{
// 			data->ray[i].enemys[j] = malloc(sizeof(t_hit_enemy));
// 			if (!data->ray[i].enemys[j])
// 				f_exit(data, 1);
// 			ft_bzero(data->ray[i].enemys[j], sizeof(t_hit_enemy));
// 			j++;
// 		}
// 		++i;
// 	}
// }

void	init_struct_item(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mlx.width)
	{
		data->ray[i].items = malloc(sizeof(t_hit_item *) * (MAX_CREATE_ITEM + MAX_CREATE_ENEMY + data->nb_door + data->map.nb_floo));
		if (!data->ray[i].items)
			f_exit(data, 1);
		ft_bzero(data->ray[i].items, sizeof(t_hit_item *) * (MAX_CREATE_ITEM + MAX_CREATE_ENEMY + data->nb_door + data->map.nb_floo));
		j = 0;
		while (j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
		{
			data->ray[i].items[j] = malloc(sizeof(t_hit_item));
			if (!data->ray[i].items[j])
				f_exit(data, 1);
			ft_bzero(data->ray[i].items[j], sizeof(t_hit_item));
			j++;
		}
		++i;
	}
}

void	init_foot_tab(t_data *data)
{
	int	i;

	// foot_tab = malloc(sizeof(t_foot *) * 8);
	// if (!foot_tab)
	// 	f_exit(data, 1);
	i = 1;
	data->map.mini.foot_tab[0].coo.case_x = data->player.coo.case_x;
	data->map.mini.foot_tab[0].coo.case_y = data->player.coo.case_y;
	data->map.mini.foot_tab[0].coo.coo_y = data->player.coo.coo_y;
	data->map.mini.foot_tab[0].coo.coo_x = data->player.coo.coo_x;
	data->map.mini.foot_tab[0].is_left = true;
	data->map.mini.foot_tab[0].is_save = true;
	data->map.mini.foot_tab[0].rad = 0;
	data->map.mini.foot_tab[0].foot_x = -1;
	data->map.mini.foot_tab[0].foot_y = -1;
	while (i < 8)
	{
		data->map.mini.foot_tab[i].is_save = false;
		data->map.mini.foot_tab[i].coo.case_x = 0;
		data->map.mini.foot_tab[i].coo.case_y = 0;
		data->map.mini.foot_tab[i].coo.coo_y = 0;
		data->map.mini.foot_tab[i].coo.coo_x = 0;
		data->map.mini.foot_tab[i].rad = 0;
		data->map.mini.foot_tab[i].is_left = true;
		data->map.mini.foot_tab[i].foot_x = -1;
		data->map.mini.foot_tab[i].foot_y = -1;
		++i;
	}
	data->map.mini.time_foot = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	srand(get_mtime());
	init_data(&data, ac, av);
	parsing(&data);
	init_struct_item(&data);
	init_mutex(&data);
	// init_semaphores(&data);
	create_thread(&data);
	open_window(&data, &data.mlx);
	data.player.radius = 8;
	data.player.coo.coo_y = 32;
	data.player.coo.coo_x = 32;
	// data.map.mini.speed = 1.5;
	init_img_mini(&data, &data.map.mini);
	init_foot_tab(&data);
	// init_display(&data, &data.f_display);
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
	// ray_launch(&data, data.ray);
	f_exit(&data, 0);
	// sem_close(data.sem_background); // FAUT CLOSE les sem dans f_exit et destroy les barier aussi
	// sem_close(data.sem_display);
	// sem_unlink(SEM_DISPLAY);
	// sem_unlink(SEM_BACKGROUND);
	pthread_barrier_destroy(&data.barrier_background);
	pthread_barrier_destroy(&data.barrier_display);
	return (1);
}
