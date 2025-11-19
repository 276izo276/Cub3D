#include "color_bonus.h"
#include "ft_printf.h"
#include "parsing_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"

static void	set_door_pos(t_door *door, int y, int x, char c)
{
	door->coo.y = y;
	door->coo.x = x;
	if (c == 'F')
		door->is_floo = 1;
}

static void	init_door(t_data *data, t_door **door)
{
	*door = malloc(sizeof(t_door));
	if (!*door)
		f_exit(data, 1);
	ft_bzero(*door, sizeof(t_door));
}

static void	init_doors(t_data *data, t_door **doors, t_door *door)
{
	int	i;

	i = 0;
	while (data->doors && data->doors[i])
		i++;
	doors = malloc(sizeof(t_door *) * (i + 2));
	if (!doors)
	{
		free(door);
		f_exit(data, 1);
	}
	doors[i + 1] = NULL;
	i = 0;
	while (data->doors && data->doors[i])
	{
		doors[i] = data->doors[i];
		i++;
	}
	doors[i] = door;
	free(data->doors);
	data->doors = doors;
}

void	add_door(t_data *data, int y, int x, char c)
{
	t_door *door;
	t_door **doors;

	door = NULL;
	doors = NULL;
	init_door(data, &door);
	set_door_pos(door, y, x, c);
	data->door = add_end_lst(door, data->door, f_elem);
	if (!data->door)
		f_exit(data, 1);
	data->map.door_map[y][x] = door;
	init_doors(data, doors, door);
}

void	save_wall(char c, int y, int x, t_data *data)
{
	t_wall_msg *wall_msg;

	if (c != '1')
		return ;
	wall_msg = malloc(sizeof(t_wall_msg));
	if (!wall_msg)
		f_exit(data, 1);
	wall_msg->msg_nb = 0;
	wall_msg->img_addr = NULL;
	wall_msg->pix_y = 0;
	wall_msg->coo.x = x;
	wall_msg->coo.y = y;
	wall_msg->is_active = false;
	data->map.wall_map[y][x] = wall_msg;
}

