#include "struct.h"
#include "cub3d.h"
#include "utils.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "texture.h"
#include "mlx.h"

void	init_img_mini(t_data *data)
{
	int	i;

	i = 0;
	data->map.mini.img[MINI_FLOOR].path = "texture/mini_map/floor.xpm";
	data->map.mini.img[MINI_WALL].path = "texture/mini_map/wall.xpm";
	data->map.mini.img[MINI_PLAYER].path = "texture/mini_map/cursor.xpm";
	data->map.mini.img[MINI_DOOR].path = "texture/mini_map/door.xpm";
	data->map.mini.img[MINI_MOB].path = "texture/mini_map/mob.xpm";
	i = 0;
	while (i < 5)
	{
		data->map.mini.img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
				data->map.mini.img[i].path, &data->map.mini.img[i].width,
				&data->map.mini.img[i].height);
		if (!data->map.mini.img[i].img)
		{
			while (i >= 0)
			{
				mlx_destroy_image(data->mlx.mlx, data->map.mini.img[i].img);
				--i;
			}
		}
		++i;
	}
}

