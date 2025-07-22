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
			// printf("ray_x\n");
			if (handle_ray_x(data, ray) == 1)
				break ;
		}
		else
		{
			// printf("ray_y\n");
			if (handle_ray_y(data, ray) == 1)
				break ;
		}
	}
}
// static void	handle_ray(t_data *data, t_ray *ray)
// {
// 	while (1)
// 	{
// 		// Calcul des distances avec gestion des cas limites
// 		if (fabs(ray->delta_x) < EPSILON)
// 			ray->rx = INFINITY;
// 		else if (ray->delta_x > 0)
// 			ray->rx = (64 - ray->coo_x) / ray->delta_x;
// 		else
// 			ray->rx = -ray->coo_x / ray->delta_x;
			
// 		if (fabs(ray->delta_y) < EPSILON)
// 			ray->ry = INFINITY;
// 		else if (ray->delta_y > 0)
// 			ray->ry = (64 - ray->coo_y) / ray->delta_y;
// 		else
// 			ray->ry = -ray->coo_y / ray->delta_y;

// 		// CORRECTION PRINCIPALE: Gestion des intersections exactes
// 		if (ray->rx < ray->ry - EPSILON)
// 		{
// 			// Intersection avec mur vertical (axe X)
// 			if (handle_ray_x(data, ray) == 1)
// 				break ;
// 		}
// 		else if (ray->ry < ray->rx - EPSILON)
// 		{
// 			// Intersection avec mur horizontal (axe Y)
// 			if (handle_ray_y(data, ray) == 1)
// 				break ;
// 		}
// 		else
// 		{
// 			// INTERSECTION EXACTE - traiter les deux axes
// 			// Priorité à l'axe X pour consistance
// 			if (handle_ray_x(data, ray) == 1)
// 				break ;
// 			// Si pas de mur en X, vérifier Y
// 			if (handle_ray_y(data, ray) == 1)
// 				break ;
// 		}
// 	}
// }

// inline void    display_game(t_data *data, t_ray ray, double i)
// {
// 	ray.dist_wall = sqrt(((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))  *  ((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))
// 	+ ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)) * ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x))  );
// 	// printf("cos angle >>>%lf\n",cos(fabs(i) * (M_PI / 180)));
// 	// printf("Angle=%lf   Distance_total=%lf\n",i,ray.dist_wall);
// 	ray.dist_wall *= cos(i * (M_PI / 180.0));
// 	// dist_wall *= .5;
// 	// double d_proj = data->mlx.height / 2 * tan(50 * (M_PI / 180)); HERE
// 	ray.size_wall = ray.d_proj / (double)(ray.dist_wall/64.0);
// 	// printf("dproj=%lf    Hauteur=%lf   mlx_height=%d\n",data->mlx.height / 2 * tan(30 * (M_PI / 180)), size_wall, data->mlx.height);
// 	ray.pix_x = data->mlx.width * 0.25 - ((ray.d_proj * tan(i * (M_PI / 180))) / (2 * ray.d_proj * tan((90 * 0.5) * (M_PI / 180)))) * data->mlx.width * 0.5;
// 	ray.pix_y = data->mlx.height * 0.5;
// 	// img_proj.img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height);
// 	// img_proj.data_addr = mlx_get_data_addr(img_proj.img,&img_proj.bits_per_pixel,&img_proj.size_line,&img_proj.endian);
// 	// double	pix_img_y = 1024;
// 	// double	pix_img_x = 1024;
// 	// write(1,"HERE\n",5);
// 	const double	max_height = data->mlx.height * 0.5;
// 	const double	max_size_wall = ray.size_wall * 0.5;
// 	const int		calc_bits = (int)(data->screen->bits_per_pixel * 0.125);
// 	while (ray.pix_y > max_height - max_size_wall && ray.pix_y > 0 )
// 	{
// 		ray.pixel_addr = data->screen->data_addr + (ray.pix_y
// 					* data->screen->size_line + ray.pix_x
// 					* (calc_bits));
// 		// printf("----  %d     %d  ----\n",ray.pix_y,pix_x);
// 		*(unsigned int *)ray.pixel_addr = 0x000000FF;
// 		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
// 		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
// 		ray.pix_y--;
// 	}
// 	while (ray.pix_y > 0)
// 	{
// 		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
// 					* data->screen->size_line + (ray.pix_x)
// 					* (calc_bits));
// 		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
// 		*(unsigned int *)ray.pixel_addr = 0x00000000;
// 		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
// 		ray.pix_y--;
// 	}
// 	ray.pix_y = data->mlx.height * 0.5;
// 	while (ray.pix_y < max_height + max_size_wall && ray.pix_y < data->mlx.height )
// 	{
// 		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
// 					* data->screen->size_line + (ray.pix_x)
// 					* (calc_bits));
// 		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
// 		*(unsigned int *)ray.pixel_addr = 0x000000FF;
// 		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x0000FF);
// 		ray.pix_y++;
// 	}
// 	while (ray.pix_y < data->mlx.height)
// 	{
// 		ray.pixel_addr = data->screen->data_addr + ((ray.pix_y)
// 					* data->screen->size_line + (ray.pix_x)
// 					* (calc_bits));
// 		// printf("put pixel >>> %d  %d\n",pix_x,ray.pix_y);
// 		*(unsigned int *)ray.pixel_addr = 0x00000000;
// 		// mlx_pixel_put(data->mlx.mlx,data->mlx.win,pix_x,ray.pix_y,0x000000);
// 		ray.pix_y++;
// 	}
// 	// mlx_destroy_image(data->mlx.mlx,img_proj.img);
// }

