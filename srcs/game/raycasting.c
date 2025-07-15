#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "time.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

static int	handle_ray_x(t_data *data, t_ray *ray)
{
	if (ray->delta_x < 0)
	{
		if (handle_ray_x_left(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right(data, ray) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y(t_data *data, t_ray *ray)
{
	if (ray->delta_y < 0)
	{
		if (handle_ray_y_top(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down(data, ray) == 1)
			return (1);
	}
	return (0);
}

static void	handle_ray(t_data *data, t_ray *ray)
{
	while (1)
	{
		if (ray->delta_x > 0)
			ray->rx = (64 - ray->coo_x) / ray->delta_x;
		else
			ray->rx = -ray->coo_x / ray->delta_x;
		if (ray->delta_y > 0)
			ray->ry = (64 - ray->coo_y) / ray->delta_y;
		else
			ray->ry = -ray->coo_y / ray->delta_y;
		if (ray->rx < ray->ry)
		{
			if (handle_ray_x(data, ray) == 1)
				break ;
		}
		else
		{
			if (handle_ray_y(data, ray) == 1)
				break ;
		}
	}
}

void	ray_launch(t_data *data, t_ray *ray)
{
	double	i;

	i = -45;
	while (i <= 45)
	{
		ray->deg = data->map.mini.deg + i + 270;
		ray->coo_y = data->map.mini.player_coo.y;
		ray->coo_x = data->map.mini.player_coo.x;
		ray->case_y = data->map.player_coo->y;
		ray->case_x = data->map.player_coo->x;
		ray->rad = ray->deg * (M_PI / 180);
		ray->delta_x = -cos(ray->rad);
		ray->delta_y = sin(ray->rad);
		handle_ray(data, ray);
			// 	data->f_display.hit_x = ray->case_x;
		// 	data->f_display.hit_y = ray->case_y;
		// 	double wall_height = (128  * 60) / sqrt(((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))  *  ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))
		// +	((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)) * ((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)));
		// 	get_pixel_col(data, &data->f_display, wall_height);
			// printf("Angle=%lf   Distance_x=%d    %d   %lf   %lf    Distance_y=%d    %d   %lf   %lf\n",
			// 	i,ray->case_x,data->map.player_coo->x,ray->coo_x,data->map.mini.player_coo.x,
			// 	ray->case_y,data->map.player_coo->y,ray->coo_y,data->map.mini.player_coo.y
			// );
		// 	printf("Angle=%lf   Distance_x=%lf    Distance_y=%lf     Distance_total=%lf\n",
		// 	i,
		// 	sqrt(((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)) * ((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x))),
		// 	sqrt( ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))  *  ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y)) ),
		// 	sqrt(((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))  *  ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))
		// +	((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)) * ((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x))  ));

		printf("Angle=%lf   Distance_total=%lf\n",
		i,
		sqrt(((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))  *  ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))
	+	((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)) * ((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x))  ));
		printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(20 * (M_PI / 180)), data->mlx.height / 2 * tan(30 * (M_PI / 180)) / (double)(2.0/64.0), data->mlx.height);
		i += .5;
	}
}
