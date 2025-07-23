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

static void	check_dir(t_data *data, t_ray *ray, int i)
{
	double	hit;

	hit = 0;
	(void)i;
	if (ray->dir == NORTH)
		ray->img = data->map.north;
	else if (ray->dir == SOUTH)
		ray->img = data->map.south;
	else if (ray->dir == EAST)
		ray->img = data->map.east;
	else if (ray->dir == WEST)
		ray->img = data->map.west;
	if (ray->dir == NORTH || ray->dir == SOUTH)
		hit = data->map.player_coo->x + ray->dist_wall * ray->case_x;
	else if (ray->dir == WEST || ray->dir == EAST)
		hit = data->map.player_coo->y + ray->dist_wall * ray->case_y;
	hit -= floor(hit);
	ray->texture_coo.x = (int)hit * ray->img->width;
	if (ray->texture_coo.x < 0)
		ray->texture_coo.x = 0;
	if (ray->texture_coo.x >= ray->img->width)
		ray->texture_coo.x = ray->img->width - 1;
}

static void	display_game_loop(t_data *data, t_ray ray, double i)
{
	(void)i;
	int	texture_x = ray.texture_coo.x;
	while (ray.pix_y > ray.htop_wall && ray.pix_y > 0) //mur haut
	{
		int	texture_y = (ray.pix_y - ray.htop_wall) * ray.img->height / (ray.hbot_wall - ray.htop_wall);
		ray.pixel_addr = ray.data_addr + (ray.pix_y
					* data->screen->size_line + ray.pix_x
					* (ray.calc_bits));
		char *texture_pixel = ray.img->data_addr + (texture_y * ray.img->size_line + texture_x * (ray.img->bits_per_pixel / 8));
		unsigned int color = *(unsigned int *)texture_pixel;
		*(unsigned int *)ray.pixel_addr = color;
		ray.pix_y--;
	}
	while (ray.pix_y > 0) // ciel
	{
		ray.pixel_addr = ray.data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (ray.calc_bits));
		*(unsigned int *)ray.pixel_addr = 0x0FF000FF;
		ray.pix_y--;
	}
	ray.pix_y = data->mlx.height * 0.5;
	while (ray.pix_y < ray.hbot_wall && ray.pix_y < data->mlx.height) //mur bas
	{
		int	texture_y = (ray.pix_y - ray.htop_wall) * ray.img->height / (ray.hbot_wall - ray.htop_wall);
		// *(unsigned int *)ray.pixel_addr = 0x00F00FF;
			ray.pixel_addr = ray.data_addr + (ray.pix_y
					* data->screen->size_line + ray.pix_x
					* (ray.calc_bits));
		char *texture_pixel = ray.img->data_addr + (texture_y * ray.img->size_line + texture_x * (ray.img->bits_per_pixel / 8));
		unsigned int color = *(unsigned int *)texture_pixel;
		*(unsigned int *)ray.pixel_addr = color;
		ray.pix_y++;
	}
	while (ray.pix_y < data->mlx.height) // sol
	{
		ray.pixel_addr = ray.data_addr + ((ray.pix_y)
					* data->screen->size_line + (ray.pix_x)
					* (ray.calc_bits));
		*(unsigned int *)ray.pixel_addr = 708080;
		ray.pix_y++;
	}
}

void    display_game(t_data *data, t_ray ray, int i, double x)
{
	ray.dist_wall = sqrt(((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))  *  ((ray.case_y - data->map.player_coo->y) * 64.0 + (ray.coo_y - data->map.mini.player_coo.y))
	+ ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)) * ((ray.case_x - data->map.player_coo->x) * 64.0 + (ray.coo_x - data->map.mini.player_coo.x)));
	ray.dist_wall *= cos(atan(x));
	// printf(" ray rad %lf \n",ray.deg);
	ray.size_wall = ray.d_proj / (double)(ray.dist_wall/64.0);
	ray.pix_x = i - 2;
	// printf("pix>%d\n",ray.pix_x);
	// ray.pix_x = 1 + data->mlx.width * 0.25 - ((ray.d_proj * tan(i * (M_PI / 180))) / (2 * ray.d_proj * tan((90 * 0.5) * (M_PI / 180)))) * data->mlx.width * 0.5;
	ray.pix_y = data->mlx.height * 0.5; // sa degagera
	ray.max_height = data->mlx.height * 0.5; // sa degagera
	ray.max_size_wall = ray.size_wall * 0.5; // sa degagera
	ray.calc_bits = (int)(data->screen->bits_per_pixel * 0.125);
	ray.data_addr = data->screen->data_addr;
	ray.htop_wall = round(ray.max_height - ray.max_size_wall);
	ray.hbot_wall = round(ray.max_height + ray.max_size_wall);
	check_dir(data, &ray, i);
	display_game_loop(data, ray, i);

}
