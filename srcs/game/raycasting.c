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

static int	handle_ray_x(t_data *data, t_ray *ray, t_ray ray_value)
{
	if (ray_value.delta_x < 0)
	{
		if (handle_ray_x_left(data, ray, *ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right(data, ray, *ray) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y(t_data *data, t_ray *ray, t_ray ray_value)
{
	if (ray_value.delta_y < 0)
	{
		if (handle_ray_y_top(data, ray, *ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down(data, ray, *ray) == 1)
			return (1);
	}
	return (0);
}

static void	handle_ray(t_data *data, t_ray *ray, t_ray ray_value)
{
	while (1)
	{
		if (ray_value.delta_x > 0)
			ray->rx = (64 - ray->coo_x) / ray_value.delta_x;
		else
			ray->rx = -ray->coo_x / ray_value.delta_x;
		if (ray_value.delta_y > 0)
			ray->ry = (64 - ray->coo_y) / ray_value.delta_y;
		else
			ray->ry = -ray->coo_y / ray_value.delta_y;
		if (ray->rx < ray->ry)
		{
			// printf("ray_x\n");
			if (handle_ray_x(data, ray, *ray) == 1)
				break ;
		}
		else
		{
			// printf("ray_y\n");
			if (handle_ray_y(data, ray, *ray) == 1)
				break ;
		}
	}
}

inline void    display_game(t_data *data, t_ray ray, double i)
{
	ray.dist_wall = sqrt(((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))  *  ((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))
	+ ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)) * ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x))  );
	// printf("cos angle >>>%lf\n",cos(fabs(i) * (M_PI / 180)));
	// printf("Angle=%lf   Distance_total=%lf\n",i,ray.dist_wall);
	ray.dist_wall *= cos(i * (M_PI / 180.0));
	// dist_wall *= .5;
	// double d_proj = data->mlx.height / 2 * tan(50 * (M_PI / 180)); HERE
	ray.size_wall = ray.d_proj / (double)(ray.dist_wall/64.0);
	// printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(30 * (M_PI / 180)), size_wall, data->mlx.height);
	ray.pix_x = data->mlx.width / 4 - ((ray.d_proj * tan(i * (M_PI / 180))) / (2 * ray.d_proj * tan((90/2) * (M_PI / 180)))) * data->mlx.width / 2;
	ray.pix_y = data->mlx.height / 2;
	// img_proj.img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
	// img_proj.data_addr = mlx_get_data_addr(img_proj.img,&img_proj.bits_per_pixel,&img_proj.size_line,&img_proj.endian);
	// double	pix_img_y = 1024;
	// double	pix_img_x = 1024;
	// write(1,"HERE\n",5);
	while (ray.pix_y > data->mlx.height / 2 - ray.size_wall/2 && ray.pix_y > 0 )
	{
		ray.pixel_addr = data->screen->data_addr + (ray.pix_y
					* data->screen->size_line + ray.pix_x
					* (data->screen->bits_per_pixel / 8));
		// printf("----  %d     %d  ----\n",ray.pix_y,pix_x);
		*(unsigned int *)ray.pixel_addr = 0x000000FF;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		ray.pix_y--;
	}
	while (ray.pix_y > 0)
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x00000000;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
		ray.pix_y--;
	}
	ray.pix_y = data->mlx.height / 2;
	while (ray.pix_y < data->mlx.height / 2 + ray.size_wall/2 && ray.pix_y < data->mlx.height )
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x000000FF;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
		ray.pix_y++;
	}
	while (ray.pix_y < data->mlx.height)
	{
		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (data->screen->bits_per_pixel / 8));
		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
		*(unsigned int *)ray.pixel_addr = 0x00000000;
		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
		ray.pix_y++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
	// mlx_destroy_image(data->mlx.mlx,img_proj.img);
}

void	ray_launch(t_data *data, t_ray ray)
{
	double	i;

	i = -45;
	while (i <= 45)
	{
		ray.deg = data->map.mini.deg + i + 270;
		ray.coo_y = data->map.mini.player_coo.y;
		ray.coo_x = data->map.mini.player_coo.x;
		ray.case_y = data->map.player_coo->y;
		ray.case_x = data->map.player_coo->x;
		ray.rad = ray.deg * (M_PI / 180);
		ray.delta_x = -cos(ray.rad);
		ray.delta_y = sin(ray.rad);
		// printf("START\n");
		handle_ray(data, &ray, ray);
		// printf("END\n");
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

	// 	printf("Angle=%lf   Distance_total=%lf\n",
	// 	i,
	// 	sqrt(((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))  *  ((ray->case_y - data->map.player_coo->y) * 64.0 + (ray->coo_y - data->map.mini.player_coo.y))
	// +	((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x)) * ((ray->case_x - data->map.player_coo->x) * 64.0 + (ray->coo_x - data->map.mini.player_coo.x))  ));
	// 	printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(20 * (M_PI / 180)), data->mlx.height / 2 * tan(30 * (M_PI / 180)) / (double)(2.0/64.0), data->mlx.height);
		display_game(data, ray, i);
		i += 1;
	}
}