inline void    display_game(t_data *data, t_ray ray, double i, double x)
{
	(void)x;
	ray.dist_wall = sqrt(((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))  *  ((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))
	+ ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)) * ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)));
	ray.dist_wall *= cos(atan(x));
	// printf(" ray rad %lf \n",ray.deg);
	ray.size_wall = ray.d_proj / (double)(ray.dist_wall/64.0);
	ray.pix_x = round(i) - 2;
	// printf("pix>%d\n",ray.pix_x);
	// ray.pix_x = 1 + data->mlx.width * 0.25 - ((ray.d_proj * tan(i * (M_PI / 180))) / (2 * ray.d_proj * tan((90 * 0.5) * (M_PI / 180)))) * data->mlx.width * 0.5;
	ray.pix_y = data->mlx.height * 0.5;
	const double	max_height = data->mlx.height * 0.5; // sa degagera
	const double	max_size_wall = ray.size_wall * 0.5; // sa degagera
	const int		calc_bits = (int)(data->screen->bits_per_pixel * 0.125);
	char			*data_addr = data->screen->data_addr;
	const double	htop_wall = round(max_height - max_size_wall);
	const double	hbot_wall = round(max_height + max_size_wall);
	while (ray.pix_y > htop_wall && ray.pix_y > 0 )
	{
		ray.pixel_addr = data_addr + (ray.pix_y
					* data->screen->size_line + ray.pix_x
					* (calc_bits));
		*(unsigned int *)ray.pixel_addr = 0x00F00FF;
		ray.pix_y--;
	}
	while (ray.pix_y > 0)
	{
		ray.pixel_addr = data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (calc_bits));
		*(unsigned int *)ray.pixel_addr = 0x0FF000FF;
		ray.pix_y--;
	}
	ray.pix_y = data->mlx.height * 0.5;
	while (ray.pix_y < hbot_wall && ray.pix_y < data->mlx.height )
	{
		ray.pixel_addr = data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (calc_bits));
		*(unsigned int *)ray.pixel_addr = 0x00F00FF;
		ray.pix_y++;
	}
	while (ray.pix_y < data->mlx.height)
	{
		ray.pixel_addr = data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (calc_bits));
		*(unsigned int *)ray.pixel_addr = 708080;
		ray.pix_y++;
	}
}

void	ray_launch(t_data *data, t_ray ray)
{
	double	i;
	// double	step;
	static int a = 0;

	// step = 90.0 / data->mlx.width;
	// printf("step %lf\n",step);
	i = 0;
	int	screen_width = data->mlx.width / 2;
	while (i <= screen_width)
	{
		// ray.deg = data->map.mini.deg + i + 270;
		double x = i / screen_width;
		x *= -2;
		x += 1;
		
		ray.rad = -atan(1 / x);
		ray.deg = ray.rad;
		if (ray.rad >= 0)
			ray.rad += M_PI;
		ray.rad += data->map.mini.deg * (M_PI / 180);
		if (a == 0)
			printf("x >>> %lf\n",x);

		ray.coo_y = data->map.mini.player_coo.y;
		ray.coo_x = data->map.mini.player_coo.x;
		ray.case_y = data->map.player_coo->y;
		ray.case_x = data->map.player_coo->x;
		// ray.rad = ray.deg * (M_PI / 180);
		ray.delta_x = -cos(ray.rad);
		ray.delta_y = sin(ray.rad);
		// printf("START\n");
		handle_ray(data, &ray);

		i += 1;
		display_game(data, ray, i, x);
	}
	a = 1;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
}
