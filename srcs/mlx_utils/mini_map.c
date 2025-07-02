#include "struct.h"
#include "cub3d.h"
#include "utils.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "texture.h"
#include "mlx.h"


bool	check_access_sprite(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1) // msg error
		return (false);
	close(fd);
	return (true);
}

static bool	init_img_mini(t_mini *mini)
{
	size_t	i;

	i = 0;
	mini->path[MINI_FLOOR] = "texture/mini_map/floor.xpm";
	mini->path[MINI_WALL] = "texture/mini_map/wall.xpm";
	mini->path[MINI_PLAYER] = "texture/mini_map/player.xpm";
	mini->path[MINI_DOOR] = "texture/mini_map/door.xpm";
	mini->path[MINI_MOB] = "texture/mini_map/mob.xpm";
	mini->path[5] = NULL;
	while (mini->path[i])
	{
		if (!check_access_sprite(mini->path[i]))
			return (false);
		++i;
	}
	return (true);
}

bool	load_img_mini_map(t_mlx *mlx, t_mini *mini)
{
	size_t	i;

	if (!init_img_mini(mini))
		return (false);
	i = 0;
	while (i < 4)
	{
		mini->sprite[i] = mlx_xpm_file_to_image(mlx->mlx, mini->path[i],
				&mini->width, &mini->height);
		if (!mini->sprite[i]) // error msg
			return (false);
		++i;
	}
	return (true);
}

void	display_mini_map(t_data *data, t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->tabmap[i])
	{
		j = 0;
		while (map->tabmap[i][j])
		{
			if (map->tabmap[i][j] == 'N')
					mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
						map->mini.sprite[MINI_PLAYER], i * 64, j * 64);
			else if (map->tabmap[i][j] == '0')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
						map->mini.sprite[MINI_FLOOR], i * 64, j * 64);
			else if (map->tabmap[i][j] == '1')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
						map->mini.sprite[MINI_WALL], i * 64, j * 64);
			++j;
		}
		++i;
	}
}
